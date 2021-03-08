#include "mbQuad2d.hpp"

#include <GL/glew.h>



using namespace std;
using namespace glm;




glm::mat4 MBG::mbQuad2d::m_quad_model = glm::mat4();



// Constructor
MBG::mbQuad2d::mbQuad2d()
{
}


// Distructor
MBG::mbQuad2d::~mbQuad2d()
{
}


// Render
void MBG::mbQuad2d::Render(mbShader& _shader, unsigned int& texID)
{
	// передать в шедор для уменьщения и перемещения
	_shader.SetUniform("model", m_quad_model);

	// присоединится к буферу вершин
	glBindVertexArray(m_vao);
	// активизировать и привязатся к текстуру
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);
	// отрисовка
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

}



// CreateQuad2d
bool MBG::mbQuad2d::CreateQuad2d(vec2 _pos_xy, float _scale)
{

	float quadVertices[] = {
		// positions		// texture Coords
		-1.0f,  1.0f, 0.0f,	0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
		1.0f,  1.0f, 0.0f,	1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,	1.0f, 0.0f,
	};

	uint vbo;
	// setup plane VAO
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	m_quad_model = glm::scale(m_quad_model, vec3(_scale));
	m_quad_model = glm::translate(m_quad_model, vec3(_pos_xy.x, _pos_xy.y, 0.0f));




	return false;
}
