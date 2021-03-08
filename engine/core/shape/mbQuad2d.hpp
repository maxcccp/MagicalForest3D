#ifndef MB_PROGRAMMER3D_QUAD_HPP__
#define MB_PROGRAMMER3D_QUAD_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <glm/glm.hpp>
#include "../shader/mbShader.hpp"


namespace MBG
{

	class mbQuad2d
	{
	public:
		mbQuad2d();
		virtual ~mbQuad2d();

		void Render(mbShader& _shader, unsigned int& texID);
		bool CreateQuad2d(glm::vec2 _pos_xy,float _scale = 0.5f);

	private:
		unsigned int m_vao;
		static glm::mat4 m_quad_model;
	};

}
#endif
