#include "dcpch.h"
#include "Mesh.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "Logger\Logger.h"
#include "Renderer\Renderer.h"
#include "Renderer\Shader.h"
#include "Renderer\Material.h"
#include "Renderer\Texture.h"

static uint32_t s_meshImportFlags = 
	aiProcess_Triangulate 
	| aiProcess_FlipUVs
	| aiProcess_OptimizeMeshes
	| aiProcess_SortByPType
	| aiProcess_CalcTangentSpace
	| aiProcess_GenNormals
	| aiProcess_GenUVCoords;

Decay::Mesh::Mesh(S_PTR<MeshSource> meshSource) : m_meshSource(meshSource)
{

}

Decay::Mesh::~Mesh()
{
	//有可能需要手动释放m_Scene
}

Decay::MeshSource::MeshSource(std::string path)
	:m_path(path)
{
	m_importer = CreateS_PTR<Assimp::Importer>();
	m_scene = m_importer->ReadFile(path, s_meshImportFlags);
	if (!m_scene || !m_scene->HasMeshes())
	{
		DC_CORE_ERROR("Failed to load mesh file: {0}", path);
		return;
	}

	uint32_t vertexCount = 0,indexCount = 0;
	
	m_submeshes.reserve(m_scene->mNumMeshes);
	for (unsigned m = 0; m < m_scene->mNumMeshes; m++)
	{
		aiMesh* mesh = m_scene->mMeshes[m];

		Submesh& submesh = m_submeshes.emplace_back();
		submesh.BaseVertex = vertexCount;
		submesh.BaseIndex = indexCount;
		submesh.MaterialIndex = mesh->mMaterialIndex;
		submesh.VertexCount = mesh->mNumVertices;
		submesh.IndexCount = mesh->mNumFaces * 3;
		submesh.MeshName = mesh->mName.C_Str();

		vertexCount += mesh->mNumVertices;
		indexCount += submesh.IndexCount;

		DC_CORE_ASSERT(mesh->HasPositions(), "Meshes require positions.");
		DC_CORE_ASSERT(mesh->HasNormals(), "Meshes require normals.");

		// Vertices
		auto& aabb = submesh.BoundingBox;
		aabb.Min = { FLT_MAX, FLT_MAX, FLT_MAX };
		aabb.Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vertex.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
			aabb.Min.x = glm::min(vertex.Position.x, aabb.Min.x);
			aabb.Min.y = glm::min(vertex.Position.y, aabb.Min.y);
			aabb.Min.z = glm::min(vertex.Position.z, aabb.Min.z);
			aabb.Max.x = glm::max(vertex.Position.x, aabb.Max.x);
			aabb.Max.y = glm::max(vertex.Position.y, aabb.Max.y);
			aabb.Max.z = glm::max(vertex.Position.z, aabb.Max.z);

			if (mesh->HasTangentsAndBitangents())
			{
				vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
				vertex.Binormal = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
			}

			if (mesh->HasTextureCoords(0))
				vertex.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };

			m_vertices.push_back(vertex);
		}

		// Indices
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			DC_CORE_ASSERT(mesh->mFaces[i].mNumIndices == 3, "Must have 3 indices.");
			Index index = { mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] };
			m_indices.push_back(index);

			m_triangleCache[m].emplace_back(m_vertices[index.V0 + submesh.BaseVertex], m_vertices[index.V1 + submesh.BaseVertex], m_vertices[index.V2 + submesh.BaseVertex]);
		}
	}

	//Textures
	if (m_scene->HasMaterials())
	{
		DC_CORE_INFO("---- Materials - {0} ----", path);

		m_materials.resize(m_scene->mNumMaterials);

		for (uint32_t i = 0; i < m_scene->mNumMaterials; i++)
		{
			auto aiMaterial = m_scene->mMaterials[i];
			auto aiMaterialName = aiMaterial->GetName();
			S_PTR<Material> mi = Material::Create(Renderer::GetShaderLibrary()->Get("PBR"), std::string(aiMaterialName.data));
			m_materials[i] = mi;

			DC_CORE_INFO("  {0} (Index = {1})", aiMaterialName.data, i);
			aiString aiTexPath;
			uint32_t textureCount = aiMaterial->GetTextureCount(aiTextureType_DIFFUSE);
			DC_CORE_INFO("    TextureCount = {0}", textureCount);

			glm::vec3 albedoColor(0.8f);
			float emission = 0.0f;
			aiColor3D aiColor, aiEmission;
			if (aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor) == AI_SUCCESS)
				albedoColor = { aiColor.r, aiColor.g, aiColor.b };

			if (aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, aiEmission) == AI_SUCCESS)
				emission = aiEmission.r;

			mi->Set("u_MaterialUniforms.AlbedoColor", albedoColor);
			mi->Set("u_MaterialUniforms.Emission", emission);

			float shininess, metalness;
			if (aiMaterial->Get(AI_MATKEY_SHININESS, shininess) != aiReturn_SUCCESS)
				shininess = 80.0f; // Default value

			if (aiMaterial->Get(AI_MATKEY_REFLECTIVITY, metalness) != aiReturn_SUCCESS)
				metalness = 0.0f;

			float roughness = 1.0f - glm::sqrt(shininess / 100.0f);
			DC_CORE_INFO("    COLOR = {0}, {1}, {2}", aiColor.r, aiColor.g, aiColor.b);
			DC_CORE_INFO("    ROUGHNESS = {0}", roughness);
			DC_CORE_INFO("    METALNESS = {0}", metalness);
			bool hasAlbedoMap = aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexPath) == AI_SUCCESS;
			bool fallback = !hasAlbedoMap;
			if (hasAlbedoMap)
			{
				S_PTR<Texture2D> texture;
				if (auto aiTexEmbedded = m_scene->GetEmbeddedTexture(aiTexPath.C_Str()))
				{
					texture = Texture2D::Create(ImageFormat::RGB, aiTexEmbedded->mWidth, aiTexEmbedded->mHeight, aiTexEmbedded->pcData);
				}
				else
				{
					std::filesystem::path pather = path;
					auto parentPath = pather.parent_path();
					parentPath /= std::string(aiTexPath.data);
					std::string texturePath = parentPath.string();
					DC_CORE_INFO("    Albedo map path = {0}", texturePath);
					texture = Texture2D::Create(texturePath);
				}

				if (texture)
				{
					mi->Set("u_AlbedoTexture", texture);
					mi->Set("u_MaterialUniforms.AlbedoColor", glm::vec3(1.0f));
				}
				else
				{
					DC_CORE_ERROR("Could not load texture: {0}", aiTexPath.C_Str());
					fallback = true;
				}
			}

			if (fallback)
			{
				DC_CORE_WARN("    No albedo map");
				mi->Set("u_AlbedoTexture", Texture2D::GetWhite());
			}

			// Normal maps
			bool hasNormalMap = aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &aiTexPath) == AI_SUCCESS;
			fallback = !hasNormalMap;
			if (hasNormalMap)
			{
				S_PTR<Texture2D> texture;
				if (auto aiTexEmbedded = m_scene->GetEmbeddedTexture(aiTexPath.C_Str()))
				{
					texture = Texture2D::Create(ImageFormat::RGB, aiTexEmbedded->mWidth, aiTexEmbedded->mHeight, aiTexEmbedded->pcData);
				}
				else
				{

					// TODO: Temp - this should be handled by Hazel's filesystem
					std::filesystem::path pather = path;
					auto parentPath = pather.parent_path();
					parentPath /= std::string(aiTexPath.data);
					std::string texturePath = parentPath.string();
					DC_CORE_INFO("    Normal map path = {0}", texturePath);
					texture = Texture2D::Create(texturePath);
				}

				if (texture)
				{
					mi->Set("u_NormalTexture", texture);
					mi->Set("u_MaterialUniforms.UseNormalMap", true);
				}
				else
				{
					DC_CORE_ERROR("    Could not load texture: {0}", aiTexPath.C_Str());
					fallback = true;
				}
			}

			if (fallback)
			{
				DC_CORE_WARN("    No normal map");
				mi->Set("u_NormalTexture", Texture2D::GetWhite());
				mi->Set("u_MaterialUniforms.UseNormalMap", false);
			}

			// Roughness map
			bool hasRoughnessMap = aiMaterial->GetTexture(aiTextureType_SHININESS, 0, &aiTexPath) == AI_SUCCESS;
			fallback = !hasRoughnessMap;
			if (hasRoughnessMap)
			{
				S_PTR<Texture2D> texture;
				if (auto aiTexEmbedded = m_scene->GetEmbeddedTexture(aiTexPath.C_Str()))
				{
					texture = Texture2D::Create(ImageFormat::RGB, aiTexEmbedded->mWidth, aiTexEmbedded->mHeight, aiTexEmbedded->pcData);
				}
				else
				{

					// TODO: Temp - this should be handled by Hazel's filesystem
					std::filesystem::path pather = path;
					auto parentPath = pather.parent_path();
					parentPath /= std::string(aiTexPath.data);
					std::string texturePath = parentPath.string();
					DC_CORE_INFO("    Roughness map path = {0}", texturePath);
					texture = Texture2D::Create(texturePath);
				}

				if (texture)
				{
					mi->Set("u_RoughnessTexture", texture);
					mi->Set("u_MaterialUniforms.Roughness", 1.0f);
				}
				else
				{
					DC_CORE_ERROR("    Could not load texture: {0}", aiTexPath.C_Str());
					fallback = true;
				}
			}

			if (fallback)
			{
				DC_CORE_WARN("    No roughness map");
				mi->Set("u_RoughnessTexture", Texture2D::GetWhite());
				mi->Set("u_MaterialUniforms.Roughness", roughness);
			}

			bool metalnessTextureFound = false;
			for (uint32_t p = 0; p < aiMaterial->mNumProperties; p++)
			{
				auto prop = aiMaterial->mProperties[p];
				if (prop->mType == aiPTI_String)
				{
					uint32_t strLength = *(uint32_t*)prop->mData;
					std::string str(prop->mData + 4, strLength);

					std::string key = prop->mKey.data;
					if (key == "$raw.ReflectionFactor|file")
					{
						S_PTR<Texture2D> texture;
						if (auto aiTexEmbedded = m_scene->GetEmbeddedTexture(str.data()))
						{
							texture = Texture2D::Create(ImageFormat::RGB, aiTexEmbedded->mWidth, aiTexEmbedded->mHeight, aiTexEmbedded->pcData);
						}
						else
						{
							// TODO: Temp - this should be handled by Hazel's filesystem
							std::filesystem::path pather = path;
							auto parentPath = pather.parent_path();
							parentPath /= str;
							std::string texturePath = parentPath.string();
							DC_CORE_INFO("    Metalness map path = {0}", texturePath);
							texture = Texture2D::Create(texturePath);
						}

						if (texture)
						{
							metalnessTextureFound = true;
							mi->Set("u_MetalnessTexture", texture);
							mi->Set("u_MaterialUniforms.Metalness", 1.0f);
						}
						else
						{
							DC_CORE_ERROR("    Could not load texture: {0}", str);
						}
						break;
					}
				}
			}

			fallback = !metalnessTextureFound;
			if (fallback)
			{
				DC_CORE_WARN("    No metalness map");
				mi->Set("u_MetalnessTexture", Texture2D::GetWhite());
				mi->Set("u_MaterialUniforms.Metalness", metalness);

			}
		}
	}
	else
	{
		auto mi = Material::Create(Renderer::GetShaderLibrary()->Get("HazelPBR_Static"), "Hazel-Default");
		mi->Set("u_MaterialUniforms.AlbedoColor", glm::vec3(0.8f));
		mi->Set("u_MaterialUniforms.Emission", 0.0f);
		mi->Set("u_MaterialUniforms.Metalness", 0.0f);
		mi->Set("u_MaterialUniforms.Roughness", 0.8f);
		mi->Set("u_MaterialUniforms.UseNormalMap", false);

		mi->Set("u_AlbedoTexture", Texture2D::GetWhite());
		mi->Set("u_MetalnessTexture", Texture2D::GetWhite());
		mi->Set("u_RoughnessTexture", Texture2D::GetWhite());
		m_materials.push_back(mi);
	}
}

Decay::MeshSource::~MeshSource()
{
}
