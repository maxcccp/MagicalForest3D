#include "mbObject.hpp"


using namespace std;
using namespace glm;



std::vector<MBG::Vertex> BUBE_DATA();




//================
// MB_BASE_OBJECT
//================

// Constructor baseclass
MBG::mbObject::mbObject(const string& TexturePath, const vec3 & position)
{
	m_texture_path = TexturePath;
	

	// ставим плоскость в нужное положение 
	m_model = glm::translate(m_model, position);

	



}
// Distructor baseclass
MBG::mbObject::~mbObject()
{
}

// входной параметры этой функции не константный и передать по ссылке обязательно так как он изменят ее 
void MBG::mbObject::claculateTangentBitangent(vector<Vertex>& vertex)
{
	// T & B - это ветрока трехмерные
	// deltaUV - координаты текстурные
	// deltaPos1 - это из одной вершины вычисть другую вершину
	// deltaPos1 = ( deltaUV1.x *  T ) + ( deltaUV1.y * B );
	// deltaPos2 = ( deltaUV2.x *  T ) + ( deltaUV2.y * B );

	for (int i = 0; i < (int)vertex.size(); i+=3) {
		// positions
		glm::vec3 pos1 = vertex[i].Position; //offsetof(Vertex, TexCoords);
		glm::vec3 pos2 = vertex[i+1].Position;
		glm::vec3 pos3 = vertex[i + 2].Position;
		
		
		// texture coordinates
		glm::vec2 uv1 = vertex[i].TexCoords;
		glm::vec2 uv2 = vertex[i + 1].TexCoords;
		glm::vec2 uv3 = vertex[i + 2].TexCoords;
		
		

		// calculate tangent/bitangent vectors of both triangles
		glm::vec3 tangent1, bitangent1;
	
		// triangle 1
		// ----------
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent1 = glm::normalize(tangent1);

		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent1 = glm::normalize(bitangent1);

		// Этот метод тоже работает результат один и тот же
		/*tangent1 = (edge1 *  deltaUV2.y - edge2 * deltaUV1.y) * f;
		bitangent1 = (edge2 *  deltaUV1.x - edge1 * deltaUV2.x) * f;*/


		
		// pass
		vertex[i].Tangent = tangent1;
		vertex[i + 1].Tangent = tangent1;
		vertex[i + 2].Tangent = tangent1;

		vertex[i].Bitangent = bitangent1;
		vertex[i + 1].Bitangent = bitangent1;
		vertex[i + 2].Bitangent = bitangent1;
	
	}

}





//==================
// MB_PLANE_OBJECTS
//==================

