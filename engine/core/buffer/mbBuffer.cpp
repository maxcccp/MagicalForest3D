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

// �������� ������ ������ �� GPU � ��������� ��� ������ �� ����������
void MBG::mbBuffer::CreateVertexBuffer(vector<Vertex> vertices, vector<unsigned int> indices)
{
	this->m_vertices = vertices;
	this->m_indices = indices;


	

	// ��������� ������ / �������
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	// ��������� ������ � ��������� ������
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	// ������������� ���� � ���������� ����������� � ���, ��� �� ����� ������ �������� ���������������� ��� ���� ��� ���������.
	// ������ ����������� � ���, ��� �� ����� ������ �������� ��������� �� ���������, � �� ������� ����������� � ������ glm :: vec3 / 2, �������
	// ����� ������������� � 3/2 float, ��� ��������� � ������ ������.
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);


	// ���� �� ���� �� ������ ����� �������� �� ����������
	if (!m_indices.empty()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	}


	// ������������� ��������� ��������� ������ �� ���������(default)
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

	// ������ ��������� �� ����������
	m_data_anloaded = true;

	// ���������� ���� �� �������� VAO
	UnBindVertexArray();

}

// SetAttribPosition
void MBG::mbBuffer::SetAttribPosition(const unsigned int& _position)
{
	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();

	// vertex Positions
	glEnableVertexAttribArray(_position);
	glVertexAttribPointer(_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	
	// ���������� ���� �� �������� m_vao
	UnBindVertexArray();

}

// SetAttribNormal
void MBG::mbBuffer::SetAttribNormal(const unsigned int & _normal)
{
	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();
	
	// vertex normals
	glEnableVertexAttribArray(_normal);
	glVertexAttribPointer(_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	
	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();

}

// SetAttribTexCoord
void MBG::mbBuffer::SetAttribTexCoord(const unsigned int & _texCoord)
{
	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();

	// vertex texture coords
	glEnableVertexAttribArray(_texCoord);
	glVertexAttribPointer(_texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();
}

// SetAttribTangent
void MBG::mbBuffer::SetAttribTangent(const unsigned int & _Tangent)
{
	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();

	// vertex tangent
	glEnableVertexAttribArray(_Tangent);
	glVertexAttribPointer(_Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();
}

// SetAttribBiTangent
void MBG::mbBuffer::SetAttribBiTangent(const unsigned int & _biTangent)
{
	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();

	// vertex bitangent
	glEnableVertexAttribArray(_biTangent);
	glVertexAttribPointer(_biTangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	// �������� � ���������� m_vao(���� ��� ��������)
	BindVertexArrray();
}



// ������������� ������� ��� ��������� ������
void MBG::mbBuffer::DeleteBuffer() const
{
	// �� ������� ���������� �� ���� 
	UnBindVertexArray();
	// � �� ����� ����������� ������ �� GPU
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
}
// ����������� � ������ ������ �� ����������
void MBG::mbBuffer::BindVertexArrray() const
{
	glBindVertexArray(m_vao); // reset
}
// ���������� �� �������� ������ ������ 
void MBG::mbBuffer::UnBindVertexArray()const
{
	glBindVertexArray(0); // reset
}
