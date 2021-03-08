#ifndef MB_PROGRAMMER3D_IMAGE_HPP__
#define MB_PROGRAMMER3D_IMAGE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <GL/glew.h>
#include <vector>
#include "../../common/mbType.hpp"



namespace MBG
{


	struct mbTextureInfo
	{
		bool MipMap = true;
		int Width = 0;
		int Height = 0;
		unsigned int Depth = 0;


		int NumberColorComponents				= GL_RGBA;                 // количество цветных компонентов
		unsigned int TargetTexture				= GL_TEXTURE_2D;           // с какой текстурой мы имеем дело
		unsigned int FormatTexe					= GL_RGBA;                 // формат каждого текселя сохраняется в
		unsigned int Type						= GL_UNSIGNED_BYTE;
		unsigned int FilterMin					= GL_LINEAR_MIPMAP_LINEAR; // метод фильтра использовать во время минимизации
		unsigned int FilterMax					= GL_LINEAR;               // метод фильтра использовать во время увеличения
		unsigned int CoordS						= GL_REPEAT;               // метод обтекания S-координаты
		unsigned int CoordT						= GL_REPEAT;               // метод обертывания Т-координаты
		unsigned int CoordR						= GL_REPEAT;               // метод обтекания R-координаты


	};


	class mbImage
	{
	public:
		mbImage();
		virtual ~mbImage();
		void LoadTexture2D(const std::string& path);


		void Bind(unsigned int TargetTexture = GL_TEXTURE_2D);  // с какой текстурой мы имеем дело TextureUnit=0);
		void UnBind();
		unsigned int LoadTextureCubeMap(const std::vector<std::string>& faces);
		const unsigned int& GetTextureID() { return m_textureObj; }
	private:

		mbTextureInfo m_INFORMATION;
		std::string	m_fileName;
		unsigned int m_textureObj;
		unsigned int TargetTexture = GL_TEXTURE_2D;	// с какой текстурой мы имеем дело LoadTextureCubeMap(const std::vector<std::string>& _face);



	};


	/*Load Texture (загружает текстуру и возвращает ID)*/
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);






}
#endif
