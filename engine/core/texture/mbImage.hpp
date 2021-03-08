#ifndef MB_PROGRAMMER3D_IMAGE_HPP__
#define MB_PROGRAMMER3D_IMAGE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright � 2018-2019
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


		int NumberColorComponents				= GL_RGBA;                 // ���������� ������� �����������
		unsigned int TargetTexture				= GL_TEXTURE_2D;           // � ����� ��������� �� ����� ����
		unsigned int FormatTexe					= GL_RGBA;                 // ������ ������� ������� ����������� �
		unsigned int Type						= GL_UNSIGNED_BYTE;
		unsigned int FilterMin					= GL_LINEAR_MIPMAP_LINEAR; // ����� ������� ������������ �� ����� �����������
		unsigned int FilterMax					= GL_LINEAR;               // ����� ������� ������������ �� ����� ����������
		unsigned int CoordS						= GL_REPEAT;               // ����� ��������� S-����������
		unsigned int CoordT						= GL_REPEAT;               // ����� ����������� �-����������
		unsigned int CoordR						= GL_REPEAT;               // ����� ��������� R-����������


	};


	class mbImage
	{
	public:
		mbImage();
		virtual ~mbImage();
		void LoadTexture2D(const std::string& path);


		void Bind(unsigned int TargetTexture = GL_TEXTURE_2D);  // � ����� ��������� �� ����� ���� TextureUnit=0);
		void UnBind();
		unsigned int LoadTextureCubeMap(const std::vector<std::string>& faces);
		const unsigned int& GetTextureID() { return m_textureObj; }
	private:

		mbTextureInfo m_INFORMATION;
		std::string	m_fileName;
		unsigned int m_textureObj;
		unsigned int TargetTexture = GL_TEXTURE_2D;	// � ����� ��������� �� ����� ���� LoadTextureCubeMap(const std::vector<std::string>& _face);



	};


	/*Load Texture (��������� �������� � ���������� ID)*/
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);






}
#endif
