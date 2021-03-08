#include "mbBuffer.hpp"

#include <GL/glew.h>


using namespace std;






// Constructor
MBG::mbBuffer::mbBuffer()
	:m_vao(0),m_vbo(0),m_ebo(0)
{
	m_data_anloaded = false;
}


// Distructor
MBG::mbBuffer::~mbBuffer()
{
	DeleteBuffer();
}

void MBG::mbBuffer::CreateVertexBuffer(Vertex* vertices, unsigned int* indices)
{
	

}

// Создание буфера вершин на GPU и загружать все данные на видеокарту
void MBG::mbBuffer::CreateVertexBuffer(vector<Vertex> vertices, vector<unsigned int> indices)
{
	this->m_vertices = vertices;
	this->m_indices = indices;


	

	// Создавать буферы / массивы
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	// загружать данные в вершинные буферы
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	// Замечательная вещь о структурах заключается в том, что их макет памяти является последовательным для всех его элементов.
	// Эффект заключается в том, что мы можем просто передать указатель на структуру, и он отлично переводится в массив glm :: vec3 / 2, который
	// снова преобразуется в 3/2 float, что переводит в массив байтов.
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);


	// если не пуст то данные будем сгружать на видеокарту
	if (!m_indices.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	}


	// устанавливаем указатели атрибутов вершин по умолчанию(default)
	// vertex Positions
	glEnableVertexAttribArray(mbPOSITION_ATTRIBUTE);
	glVertexAttribPointer(mbPOSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)NULL);
	// vertex normals
	glEnableVertexAttribArray(mbNORMAL_ATTRIBUTE);
	glVertexAttribPointer(mbNORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(mbTEXTURECOORD_ATTRIBUTE);
	glVertexAttribPointer(mbTEXTURECOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(mbTANGENT_ATTRIBUTE);
	glVertexAttribPointer(mbTANGENT_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(mbBITANGENT_ATTRIBUTE);
	glVertexAttribPointer(mbBITANGENT_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	// данные сгруженны на видеокарту
	m_data_anloaded = true;

	// отвязаться пока от текущего VAO
	UnBindVertexArray();

}

// SetAttribPosition
void MBG::mbBuffer::SetAttribPosition(const unsigned int& _position)
{
	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();

	// vertex Positions
	glEnableVertexAttribArray(_position);
	glVertexAttribPointer(_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	// отвязаться пока от текущего m_vao
	UnBindVertexArray();

}

// SetAttribNormal
void MBG::mbBuffer::SetAttribNormal(const unsigned int & _normal)
{
	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();
	
	// vertex normals
	glEnableVertexAttribArray(_normal);
	glVertexAttribPointer(_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	
	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();

}

// SetAttribTexCoord
void MBG::mbBuffer::SetAttribTexCoord(const unsigned int & _texCoord)
{
	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();

	// vertex texture coords
	glEnableVertexAttribArray(_texCoord);
	glVertexAttribPointer(_texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();
}

// SetAttribTangent
void MBG::mbBuffer::SetAttribTangent(const unsigned int & _Tangent)
{
	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();

	// vertex tangent
	glEnableVertexAttribArray(_Tangent);
	glVertexAttribPointer(_Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();
}

// SetAttribBiTangent
void MBG::mbBuffer::SetAttribBiTangent(const unsigned int & _biTangent)
{
	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();

	// vertex bitangent
	glEnableVertexAttribArray(_biTangent);
	glVertexAttribPointer(_biTangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	// привязка к внутренему m_vao(куда все сгрузили)
	BindVertexArrray();
}



// Принудительно удолить все выделеные буферы
void MBG::mbBuffer::DeleteBuffer() const
{
	// но сначало отвязеться от него 
	UnBindVertexArray();
	// а уж потом освобождать память на GPU
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}
// привязаться к буферу вершин на видеокарте
void MBG::mbBuffer::BindVertexArrray() const
{
	glBindVertexArray(m_vao); // reset
}
// отвязаться от текущего буфера вершин 
void MBG::mbBuffer::UnBindVertexArray()const
{
	glBindVertexArray(0); // reset
}
