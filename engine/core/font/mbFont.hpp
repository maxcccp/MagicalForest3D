#ifndef MB_PROGRAMMER3D_FONT_HPP__
#define MB_PROGRAMMER3D_FONT_HPP__
/*
*	www.mbprogrammer.com
*	maximprogram.cpp@mail.ru
*   Copyright © 2018-2019 Maksim Bogomolov
*/


// ft
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H



// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
// std
#include <map>
// mb
#include "../../common/mbType.hpp"
#include "../shader/mbShader.hpp"


namespace MBG
{

		struct Character {
			unsigned int TextureID;     // ID handle of the glyph texture
			glm::ivec2 Size;            // Size of glyph
			glm::ivec2 Bearing;         // Offset from baseline to left/top of glyph
			unsigned int Advance;       // Offset to advance to next glyph
		};


		class mbFont
		{
			friend void Text(mbFont& font, std::string text, float x, float y, float scale, glm::vec3 color);
		public:
			mbFont(const std::string& pathFont,const mbShader& shaderProgram);
			virtual ~mbFont();

			const mbShader* GetShaderFont() { return m_shader_font; }

		private:
			const mbShader* m_shader_font;
			unsigned int m_vao_font, m_vbo_font;
			std::map<char, Character> m_Characters;

		};

		void Text(mbFont& font, std::string text, float x, float y, float scale, glm::vec3 color);

}
#endif
