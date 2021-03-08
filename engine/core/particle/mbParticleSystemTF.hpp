#ifndef MB_PROGRAMMER3D_PARTICLESYSTEM_TRANSFORM_FIDBACK_HPP__
#define MB_PROGRAMMER3D_PARTICLESYSTEM_TRANSFORM_FIDBACK_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include "../texture/mbImage.hpp"
#include "../shader/mbShader.hpp"

#define NUM_PARTICLE_ATTRIBUTES 6
#define MAX_PARTICLES_ON_SCENE 100000

#define PARTICLE_TYPE_GENERATOR 0
#define PARTICLE_TYPE_NORMAL 1



class mbParticle
{
public:
	glm::vec3 vPosition;
	glm::vec3 vVelocity;
	glm::vec3 vColor;
	float fLifeTime;
	float fSize;
	int iType;
};



class mbParticleSystemTransformFeedback
{
public:

	mbParticleSystemTransformFeedback();
	bool InitalizeParticleSystem();

	void RenderParticles();
	void UpdateParticles(float fTimePassed);
	void SetMatrices(const glm::mat4* a_matProjection, glm::vec3 vEye, glm::vec3 vView, glm::vec3 vUpVector);
	void SetGeneratorProperties(glm::vec3 a_vGenPosition, glm::vec3 a_vGenVelocityMin, glm::vec3 a_vGenVelocityMax, glm::vec3 a_vGenGravityVector, glm::vec3 a_vGenColor, float a_fGenLifeMin, float a_fGenLifeMax, float a_fGenSize, float fEvery, int a_iNumToGenerate);

	int GetNumParticles();

private:
	bool bInitialized;
	float fElapsedTime;
	float fNextGenerationTime;
	float fGenLifeMin;
	float fGenLifeRange;
	float fGenSize;

	unsigned int uiTransformFeedbackBuffer;
	unsigned int uiParticleBuffer[2];
	unsigned int uiVAO[2];

	unsigned int uiQuery;
	unsigned int uiTexture;

	int iCurReadBuffer;
	int iNumParticles;
	int iNumToGenerate;

	glm::mat4 matProjection, matView;
	glm::vec3 vQuad1, vQuad2;

	glm::vec3 vGenPosition;
	glm::vec3 vGenVelocityMin, vGenVelocityRange;
	glm::vec3 vGenGravityVector;
	glm::vec3 vGenColor;

	MBG::mbImage texture;
	MBG::mbShader ShaderParticlesUpdate;
	MBG::mbShader ShaderParticlesRender;

};

#endif
