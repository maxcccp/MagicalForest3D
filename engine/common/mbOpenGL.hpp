#ifndef MB_PROGRAMMER3D_OPENGL_HPP__
#define	MB_PROGRAMMER3D_OPENGL_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


namespace MBG
{
	namespace OPENGL
	{
		const float buffer_clear[] = { 1.0 };
		const float buffer_not_clear[] = { 0.0 };

		bool InitLibGLEW();
		bool InitLibGLAD();

        void glON(unsigned int  comand);
        void glOFF(unsigned int  comand);
		void ON_DEPTH();
		void OFF_DEPTH();
		void RENDERER_POLIGON();
		void VIEWPORT(int& w, int& h);


	}
}
#endif
