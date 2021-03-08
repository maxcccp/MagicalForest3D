#include "mbParticleSystemTF.hpp"


using namespace std;




/////////////////////////////////////////////////////////////////////
// Constructor
mbParticleSystemTransformFeedback::mbParticleSystemTransformFeedback()
{
	bInitialized = false;
	iCurReadBuffer = 0;
}




///////////////////////////////////////////////////////////////////////////////
//	Инициализирует все буферы и данные на GPUдля системы частиц обратной связи.
bool mbParticleSystemTransformFeedback::InitalizeParticleSystem()
{
	if(bInitialized)return false;

	texture.LoadTexture2D("data/textures/snowflakes7.png");

	const char* sVaryings[NUM_PARTICLE_ATTRIBUTES] =
	{
		"vPositionOut",
		"vVelocityOut",
		"vColorOut",
		"fLifeTimeOut",
		"fSizeOut",
		"iTypeOut",
	};

	// Updating program
	ShaderParticlesUpdate.LoadDetal("data/glsl/Particle/particles_update.vs","data/glsl/Particle/particles_update.gs","data/glsl/Particle/particles_update.fs");

	// обязательно передать glTransformFeedbackVaryings до линковки шейдорной прогрммы
	// так понял, что передать данные в шейдор а уж потом линковать прогрмму
	FOR(i, NUM_PARTICLE_ATTRIBUTES)
		glTransformFeedbackVaryings(ShaderParticlesUpdate.GetProgamID(), 6, sVaryings, GL_INTERLEAVED_ATTRIBS);
	// link
	ShaderParticlesUpdate.LinkProgram();


	// Rendering program
	ShaderParticlesRender.LoadDetal("data/glsl/Particle/particles_render.vs", "data/glsl/Particle/particles_render.gs", "data/glsl/Particle/particles_render.fs");
	// link
	ShaderParticlesRender.LinkProgram();

	glGenTransformFeedbacks(1, &uiTransformFeedbackBuffer);
	glGenQueries(1, &uiQuery);

	glGenBuffers(2, uiParticleBuffer);
	glGenVertexArrays(2, uiVAO);

	mbParticle partInitialization;
	partInitialization.iType = PARTICLE_TYPE_GENERATOR;

	FOR(i, 2)
	{
		glBindVertexArray(uiVAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, uiParticleBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mbParticle)*MAX_PARTICLES_ON_SCENE, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(mbParticle), &partInitialization);

		FOR(i, NUM_PARTICLE_ATTRIBUTES)
			glEnableVertexAttribArray(i);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mbParticle), (const GLvoid*)0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mbParticle), (const GLvoid*)12); // Velocity
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(mbParticle), (const GLvoid*)24); // Color
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(mbParticle), (const GLvoid*)36); // Lifetime
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(mbParticle), (const GLvoid*)40); // Size
		glVertexAttribPointer(5, 1, GL_INT,	  GL_FALSE, sizeof(mbParticle), (const GLvoid*)44); // Type
	}
	iCurReadBuffer = 0;
	iNumParticles = 1;

	bInitialized = true;

	return true;
}





//////////////////////////////////////////////////////////////////////////////////////////////
// Выполняет обновление частиц на GPU. fTimePassed - время, прошедшее с момента последнего кадра
float grandf(float fMin, float fAdd)
{
	float fRandom = float(rand()%(RAND_MAX+1))/float(RAND_MAX);
	return fMin+fAdd*fRandom;
}

