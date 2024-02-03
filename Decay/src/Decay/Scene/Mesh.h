#pragma once
#include<glm\glm.hpp>

struct aiScene;

namespace Assimp
{
	class Importer;
}

namespace Decay
{
	class Material;

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 Texcoord;
		glm::vec3 Normal;
		glm::vec3 Bitangent;
		glm::vec3 Tangent;
	};

	struct Index
	{
		uint32_t V0, V1, V2;
	};

	struct Triangle
	{
		Vertex V0, V1, V2;
		Triangle(Vertex v0, Vertex v1, Vertex v2)
			:V0(v0), V1(v1), V2(v2)
		{
		}
	};

	struct AABB
	{
		glm::vec3 Min;
		glm::vec3 Max;

		AABB()
			:Min({FLT_MIN, FLT_MIN, FLT_MIN}), Max({FLT_MAX,FLT_MAX,FLT_MAX})
		{
		}
	};

	struct Submesh
	{
		uint32_t BaseVertex;
		uint32_t BaseIndex;
		uint32_t MaterialIndex;
		uint32_t VertexCount;
		uint32_t IndexCount;
		std::string MeshName;
		AABB BoundingBox;
	};

	class MeshSource
	{
	public:
		MeshSource(std::string path);
		~MeshSource();
	
	public:
		inline const std::string& GetPath() const { return m_Path; }
		inline const aiScene* GetScene() const { return m_Scene; }
		inline const std::vector<Submesh>& GetSubmeshes() const { return m_Submeshes; }
		inline const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
		inline const std::vector<Index>& GetIndices() const { return m_Indices; }
		inline const std::vector<S_PTR<Material>>& GetMaterials() const { return m_Materials; }
		inline const AABB& GetBoundingBox() const { return m_BoundingBox; }
		inline const std::map<std::uint32_t, std::vector<Triangle>>& GetTriangleCache() const { return m_TriangleCache; }

	private:
		std::string m_Path;
		const aiScene* m_Scene;
		S_PTR<Assimp::Importer> m_Importer;
		AABB m_BoundingBox;
		std::vector<Submesh> m_Submeshes;
		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;
		std::map<std::uint32_t, std::vector<Triangle>> m_TriangleCache;
		std::vector<S_PTR<Material>> m_Materials;
	};

	class Mesh
	{
	public:
		Mesh(S_PTR<MeshSource> meshSource);
		~Mesh();

		inline S_PTR<MeshSource> GetMeshSource() { return m_MeshSource; }

	private:
		S_PTR<MeshSource> m_MeshSource;
	};
}