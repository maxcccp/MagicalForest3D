#ifndef MB_PROGRAMMER3D_MODEL_HPP__
#define MB_PROGRAMMER3D_MODEL_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include "mbMesh.hpp"
#include "../texture/mbImage.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>



namespace MBG
{

	class mbModel
	{
	public:

		mbModel() {}
		mbModel(std::string const &path, glm::vec3 _position = glm::vec3(0.0f), float _scale = 0.0f, bool _physic = false, bool gamma = false);
		virtual ~mbModel();

		std::string directory;
		bool gammaCorrection;
		std::vector<mbMesh> meshes;
		std::vector<Texture> textures_loaded;

		void ScaleModel(glm::vec3& _xyz);
		void TranslateModel(glm::vec3& _xyz);
		void Draw(mbShader& shader);
		void RorateModel(const float& _angl, const glm::vec3& _xyz);

		glm::mat4& GetMatModel() { return m_mat4Model; }
		const unsigned int& GetTextureID() { return m_model_TextureID; }

	private:

		glm::mat4				m_mat4Model;
		float					m_fScaleModel;
		unsigned short			m_countTexture;
		unsigned int			m_model_TextureID;

		void loadModel(std::string const &path);
		void processNode(aiNode *node, const aiScene *scene);
		mbMesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	};

}
#endif