void mbParticleSystemTransformFeedback::UpdateParticles(float fTimePassed)
{
	if(!bInitialized)
		return;

	glm::vec3 vUpload;

	ShaderParticlesUpdate.Use();
	ShaderParticlesUpdate.SetUniform("fTimePassed", fTimePassed);
	ShaderParticlesUpdate.SetUniform("vGenPosition", vGenPosition);
	ShaderParticlesUpdate.SetUniform("vGenVelocityMin", vGenVelocityMin);
	ShaderParticlesUpdate.SetUniform("vGenVelocityRange", vGenVelocityRange);
	ShaderParticlesUpdate.SetUniform("vGenColor", vGenColor);
	ShaderParticlesUpdate.SetUniform("vGenGravityVector", vGenGravityVector);

	ShaderParticlesUpdate.SetUniform("fGenLifeMin", fGenLifeMin);
	ShaderParticlesUpdate.SetUniform("fGenLifeRange", fGenLifeRange);

	ShaderParticlesUpdate.SetUniform("fGenSize", fGenSize);
	ShaderParticlesUpdate.SetUniform("iNumToGenerate", 0);


	fElapsedTime += fTimePassed;

	if(fElapsedTime > fNextGenerationTime)
	{
		ShaderParticlesUpdate.SetUniform("iNumToGenerate", iNumToGenerate);

		fElapsedTime -= fNextGenerationTime;

		glm::vec3 vRandomSeed = glm::vec3(grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f));

		ShaderParticlesUpdate.SetUniform("vRandomSeed", vRandomSeed);
	}

	glEnable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, uiTransformFeedbackBuffer);

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glEnableVertexAttribArray(1); // Re-enable velocity

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, uiParticleBuffer[1-iCurReadBuffer]);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, uiQuery);
	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, iNumParticles);

	glEndTransformFeedback();

	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glGetQueryObjectiv(uiQuery, GL_QUERY_RESULT, &iNumParticles);

	iCurReadBuffer = 1-iCurReadBuffer;

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}




/////////////////////////////////////////////////////////
//	Выполняет рендеринг частиц на GPU.
void mbParticleSystemTransformFeedback::RenderParticles( )
{
	if(!bInitialized)return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// это из моего дркго двигателя SDL из билбордов
	//glDepthMask(0);

	glDisable(GL_RASTERIZER_DISCARD);


	ShaderParticlesRender.Use();
	ShaderParticlesRender.SetUniform("matrices.mProj", matProjection);
	ShaderParticlesRender.SetUniform("matrices.mView", matView);

	ShaderParticlesRender.SetUniform("vQuad1", vQuad1);
	ShaderParticlesRender.SetUniform("vQuad2", vQuad2);

	// bind texture
	texture.Bind(0);
	ShaderParticlesRender.SetUniform("gSampler",0);

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glDisableVertexAttribArray(1); // Disable velocity, because we don't need it for rendering

	glDrawArrays(GL_POINTS, 0, iNumParticles);



	glDisable(GL_BLEND);
	//glDepthMask(1); //закомиченно 03,12,17 исправлено в шейлоре исключение альфа конала
}




//////////////////////////////////////////////////////////////////////////////////
// Устанавливает матрицу проекции и матрицу просмотра,
// что шейдеры преобразованной системы частиц обратной связи
// необходимость.vEye, vView, vUpVector -определение матрицы представлений
void mbParticleSystemTransformFeedback::SetMatrices(const glm::mat4* a_matProjection, glm::vec3 vEye, glm::vec3 vView, glm::vec3 vUpVector)
{
	matProjection = *a_matProjection;

	matView = glm::lookAt(vEye, vView, vUpVector);
	vView = vView-vEye;
	vView = glm::normalize(vView);
	vQuad1 = glm::cross(vView, vUpVector);
	vQuad1 = glm::normalize(vQuad1);
	vQuad2 = glm::cross(vView, vQuad1);
	vQuad2 = glm::normalize(vQuad2);
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// свойства генерации частиц
void mbParticleSystemTransformFeedback::SetGeneratorProperties(glm::vec3 a_vGenPosition, glm::vec3 a_vGenVelocityMin, glm::vec3 a_vGenVelocityMax, glm::vec3 a_vGenGravityVector, glm::vec3 a_vGenColor, float a_fGenLifeMin, float a_fGenLifeMax, float a_fGenSize, float fEvery, int a_iNumToGenerate)
{
	vGenPosition = a_vGenPosition;
	vGenVelocityMin = a_vGenVelocityMin;
	vGenVelocityRange = a_vGenVelocityMax - a_vGenVelocityMin;

	vGenGravityVector = a_vGenGravityVector;
	vGenColor = a_vGenColor;
	fGenSize = a_fGenSize;

	fGenLifeMin = a_fGenLifeMin;
	fGenLifeRange = a_fGenLifeMax - a_fGenLifeMin;

	fNextGenerationTime = fEvery;
	fElapsedTime = 0.8f;

	iNumToGenerate = a_iNumToGenerate;
}




///////////////////////////////////////////////////////
// Извлекает текущее количество частиц.
int mbParticleSystemTransformFeedback::GetNumParticles()
{
	return iNumParticles;
}
