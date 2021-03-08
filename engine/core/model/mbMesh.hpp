#ifndef MB_PROGRAMMER3D_MESH_HPP__
#define MB_PROGRAMMER3D_MESH_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../../common/mbType.hpp"
#include "../shader/mbShader.hpp"






namespace MBG
{

	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	struct Texture {
		unsigned int id;
		std::string type;
		aiString path;
	};


	class mbMesh
	{
	public:
		mbMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		virtual ~mbMesh();

		void Draw(mbShader& shader);
		void DeleteBuffer();
		void unBindTextures(const int texUnitCnt) const;

	private:

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		void InitBufferMesh();

		std::vector<Vertex> vertices;
		std::vector<Texture> textures;
		std::vector<unsigned int> indices;

	};



}
#endif
