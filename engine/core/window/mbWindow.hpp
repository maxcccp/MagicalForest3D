#ifndef MB_PROGRAMMER3D_WINDOW_HPP__
#define MB_PROGRAMMER3D_WINDOW_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../shader/mbShader.hpp"
#include "../system/mbFileSystem.hpp"
#include "../../common/mbOpenGL.hpp"
#include"../../common/mbLibGLFW3.hpp"


namespace MBG
{

	enum mbStateCursor
	{
		normal = 212993,
		hidden,
		disabled

	};




	class mbWindow
	{

	private:
		friend bool BtnPress(int btn);
		friend bool KeyPress(int key);
		friend void glfw_onWindowClose(GLFWwindow* window);
		friend void glfw_onCursorEnter(GLFWwindow* window, int entered);
		friend void glfw_onFrameBufferSize(GLFWwindow* window, int w, int h);
		friend void glfw_onResize(GLFWwindow* window, int width, int height);
		friend void glfw_onMouseMove(GLFWwindow* window, double xpos, double ypos);
		friend void glfw_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
		friend void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods);
		friend void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);

	public:
		mbWindow();
		virtual ~mbWindow();

		bool Create(const std::string &title, int &w, int &h);
		void Show();
		void Update();
		bool Open();
		void Clear(const float* color, const float* depth);
		void AddShader(const mbShader& shaderName);


		static const int&       GetWidth();
		static const int&       GetHeight();
		static const bool&      GetResize();
		static const double&    GetMouseX();
		static const double&    GetMouseY();
		static const double&    GetScroll();
		static const int&       GetCursorState();

		static GLFWwindow* w_AppWindow;

	private:

		static bool			m_open;
		static bool			m_Resize;
		static int			m_width;
		static int			m_height;
		static int			m_cursor;
		static double		m_mouseX;
		static double		m_mouseY;
		static double		m_scrolY;
		static mbWindow*	m_this_class;

		static BufferShader		m_update_shader;
		static void KeyEventPrivate(int& key, int& action);

	};

    //--------------------------------------------------------------------------------
	bool KeyPress(int key);
	bool BtnPress(int btn);
	void glfw_onWindowClose(GLFWwindow* window);
	void glfw_onCursorEnter(GLFWwindow* window, int entered);
	void glfw_onFrameBufferSize(GLFWwindow* window, int w, int h);
	void glfw_onResize(GLFWwindow* window, int width, int height);
	void glfw_onMouseMove(GLFWwindow* window, double xpos, double ypos);
	void glfw_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods);
	void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	//--------------------------------------------------------------------------------


}
#endif
