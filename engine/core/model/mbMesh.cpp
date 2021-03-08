#include "mbMesh.hpp"


#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>






using namespace std;



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// constructor
MBG::mbMesh::mbMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	// ������, ����� ���� ��� ����������� ������, ���������� ��������� ������ � ��������� �� ��� ��������.
	InitBufferMesh();
}


///////////////////////////
// Distructor
MBG::mbMesh::~mbMesh()
{
	
}



//////////////////////////////////////
// Delete buffer
void MBG::mbMesh::DeleteBuffer()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}




////////////////////////////////////////////////////
// ���������� mesh
void MBG::mbMesh::Draw(mbShader& shader)
{
	// ��������� ��������������� ��������
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	unsigned int normalNr = 0;
	unsigned int heightNr = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);	// �������� ��������� �������� �� ��������
											// �������� ����� �������� (N � diffuse_textureN)
		stringstream ss;
		string number;
		string name = textures[i].type;

		if (name == "texture_diffuse")
			ss << diffuseNr++; // transfer unsigned int to stream
		else if (name == "texture_specular")
			ss << specularNr++; // transfer unsigned int to stream
		else if (name == "texture_normal")
			ss << normalNr++; // transfer unsigned int to stream
		else if (name == "texture_height")
			ss << heightNr++; // transfer unsigned int to stream
		number = ss.str();
		// ������ ���������� ������������� � ���������� ��������
		glUniform1i(glGetUniformLocation(shader.GetProgamID(), (name + number).c_str()), i);
		// �, �������, ������� ��������
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// ������ ������� ��������, ����� ��� ���� ��������� �� �������� �� ��������� ����� ���������.
	unBindTextures(diffuseNr);
	unBindTextures(specularNr);
	unBindTextures(normalNr);
	unBindTextures(heightNr);

	
	
}



//////////////////////////
// �������� ��� ��������
void  MBG::mbMesh::unBindTextures(const int texUnitCnt) const
{
	if (texUnitCnt == 0)return;

	for (int i = 0; i < texUnitCnt; ++i)
	{
		
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}

	
}



//////////////////////////////////////////////////
// �������������� ��� �������� ������� / �������
void MBG::mbMesh::InitBufferMesh()
{
	// ��������� ������ / �������
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	// ��������� ������ � ��������� ������
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// ������������� ���� � ���������� ����������� � ���, ��� �� ����� ������ �������� ���������������� ��� ���� ��� ���������.
	// ������ ����������� � ���, ��� �� ����� ������ �������� ��������� �� ���������, � �� ������� ����������� � ������ glm :: vec3 / 2, �������
	// ����� ������������� � 3/2 float, ��� ��������� � ������ ������.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// ������������� ��������� ��������� ������
	// vertex Positions
	glEnableVertexAttribArray(mbPOSITION_ATTRIBUTE);
	glVertexAttribPointer(mbPOSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
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

	glBindVertexArray(0); // reset

}

