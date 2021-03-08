#include "mbShadowMap.hpp"


#include <GL/glew.h>


using namespace std;
using namespace glm;


mat4 scale_bias_matrix = glm::mat4( glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
                                    glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
                                    glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
                                    glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
                                );


/*
* Constructor
*/
MBG::mbShadowMap::mbShadowMap()
{

}



/*
* Distructor
*/
MBG::mbShadowMap::~mbShadowMap()
{
}



/*
* Читать в текстуру
*/
void MBG::mbShadowMap::Write(mbShader* shader)
{
	glEnable(GL_DEPTH_TEST);
	// так сказать привязываемя к созданному мной фрейму
	glViewport(0, 0, m_SHADOW_INFO.Windth, m_SHADOW_INFO.Height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(4.0f, 4.0f);


	//glm::mat4 depthModelMatrix = glm::mat4(1.0);


    shader->SetUniform("lightSpaceMatrix",m_SHADOW_INFO.SpaseMatrix );

}



/*
* Отвязатся от моего FBO и привязаться к главному фрайму
*/
void MBG::mbShadowMap::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



/*
* Создание текстуры и Фрайм буффера для рендара туда все объекты сцены
*/
bool MBG::mbShadowMap::CreateShadowMap(int SHADOW_WIDTH, int SHADOW_HEIGHT, vec3 posLight, float NearPlane, float FarPlane)
{
	m_SHADOW_INFO.Windth	= SHADOW_WIDTH;
	m_SHADOW_INFO.Height	= SHADOW_HEIGHT;
	m_SHADOW_INFO.Near		= NearPlane;
	m_SHADOW_INFO.Far		= FarPlane;
	m_SHADOW_INFO.PosLight	= posLight;
	( NearPlane > 0.1f )	?	m_SHADOW_INFO.Near = NearPlane	:	m_SHADOW_INFO.Near = 0.1f;
	( FarPlane > 7.5f )		?	m_SHADOW_INFO.Far = FarPlane	:	m_SHADOW_INFO.Far = 7.5f;

	float x = 10.0f, y = 10.0f;

	m_SHADOW_INFO.View = glm::lookAt(m_SHADOW_INFO.PosLight, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	m_SHADOW_INFO.Projection = glm::ortho(-x, x, -y, y, m_SHADOW_INFO.Near, m_SHADOW_INFO.Far);
    // для постоянной передачи в шейдор матриуцы проекции света
	m_SHADOW_INFO.SpaseMatrix = m_SHADOW_INFO.Projection * m_SHADOW_INFO.View ;

	// создание фрейма буфера куда сгружать всю сцену
	glGenFramebuffers(1, &m_DepthMapFBO);

	// create depth texture
	glGenTextures(1, &m_DepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// необходимо для использования depth-текстуры как shadow map
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// проверим текущий FBO на корректность
	unsigned int fboStatus;
	if ((fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("glCheckFramebufferStatus error 0x%X\n", fboStatus);
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	return true;
}

bool MBG::mbShadowMap::CreateShadowMapTwo(int WIDTH, int HEIGHT, vec3 posLight, float NearPlane, float FarPlane)
{

	m_SHADOW_INFO.Windth = WIDTH;
	m_SHADOW_INFO.Height = HEIGHT;
	m_SHADOW_INFO.Near = NearPlane;
	m_SHADOW_INFO.Far = FarPlane;
	m_SHADOW_INFO.PosLight = posLight;
	(NearPlane > 0.1f) ? m_SHADOW_INFO.Near = NearPlane : m_SHADOW_INFO.Near = 0.1f;
	(FarPlane > 7.5f) ? m_SHADOW_INFO.Far = FarPlane : m_SHADOW_INFO.Far = 7.5f;

	m_SHADOW_INFO.View = glm::lookAt(m_SHADOW_INFO.PosLight, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	m_SHADOW_INFO.Projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, m_SHADOW_INFO.Near, m_SHADOW_INFO.Far);
	glGenFramebuffers(1, &m_DepthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_DepthMapFBO);

	glGenTextures(1, &m_DepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_DepthTexture);
	//glTexStorage2D(GL_TEXTURE_2D, 11, GL_DEPTH_COMPONENT24, WIDTH, HEIGHT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthTexture, 0);

	glGenTextures(1, &m_ColorTexture);
	glBindTexture(GL_TEXTURE_2D, m_ColorTexture);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, WIDTH, HEIGHT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_COLOR_COMPONENTS, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorTexture, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_DEPTH_TEST);


	return false;
}
