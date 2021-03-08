/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include "engine/mbGENGINE.hpp"




using namespace std;
using namespace glm;
using namespace MBG;





// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
int SAMPLER = 8;
int MAJOR = 4;
int MINOR = 3;


int main( int atgc, char* argv[] )
{
	//MB_InitPython(argv);

	mbGENGINE engine;
	engine.Init(SAMPLER,MAJOR,MINOR);
	mbWindow* win = engine.Window("Engine-MagicalForest3D", SCR_WIDTH, SCR_HEIGHT);

	mbCameraFree freeCamera( -2.0f, 2.0f, 2.0f );
	Clock clock;
	vec3 Light(-1.0f, 5.0f, 2.0f);

	// note: loading shaders Default
	mbShader ShaderText; ShaderText.Loading( "data/glsl/Font/text" );
	// glsl::mbShader ModelShader;
	// ModelShader.Loading("data/glsl/Model/model");
	mbShader ShaderNormal; ShaderNormal.Loading( "data/glsl/Normal/normal_mapping" );

	win->AddShader(ShaderNormal);


	// loading shaders Shadow
	mbShader ShaderQuad;        ShaderQuad.Loading( "data/glsl/Shadow/QuadDepth" );
	mbShader ShaderDepth;       ShaderDepth.Loading( "data/glsl/Shadow/shadowDepth" );
	mbShader ShaderShadowMap;   ShaderShadowMap.Loading( "data/glsl/Shadow/shadowMapping" );

    mbShadowMap ShadowMap;
    ShadowMap.CreateShadowMap(1024,1024);


	// note: loadind models
	// mbFont FontSansation("data/font/sansation.ttf", ShaderText);
	mbModel modelSponza( "data/objects/sponza/sponza.obj", vec3( 0.0f ), 0.03f );
	mbModel modelSolder( "data/objects/cyborg/cyborg.obj", vec3( 5.0f,0.0f,0.0f ), 1.0f );
	mbModel modelmbRobot( "data/objects/fuel_can/fuel_can.obj", vec3( 11.0f, 0.0f, 0.0f ), 0.02f );

	mbModel shaderBall( "data/objects/shaderBall/matBallGlass.obj", vec3( -12.0f, 2.3f, -7.0f ), 1.0f );
	mbModel shaderBall2( "data/objects/shaderBall/matBallRocks.obj", vec3( -2.0f, 2.3f, -7.0f ), 1.0f );
	mbModel shaderBall3( "data/objects/shaderBall/matBallMarbleTiles.obj", vec3( 10.0f, 2.3f, -7.0f ), 1.0f );
	mbModel shaderBall4( "data/objects/shaderBall/matBallRedPlastic.obj", vec3( 20.0f, 2.3f, -7.0f ), 1.0f );
	mbModel shaderBall5( "data/objects/shaderBall/matBallRustedIron.obj", vec3( -24.0f, 2.3f, -7.0f ), 1.0f );

	mbPlaneObj plane( "data/textures/plane/Sphere", vec3( 2.0f, 0.5f, 0.0f ) );

	mbModel box_mb1("data/objects/box/box.obj", vec3( -12.0f, 1.0f, -6.0f ), 1.0f );
	mbModel box_mb2("data/objects/box/box.obj", vec3( -2.0f, 1.0f, -6.0f ), 1.0f );
	mbModel box_mb3("data/objects/box/box.obj", vec3( 10.0f, 1.0f, -6.0f ), 1.0f );
	mbModel box_mb4("data/objects/box/box.obj", vec3( 20.0f, 1.0f, -6.0f ), 1.0f );
	mbModel box_mb5("data/objects/box/box.obj", vec3( -24.0f, 1.0f, -6.0f ), 1.0f );
	//mbCube cube("data/textures/container2", glm::vec3(-8.0f, 1.0f, -1.0f));
	//mbCube cube2("data/textures/container2", glm::vec3(0.0f, 1.0f, -5.0f));

	// Quad
	mbQuad2d quad;
	quad.CreateQuad2d(vec2(1.5f, -1.5f),0.4f);

	mbQuad2d quadNDC;
	quadNDC.CreateQuad2d(vec2(50.0f),50.0f);


	mbParticleSystemTransformFeedback psMainParticleSystem;
	psMainParticleSystem.InitalizeParticleSystem();

	psMainParticleSystem.SetGeneratorProperties(
		glm::vec3(0.0f, 40.0f, 0.0f),			// Там, где образуются частицы
		glm::vec3(-15, -10.0, -15),				// Minimal velocity vec3(-5, 0, -5)
		glm::vec3(15, 10.0, 15),				// Maximal velocity vec3(5, 20, 5)
		glm::vec3(1, -2.0, 1),					// Сила тяжести, применяемая к частицам -1
		glm::vec3(1.0f, 1.0f, 1.0f),			// Color (light blue)
		3.0f,									// Минимальный срок службы в секундах 1.5
		6.0f,									// Максимальный срок службы в секундах 3.0
		0.05f,									// Размер
		0.02f,									// Постепенно каждые 0,05 секунды
		40);									// И порождают 30 частиц




	win->Show();





	/* GAME LOOP */
	while ( win->Open() )
	{

		clock.mbCountFPS();

		win->Clear(MBG::COLOR::grey, MBG::OPENGL::buffer_clear);

		// move keyborb camera
		freeCamera.Translate(clock.GetDelteTime());


       // ShaderDepth.Use();
        //ShadowMap.Write(&ShaderDepth);




		// RENDERER	//

		// Text
		//Text(FontSansation, "mbGENGINE", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		//Text(FontSansation, "mbprogrammer.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
		//Text(FontSansation, "fps: " + MB_NUM_IN_STRING(clock.GetFPS()), 25.0f, 570.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
		//Text(FontSansation, "particle: "+MB_NUM_IN_STRING(psMainParticleSystem.GetNumParticles()), 25.0f, 550.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));

		// particle system
		psMainParticleSystem.SetMatrices(&freeCamera.GetProj(), freeCamera.GetPosition(), freeCamera.GetDirection(), freeCamera.GetUp());
		psMainParticleSystem.UpdateParticles(clock.GetDelteTime()*0.1f);
		psMainParticleSystem.RenderParticles();


		// Normal Shaders
		ShaderNormal.Use();
		ShaderNormal.SetUniform("projection", freeCamera.GetProj());
		ShaderNormal.SetUniform("view", freeCamera.GetView());
		ShaderNormal.SetUniform("light.ambient",vec3(0.2f, 0.2f, 0.2f) );
		ShaderNormal.SetUniform("light.diffuse",vec3(0.3f, 0.3f, 0.3f) );
		ShaderNormal.SetUniform("light.specular",vec3(0.3f, 0.3f, 0.3f) );
		ShaderNormal.SetUniform("light.position", Light);
		ShaderNormal.SetUniform("viewPos", freeCamera.GetPosition());
		ShaderNormal.SetUniform("lightPos", Light);
		// draw objects
		modelSponza.Draw(ShaderNormal);
		modelSolder.Draw(ShaderNormal);
		shaderBall.Draw(ShaderNormal);
		//plane.Draw(ShaderNormal);
		plane.Draw(ShaderNormal);

		box_mb1.Draw( ShaderNormal );
        box_mb2.Draw( ShaderNormal );
        box_mb3.Draw( ShaderNormal );
        box_mb4.Draw( ShaderNormal );
        box_mb5.Draw( ShaderNormal );

		modelmbRobot.Draw(ShaderNormal);
		shaderBall2.Draw(ShaderNormal);
		shaderBall3.Draw(ShaderNormal);
		shaderBall4.Draw(ShaderNormal);
		shaderBall5.Draw(ShaderNormal);

		//ShadowMap.End();

		//Text(FontSansation, "mbGENGINE", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        //Text(FontSansation, "fps: " + MB_NUM_IN_STRING(clock.GetFPS()), 25.0f, 570.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));


		//ShaderQuad.Use();
		//ShaderQuad.SetUniform("depthMap",0);
		//quadNDC.Render(ShaderQuad,ShadowMap.GetDepthTextureID());



        // UPDATE
		win->Update();

	}


	//MB_EndPython();
	//ExitBulletPhysics();
	return 0;
}




// Create TextureFBO
unsigned int CreateFBOTexture(unsigned int& depthMapFBO,const unsigned int& SHADOW_WIDTH, const unsigned int& SHADOW_HEIGHT)
{

	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// 2 method
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//// comparison mode of the shadow map
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return depthMap;
}


// Create TextureFBO
unsigned int CreateFBOTextureTWO(const unsigned int& SHADOW_WIDTH, const unsigned int& SHADOW_HEIGHT)
{

	assert(SHADOW_WIDTH);
	assert(SHADOW_HEIGHT);

	unsigned int  texture;

	// запросим у OpenGL свободный индекс текстуры
	glGenTextures(1, &texture);

	// сделаем текстуру активной
	glBindTexture(GL_TEXTURE_2D, texture);

	// установим параметры фильтрации текстуры - линейная фильтрация
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// установим параметры "оборачиваниея" текстуры - отсутствие оборачивания
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// необходимо для использования depth-текстуры как shadow map
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

	// соаздем "пустую" текстуру под depth-данные
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	// проверим на наличие ошибок
	//OPENGL_CHECK_FOR_ERRORS();

	return texture;

}




