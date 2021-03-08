#ifndef MB_PROGRAMMER3D_GENGINE_HPP__
#define MB_PROGRAMMER3D_GENGINE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


//  Family GCC in Linux: -lglfw -lGLEW  -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -lfreetype -lassimp

// Microsoft Visual Studio
#if defined _WIN32 && _MSC_VER
	// WARNINGS Visual Studio
	#ifndef  _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS
	#endif

	#pragma comment(lib,"glew32.lib")
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glfw3.lib")
	#pragma comment(lib,"freetype.lib")
	#pragma comment(lib,"assimp.lib")
#endif


// mbGEngine
#include "core/window/mbWindow.hpp"
#include "core/shader/mbShader.hpp"
#include "core/model/mbMesh.hpp"
#include "core/model/mbModel.hpp"
#include "core/font/mbFont.hpp"
#include "core/camera/mbCameraFree.hpp"
#include "core/script/mbGameSctipt.hpp"
#include "core/texture/mbImage.hpp"
#include "core/time/mbTime.hpp"
#include "core/shape/mbQuad2d.hpp"
#include "core/texture/mbShadowMap.hpp"
#include "core/buffer/mbBuffer.hpp"
#include "core/shape/mbObject.hpp"
#include "core/particle/mbParticleSystemTF.hpp"


#include "common/mbColor.hpp"
#include "common/mbOpenGL.hpp"




namespace MBG
{



    class mbGCORE;
    class mbGENGINE
    {
        public:
            mbGENGINE();
            virtual ~mbGENGINE();

            bool Init(int samples=2,int major=3,int minor=3,std::string title="mbGENGINE");
            mbWindow* Window(std::string title="mbGENGINE", int w=500,int h=500);
        private:
            mbGCORE* m_GCORE;
    };
}

#endif
