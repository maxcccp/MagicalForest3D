#include "mbModel.hpp"

// std
#include <iostream>




using namespace std;
using namespace glm;






// Work Model Assimp
#define MB_ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace)
#define MB_ASSIMP_LOAD_FLAGS_TEST (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)





// �����������, ������� ���� � 3D-������.
MBG::mbModel::mbModel(string const &path, vec3 _position, float _scale, bool _physic, bool gamma)
	: gammaCorrection(gamma)
{
	// ��� ������� ������� ������� ��������� ������ ������
	m_countTexture = 0;
	m_mat4Model = glm::mat4();


	//����� ����������� ������ � �����
	cout<< "Load-Model: " << path << endl;

	// ������� ������������ ������
	loadModel(path);

	// ����� ������� ������� ����������� ��� ������� ������
	printf("CoutnLoadTexture: %d\n", m_countTexture);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_mat4Model = glm::translate(m_mat4Model, vec3(_position.x, _position.y, _position.z));


	if  (_scale != 0.0f) {
		m_fScaleModel = _scale;
		m_mat4Model = glm::scale(m_mat4Model, vec3(_scale));
	}
}




// Distructor
MBG::mbModel::mbModel::~mbModel()
{


}


// ������ ������, �, �������������, ��� �� �����
void MBG::mbModel::mbModel::Draw(mbShader& shader)
{

	// ��� �� �������� � �������� ������ �� ������ � �� � main() ��� ��������!
	shader.SetUniform("model", m_mat4Model);

	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);

	// ������ ������� ��������, ����� ��� ���� ��������� �� �������� �� ��������� ����� ���������.
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);


}



// ��� ��������������� ������� � �����
void MBG::mbModel::ScaleModel(glm::vec3& _xyz)
{
	m_mat4Model = glm::scale(m_mat4Model, _xyz);

}



// ��� ����������� ������� � �����
void MBG::mbModel::TranslateModel(glm::vec3& _xyz)
{
	m_mat4Model = glm::translate(m_mat4Model, _xyz);


}



// ��� �������� ������� � �����
void MBG::mbModel::RorateModel(const float& _angl,const glm::vec3& _xyz)
{
	m_mat4Model = glm::rotate( glm::mat4(), _angl, _xyz );

}




// ��������� ������ � ��������������� ������������ ASSIMP �� �����
// � ��������� ���������� ����� � ������� �����.
void MBG::mbModel::loadModel(string const &path)
{
	// ������ ���� ����� ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, MB_ASSIMP_LOAD_FLAGS);
	// ��������� ������� ������
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // ���� �� ����
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// �������� ���� � �������� ���� � �����
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}




// ������������ ���� ����������� �������. ������������ ������ ��������� �����,
// ������������� �� ����, � ��������� ���� ������� �� ����� �������� ����� (���� ����).
void MBG::mbModel::processNode(aiNode *node, const aiScene *scene)
{
	// ������������ ������ �����, ������������� � ������� ����
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		// ������ ���� �������� ������ ������� ��� ���������� �������� �������� � �����.
		// � ����� ���������� ��� ������, ���� ������ ������ �������������� �������� (��������, ��������� ����� ������).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// ����� ��������� ���� ����� (���� ��� ����) �� ���������� ������������ ������ �� �������� �����
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}



// �������� ����� ������
MBG::mbMesh MBG::mbModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
	// ������ ��� ����������
	vector<Vertex> vertices;
	vector<uint> indices;
	vector<Texture> textures;

	// �������� ����� ������ �� ������ �����
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vec3 vector;		// �� ��������� ������-�����������, ��� ��� assimp ���������� ����������� ��������� �����, ������� �������� ��
							// ������������� � ����� vec3 glm,  ������� �� ������� ��������� ������ �� ���� placeholder glm :: vec3. �������
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// texture coordinates
		if (mesh->mTextureCoords[0]) // �������� �� ����� ���������� ��������?
		{
			vec2 vec;
			// ������� ����� ��������� �� 8 ��������� ��������� ��������. ����� �������, �� ������ �������������, ��� �� �� �����
			// ���������� ������, ��� ������� ����� ����� ��������� ���������� ���������, ������� �� ������ ����� ������ ����� (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = vec2(0.0f, 0.0f);
		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// ������ ����� ������ �� ������������ ����� (���� ������������ ����� ����� ��� �����������) � ��������� ��������������� ������� ������.
	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// �������� ��� ������� ���� � ��������� �� � ������� ��������
		for (uint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// ��������������� ���������
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// ��������� �������� ����������� ��� ���� ��������� � ��������. ������ ��������� �������� ������ ���� �������
	// ��� 'texture_diffuseN', ��� N - ���������� ����� �� 1 �� MAX_SAMPLER_NUMBER.
	// �� �� ����� ��������� � ������ ��������, ��� �������� � ��������� ������:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


	// ������� ������ �����, ��������� �� ����������� ������ �����
	return mbMesh(vertices, indices, textures);
}



// ��������� ��� ������������ �������� ��������� ���� � ��������� ��������, ���� ��� ��� �� ���������.
// ��������� ���������� ������������ ��� ��������� ��������.
std::vector<MBG::Texture> MBG::mbModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (uint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// ���������, ���� �� �������� ��������� ������, � ���� ��, ��������� � ��������� ��������: ���������� �������� ����� ��������
		bool skip = false;
		for (uint j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // �������� � ��� �� �������� ������� ��� ���������, ��������� � ���������. (�����������)
				break;
			}
		}
		if (!skip)
		{   // ���� �������� ��� �� ���������, ��������� ��
			Texture texture;
			m_model_TextureID = TextureFromFile(str.C_Str(), this->directory);
			texture.id = m_model_TextureID;
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);

			textures_loaded.push_back(texture);  // ��������� ��� ��� ��������, ����������� ��� ���� ������, ����� �������������, ��� �� �� ����� ��������� ��������� �������.

												 // ��������� � �������� ����������� ��������
			m_countTexture++;
			// ��� ������� � ������� ����������� ������� ��� �������
			printf("Load-Texture: %s\n", str.C_Str());
		}
	}

	return textures;
}




