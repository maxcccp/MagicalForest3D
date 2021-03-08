#include "mbOpenGL.hpp"

#include <GL/glew.h>

//#include <glad/glad>
#include <iostream>



using namespace std;




//-----------------------------------------------------------------------------
bool MBG::OPENGL::InitLibGLEW()
{
    #ifdef __glew_h__
    // initialize glew to setup the opengl function pointers.
    glewExperimental = GL_TRUE;
    size_t status = glewInit();
    if (status != GLEW_OK){
        std::cerr << "[error] Initialyze library GLEW..." << std::endl;
        return false;
    }


    #endif;

return true;
}
//-----------------------------------------------------------------------------
bool MBG::OPENGL::InitLibGLAD()
{
    #ifdef __glad__
        // initialize glad to setup the opengl function pointers.
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "[error] Initialyze library GLAD..." << std::endl;
            return false;
        }
    #endif
return true;
}
//-----------------------------------------------------------------------------
void MBG::OPENGL::glON(unsigned int comand)
{
    // set comand opengl.
    glEnable(comand);
}
//-----------------------------------------------------------------------------
void MBG::OPENGL::glOFF(unsigned int comand)
{
    // set comand opengl.
    glDisable(comand);
}
//-----------------------------------------------------------------------------
void MBG::OPENGL::ON_DEPTH()
{
	glEnable(GL_DEPTH_TEST);
}
//-----------------------------------------------------------------------------
void  MBG::OPENGL::RENDERER_POLIGON()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
//-----------------------------------------------------------------------------
void MBG::OPENGL::VIEWPORT(int &w, int &h)
{
	glViewport(0, 0, w, h);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
