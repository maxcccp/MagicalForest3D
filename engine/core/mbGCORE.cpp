#include "mbGCORE.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window/mbWindow.hpp"



//-------------------------------------------------------------
MBG::mbGCORE::mbGCORE()
{
    this->m_Window = nullptr;
}
//-------------------------------------------------------------
MBG::mbGCORE::~mbGCORE()
{
   delete m_Window;
   m_Window = nullptr;
}
//-------------------------------------------------------------
bool MBG::mbGCORE::Init(int& samples,int& major,int& minor,std::string& title)
{
    // initialize library glfw3.
    if (!glfwInit()){
         fprintf(stderr, "[error] Initialize library GLFW3...\n");
         return false;
     }
    // settings.
    glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	return true;

}
//-------------------------------------------------------------
MBG::mbWindow* MBG::mbGCORE::CreateWindow(const std::string &title, int &width, int &height)
{
    m_Window = new mbWindow;
    if( m_Window->Create( title,width,height ) )
        return m_Window;

return nullptr;
}
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
