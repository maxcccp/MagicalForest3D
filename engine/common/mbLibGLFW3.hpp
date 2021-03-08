#ifndef MB_PROGRAMMER3D_LIBGLFW3_HPP__
#define MB_PROGRAMMER3D_LIBGLFW3_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace MBG
{
    namespace mbGLFW3
    {
        class GLFWwindow;
        typedef GLFWwindow* pWINDOW;
        typedef void (* ProcFuncResizeWindow)(GLFWwindow*, int width, int height);

        void mbProcWindowRes(GLFWwindow* win, int width, int height);

        void mbProcessWindowResize(GLFWwindow* window , ProcFuncResizeWindow func);

    };


    class mbLibGLFW3
    {
        public:
            mbLibGLFW3();
            virtual ~mbLibGLFW3();

        protected:
        private:

    };

}
#endif
