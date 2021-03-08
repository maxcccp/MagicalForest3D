#include "mbImage.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cassert>

/*
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <SOIL/SOIL.h>
*/

using namespace std;




void MBG::mbImage::LoadTexture2D(const std::string& path)
{
	glGenTextures(1, &m_textureObj);

	unsigned char* image = stbi_load(path.c_str(), &m_INFORMATION.Width, &m_INFORMATION.Height, &m_INFORMATION.NumberColorComponents,0);


	// ну если все впорядке то продолжаем если нет вываливаемсся из функции
	if (image)
	{
		// assert(TargetTexture == GL_TEXTURE_2D);
		//m_INFORMATION.TargetTexture = TargetTexture;


		if (m_INFORMATION.NumberColorComponents == 1)
			m_INFORMATION.FormatTexe = GL_RED;
		else if (m_INFORMATION.NumberColorComponents == 3)
			m_INFORMATION.FormatTexe = GL_RGB;
		else if (m_INFORMATION.NumberColorComponents == 4)
			m_INFORMATION.FormatTexe = GL_RGBA;

		// соеденяю текстуру
		Bind(0);

		glTexImage2D(m_INFORMATION.TargetTexture, 0, m_INFORMATION.FormatTexe, m_INFORMATION.Width, m_INFORMATION.Height, 0, m_INFORMATION.FormatTexe, m_INFORMATION.Type, image);

		glTexParameteri(m_INFORMATION.TargetTexture, GL_TEXTURE_MIN_FILTER, m_INFORMATION.FilterMin);
		glTexParameteri(m_INFORMATION.TargetTexture, GL_TEXTURE_MAG_FILTER, m_INFORMATION.FilterMax);
		glTexParameteri(m_INFORMATION.TargetTexture, GL_TEXTURE_WRAP_S, m_INFORMATION.CoordS);
		glTexParameteri(m_INFORMATION.TargetTexture, GL_TEXTURE_WRAP_T, m_INFORMATION.CoordT);
		if (m_INFORMATION.MipMap)
			glGenerateMipmap(m_INFORMATION.TargetTexture);

		// Отсоеденяю текстуру от текущего состояния машины opengl
		UnBind();
		stbi_image_free(image);
		// для отладки загруженная текстура
		std::cout << "Load-Texture: " << path << std::endl;;
	}
	else {
		cout << "Not loading textute: " << path << endl;
		return;
	}
}






/* constructor*/
MBG::mbImage::mbImage()
{

}

/* distructor*/
MBG::mbImage::~mbImage()
{
	//glDeleteTextures(1, m_texture_id);
	//// free pointer
	//if (m_texture_id) {
	//	delete m_texture_id;
	//	m_texture_id = nullptr;
	//}


}



// Loading Texture2D //
unsigned int MBG::mbImage::LoadTextureCubeMap(const std::vector<std::string>& faces)
{

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {

			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}



// Drow texture to display //
void MBG::mbImage::Bind(unsigned int TextureUnit)
{
	// test checkout.
	assert(TextureUnit >= 0 && TextureUnit <= 31);

	// Fctivate texture.
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureObj);

}

void MBG::mbImage::UnBind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


/* TextureFromFile */
unsigned int MBG::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load( filename.c_str(), &width, &height, &nrComponents, 4 );
	if (data)
	{
		unsigned int format = GL_RGB;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		// UnBind texture
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;

		// reset
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	return textureID;
}