// Constructor
MBG::mbPlaneObj::mbPlaneObj(const string& TexturePath, const vec3& position)
	:mbObject(TexturePath, position)
{

	// загрузка ткустуры
	m_deffuse_map.LoadTexture2D(TexturePath + ".png");

	// загрузка ткустуры
	m_normal_map.LoadTexture2D(TexturePath + "_normal.png");


	// данные точек
	vector<Vertex> vertex;
	vertex.push_back({ vec3(1.0f, -0.5f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(-1.0f, -0.5f, 1.0f), vec3(0.0f,  1.0f, 0.0f), vec2(1.0f,  0.0f) });
	vertex.push_back({ vec3(-1.0f, -0.5f, -1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) });

	vertex.push_back({ vec3(1.0f, -0.5f,  1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(-1.0f, -0.5f, -1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(1.0f, -0.5f, -1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f) });



	
	// прежде чем отправить в буфер на GPU 
	// нужно расчитать нормали поверхности
	claculateTangentBitangent(vertex);
	
	// сгружаем данные в буфер , а объект буфер на GPU 
	m_buffer.CreateVertexBuffer(vertex);


	//m_model = glm::rotate(m_model, 0.0f, vec3(1.0f,0.0f,0.0f));

}


// Distructor
MBG::mbPlaneObj::~mbPlaneObj()
{
}


// Draw
void MBG::mbPlaneObj::Draw( mbShader& _shader)
{

	glActiveTexture(GL_TEXTURE0);
	_shader.SetUniform("texture_diffuse0", 0);// отправить данные о матрицы модели плоскости в шейдор
	glBindTexture(GL_TEXTURE_2D, m_deffuse_map.GetTextureID());

	glActiveTexture(GL_TEXTURE1);
	_shader.SetUniform("texture_normal0", 1);// отправить данные о матрицы модели плоскости в шейдор
	glBindTexture(GL_TEXTURE_2D, m_normal_map.GetTextureID());
		
	

	_shader.SetUniform("model", m_model);// отправить данные о матрицы модели плоскости в шейдор

	m_buffer.BindVertexArrray();		// привязка к буферу вершин кде лежат данные на GPU		
	glDrawArrays(GL_TRIANGLES, 0, 6);	// рисование


	// FREE RESOURSES
	m_deffuse_map.UnBind();				// отвязаться от текстуры
	m_normal_map.UnBind();				// отвязаться от текстуры

	m_buffer.UnBindVertexArray();	// отвязаться от буфера вершин

}




//================
// MB_CUBE_OBJECT
//================

// Constructor
MBG::mbCube::mbCube(const string & TexturePath, const vec3 & position)
	:mbObject(TexturePath, position)
{

	// загрузка ткустуры
	m_deffuse_map.LoadTexture2D(TexturePath + ".png");

	// загрузка ткустуры
	m_normal_map.LoadTexture2D(TexturePath + "_normal.png");

	m_specular_map.LoadTexture2D(TexturePath + "_specular.png");
		
	// данные как рисовать трецгольники
	vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3,		//front 0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,		//right
		8, 9, 10, 8, 10, 11,	//back
		12, 13, 14, 12, 14, 15, //left
		16, 17, 18, 16, 18, 19, //upper
		20, 21, 22, 20, 22, 23	//bottom
	}; 


	// данные точек
	vector<Vertex> vertex;

	// front
	vertex.push_back({ vec3(-1.0, -1.0, 1.0),	vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, -1.0, 1.0),	vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, 1.0, 1.0),		vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(-1.0, 1.0, 1.0),	vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f) });
	// right
	vertex.push_back({ vec3(1.0, 1.0, 1.0),		vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, 1.0, -1.0),	vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, -1.0, -1.0),	vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(1.0, -1.0, 1.0),	vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f) });
	// back
	vertex.push_back({ vec3(-1.0, -1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, -1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, 1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(-1.0, 1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f) });
	//left
	vertex.push_back({ vec3(-1.0, -1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(-1.0, -1.0, 1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f) });
	vertex.push_back({ vec3(-1.0, 1.0, 1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(-1.0, 1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f) });
	//Up
	vertex.push_back({ vec3(1.0, 1.0, 1.0),		vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(-1.0, 1.0, 1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f) });
	vertex.push_back({ vec3(-1.0, 1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(1.0, 1.0, -1.0),	vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f) });
	//bottom
	vertex.push_back({ vec3(-1.0, -1.0, -1.0),	vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, -1.0, -1.0),	vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f) });
	vertex.push_back({ vec3(1.0, -1.0, 1.0),	vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f) });
	vertex.push_back({ vec3(-1.0, -1.0, 1.0),	vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) });


	// прежде чем отправить в буфер на GPU 
	// нужно расчитать нормали поверхности
	claculateTangentBitangent(vertex);


	// сгружаем данные на GPU
	m_buffer.CreateVertexBuffer(vertex, indices);

}


// Distructor
MBG::mbCube::~mbCube()
{

}

