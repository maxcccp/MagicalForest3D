#include "mbLibGLFW3.hpp"


#include <iostream>


// mb-soft: Constructor.
MBG::mbLibGLFW3::mbLibGLFW3()
{
    //ctor
}


// mb-soft: Distructor.
MBG::mbLibGLFW3::~mbLibGLFW3()
{
    //dtor
}


void MBG::mbGLFW3::mbProcWindowRes(GLFWwindow* win, int width, int height)
{
    std::cout <<"Resize"<< std::endl;
}


void MBG::mbGLFW3::mbProcessWindowResize(GLFWwindow* window , ProcFuncResizeWindow func)
{
    //glfwSetWindowSizeCallback(window,	(GLFWwindowsizefun)func);
}
