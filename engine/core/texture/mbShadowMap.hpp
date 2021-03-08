#ifndef MB_PROGRAMMER3D_SHADOWMAP_HPP__
#define MB_PROGRAMMER3D_SHADOWMAP_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <glm/glm.hpp>
#include "../shader/mbShader.hpp"

namespace MBG
{



	struct Shadowinfo
	{
		float Near;
		float Far;
		int Windth;
		int Height;
		glm::vec3 PosLight;
		glm::mat4 View;
		glm::mat4 Projection;
		glm::mat4 SpaseMatrix;
	};



	class mbShadowMap
	{
	public:
		mbShadowMap();
		bool CreateShadowMap(int WIDTH = 1024, int HEIGHT = 1024 , glm::vec3 posLight = glm::vec3(0.0f), float NearPlane = 0.1f, float FarPlane =7.5f );
		bool CreateShadowMapTwo(int WIDTH = 1024, int HEIGHT = 1024, glm::vec3 posLight = glm::vec3(0.0f), float NearPlane = 0.1f, float FarPlane = 7.5f);
		virtual ~mbShadowMap();


		void Write(mbShader* shader);
		void End();
		inline  unsigned int& GetDepthTextureID() { return m_DepthTexture; }
		inline  unsigned int& GetColorTextureID() { return m_ColorTexture; }
		inline glm::mat4& GetSpaceMat4() { return m_SHADOW_INFO.SpaseMatrix; }
		inline Shadowinfo GetInfo() {return m_SHADOW_INFO;}
		unsigned int m_DepthMapFBO;
	protected:
	private:

		unsigned int m_DepthTexture;
		unsigned int m_ColorTexture;
		glm::mat4 lightSpaceMatrix;
		Shadowinfo m_SHADOW_INFO;

	};




}
#endif