// Draw
void MBG::mbCube::Draw( mbShader & _shader)
{

	glActiveTexture(GL_TEXTURE0);
	_shader.SetUniform("texture_diffuse0", 0);// отправить данные о матрицы модели плоскости в шейдор
	glBindTexture(GL_TEXTURE_2D, m_deffuse_map.GetTextureID());


	glActiveTexture(GL_TEXTURE1);
	_shader.SetUniform("texture_specular0", 1);// отправить данные о матрицы модели плоскости в шейдор
	glBindTexture(GL_TEXTURE_2D, m_specular_map.GetTextureID());

	glActiveTexture(GL_TEXTURE2);
	_shader.SetUniform("texture_normal0", 2);// отправить данные о матрицы модели плоскости в шейдор
	glBindTexture(GL_TEXTURE_2D, m_normal_map.GetTextureID());


	

	_shader.SetUniform("model", m_model);// отправить данные о матрицы модели плоскости в шейдор

	m_buffer.BindVertexArrray();		// привязка к буферу вершин кде лежат данные на GPU		
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);	// рисование glDrawArrays(GL_TRIANGLES, 0, 6);

	
	// FREE RESOURSES
	m_specular_map.UnBind();
	m_normal_map.UnBind();					// отвязаться от текстуры
	m_deffuse_map.UnBind();					// отвязаться от текстуры
	m_buffer.UnBindVertexArray();			// отвязаться от буфера вершин

}



// АРХИВ!!!
// начальны расчет тангента и битангента
std::vector<MBG::Vertex> BUBE_DATA()
{

	using std::vector;
	using glm::vec3;
	using glm::vec2;

	std::vector<MBG::Vertex> vertex;


	// positions
	glm::vec3 pos1(-1.0, -1.0, 1.0);
	glm::vec3 pos2(1.0, -1.0, 1.0);
	glm::vec3 pos3(1.0, 1.0, 1.0);
	glm::vec3 pos4(-1.0, 1.0, 1.0);
	// texture coordinates
	glm::vec2 uv1(0.0f, 0.0f);
	glm::vec2 uv2(1.0f, 0.0f);
	glm::vec2 uv3(1.0f, 1.0f);
	glm::vec2 uv4(0.0f, 1.0f);
	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);

	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;
	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent2 = glm::normalize(bitangent2);



	// positions            // normal         // texcoords  // tangent                          // bitangent
	vertex.push_back({ vec3(pos1.x, pos1.y, pos1.z), vec3(nm.x, nm.y, nm.z), vec2(uv1.x, uv1.y), vec3(tangent1.x, tangent1.y, tangent1.z), vec3(bitangent1.x, bitangent1.y, bitangent1.z) });
	vertex.push_back({ vec3(pos2.x, pos2.y, pos2.z), vec3(nm.x, nm.y, nm.z), vec2(uv2.x, uv2.y), vec3(tangent1.x, tangent1.y, tangent1.z), vec3(bitangent1.x, bitangent1.y, bitangent1.z) });
	vertex.push_back({ vec3(pos3.x, pos3.y, pos3.z), vec3(nm.x, nm.y, nm.z), vec2(uv3.x, uv3.y), vec3(tangent1.x, tangent1.y, tangent1.z), vec3(bitangent1.x, bitangent1.y, bitangent1.z) });

	vertex.push_back({ vec3(pos1.x, pos1.y, pos1.z), vec3(nm.x, nm.y, nm.z), vec2(uv1.x, uv1.y), vec3(tangent2.x, tangent2.y, tangent2.z), vec3(bitangent2.x, bitangent2.y, bitangent2.z) });
	vertex.push_back({ vec3(pos3.x, pos3.y, pos3.z), vec3(nm.x, nm.y, nm.z), vec2(uv3.x, uv3.y), vec3(tangent2.x, tangent2.y, tangent2.z), vec3(bitangent2.x, bitangent2.y, bitangent2.z) });
	vertex.push_back({ vec3(pos4.x, pos4.y, pos4.z), vec3(nm.x, nm.y, nm.z), vec2(uv4.x, uv4.y), vec3(tangent2.x, tangent2.y, tangent2.z), vec3(bitangent2.x, bitangent2.y, bitangent2.z) });



	
	return vertex;
}