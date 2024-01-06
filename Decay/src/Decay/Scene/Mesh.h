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
		glm::vec3 Binormal;
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

	private:
		std::string m_path;
		const aiScene* m_scene;
		S_PTR<Assimp::Importer> m_importer;
		AABB m_boundingBox;
		std::vector<Submesh> m_submeshes;
		std::vector<Vertex> m_vertices;
		std::vector<Index> m_indices;
		std::map<std::uint32_t, std::vector<Triangle>> m_triangleCache;
		std::vector<S_PTR<Material>> m_materials;
	};

	class Mesh
	{
	public:
		Mesh(S_PTR<MeshSource> meshSource);
		~Mesh();

	private:
		S_PTR<MeshSource> m_meshSource;
	};
}