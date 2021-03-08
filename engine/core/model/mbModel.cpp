#include "mbModel.hpp"

// std
#include <iostream>




using namespace std;
using namespace glm;






// Work Model Assimp
#define MB_ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace)
#define MB_ASSIMP_LOAD_FLAGS_TEST (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)





// Конструктор, ожидает путь к 3D-модели.
MBG::mbModel::mbModel(string const &path, vec3 _position, float _scale, bool _physic, bool gamma)
	: gammaCorrection(gamma)
{
	// для отладки сколько текстур загружает каждая модель
	m_countTexture = 0;
	m_mat4Model = glm::mat4();


	//вывод звгружаемой модели в сцену
	cout<< "Load-Model: " << path << endl;

	// процесс формирования модели
	loadModel(path);

	// вывод сколько текстур загрузилось для текущей модели
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


// рисует модель, и, следовательно, все ее сетки
void MBG::mbModel::mbModel::Draw(mbShader& shader)
{

	// Что бы работать с матрицей модели из класса а не в main() ВСЕ ГОРОДИТЬ!
	shader.SetUniform("model", m_mat4Model);

	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);

	// Всегда хорошая практика, чтобы все было настроено на значения по умолчанию после настройки.
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);


}



// ДЛЯ МАСШТАБИРОВАНИЯ ОБЪЕКТА В СЦЕНЕ
void MBG::mbModel::ScaleModel(glm::vec3& _xyz)
{
	m_mat4Model = glm::scale(m_mat4Model, _xyz);

}



// ДЛЯ ПЕРЕМЕШЕНИЯ ОБЪЕКТА В СЦЕНЕ
void MBG::mbModel::TranslateModel(glm::vec3& _xyz)
{
	m_mat4Model = glm::translate(m_mat4Model, _xyz);


}



// ДЛЯ ПОВОРОТА ОБЪЕКТА В СЦЕНЕ
void MBG::mbModel::RorateModel(const float& _angl,const glm::vec3& _xyz)
{
	m_mat4Model = glm::rotate( glm::mat4(), _angl, _xyz );

}




// загружает модель с поддерживаемыми расширениями ASSIMP из файла
// и сохраняет полученные сетки в векторе сеток.
void MBG::mbModel::loadModel(string const &path)
{
	// Читать файл через ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, MB_ASSIMP_LOAD_FLAGS);
	// Проверять наличие ошибок
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // Если не ноль
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// Получить путь к каталогу пути к файлу
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}




// обрабатывает узел рекурсивным образом. Обрабатывает каждую отдельную сетку,
// расположенную на узле, и повторяет этот процесс на своих дочерних узлах (если есть).
void MBG::mbModel::processNode(aiNode *node, const aiScene *scene)
{
	// Обрабатывать каждую сетку, расположенную в текущем узле
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		// объект узла содержит только индексы для индексации реальных объектов в сцене.
		// в сцене содержатся все данные, узел должен просто организовывать материал (например, отношения между узлами).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// после обработки всех ячеек (если они есть) мы рекурсивно обрабатываем каждый из дочерних узлов
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}



// Получаем сетку модели
MBG::mbMesh MBG::mbModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
	// Данные для заполнения
	vector<Vertex> vertices;
	vector<uint> indices;
	vector<Texture> textures;

	// Пройдите через каждую из вершин сетки
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vec3 vector;		// мы объявляем вектор-заполнитель, так как assimp использует собственный векторный класс, который напрямую не
							// преобразуется в класс vec3 glm,  поэтому мы сначала переносим данные на этот placeholder glm :: vec3. позиции
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
		if (mesh->mTextureCoords[0]) // содержит ли сетка координаты текстуры?
		{
			vec2 vec;
			// вершина может содержать до 8 различных координат текстуры. Таким образом, мы делаем предположение, что мы не будем
			// используем модели, где вершина может иметь несколько текстурных координат, поэтому мы всегда берем первый набор (0).
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
	// Теперь через каждую из поверхностей сетки (лицо представляет собой сетку его треугольник) и извлекают соответствующие индексы вершин.
	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Получить все индексы лица и сохранить их в векторе индексов
		for (uint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Технологические материалы
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// принимаем условное обозначение для имен семплеров в шейдерах. Каждая диффузная текстура должна быть названа
	// как 'texture_diffuseN', где N - порядковое число от 1 до MAX_SAMPLER_NUMBER.
	// То же самое относится к другой текстуре, как показано в следующем списке:
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


	// Вернуть объект сетки, созданный из извлеченных данных сетки
	return mbMesh(vertices, indices, textures);
}



// проверяет все материальные текстуры заданного типа и загружает текстуры, если они еще не загружены.
// требуемая информация возвращается как структура текстуры.
std::vector<MBG::Texture> MBG::mbModel::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (uint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		// Проверьте, была ли текстура загружена раньше, и если да, перейдите к следующей итерации: пропустите загрузку новой текстуры
		bool skip = false;
		for (uint j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // Текстура с тем же файловым каналом уже загружена, перейдите к следующей. (Оптимизация)
				break;
			}
		}
		if (!skip)
		{   // Если текстура уже не загружена, загрузите ее
			Texture texture;
			m_model_TextureID = TextureFromFile(str.C_Str(), this->directory);
			texture.id = m_model_TextureID;
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);

			textures_loaded.push_back(texture);  // Сохраните его как текстуру, загруженную для всей модели, чтобы гарантировать, что мы не будем загружать дубликаты текстур.

												 // добавляем к счетчику загруженную текстуру
			m_countTexture++;
			// для вываода в консоль загружженых текстур для отладки
			printf("Load-Texture: %s\n", str.C_Str());
		}
	}

	return textures;
}




