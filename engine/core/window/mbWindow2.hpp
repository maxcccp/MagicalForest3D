#ifndef MBWINDOW_HPP
#define MBWINDOW_HPP
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <Windows.h>
#define GLFW_STATIC
#include <GLFW/glfw3.h>


#include <string>


#include "../shader/mbShader.hpp"
#include "../../common/mbType.hpp"
#include "../system/mbFileSystem.h"
#include "../../common/mbOpenGL.hpp"






namespace MBG
{


	class mbWindow
	{

	private:
		friend bool KeyPress(int Key);
		friend void glfw_onResize(GLFWwindow* window, int width, int height);
		friend void glfw_onMouseMove(GLFWwindow* window, double xpos, double ypos);
		friend void glfw_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
		friend void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods);
		friend void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods);

		void aux_CreateWindow(const std::string &title, int &w, int &h);

	public:
		mbWindow();
		mbWindow(const std::string& title="GameWindow", int w=800, int h=600);
		virtual ~mbWindow();

		void Show();
		void Update();
		bool Open();
		void Clear(const float* color, const float* depth);
		void AddShader(const mbShader& shaderName);


		static const int& GetWidth();
		static const int& GetHeight();
		static const bool& GetResize();
		static const double& GetMouseX();
		static const double& GetMouseY();
		static const double& GetScroll();

		static mbWindow* GetThisClass();
		static GLFWwindow* w_AppWindow;

	protected:
		static bool			m_open;
		static bool			m_Resize;
		static int			m_width;
		static int			m_height;
		static double		m_mouseX;
		static double		m_mouseY;
		static double		m_scrolY;
		static mbWindow*	m_this_class;

		BufferShader		m_update_shader;
		void KeyEventPrivate(int& key, int& action);

	};


	bool KeyPress(int Key);

	void glfw_onResize(pWin window, int width, int height);
	void glfw_onMouseMove(pWin window, double xpos, double ypos);
	void glfw_onMouseScroll(pWin window, double xoffset, double yoffset);
	void glfw_onMouseButton(pWin window, int button, int action, int mods);
	void glfw_onKey(pWin window, int key, int scancode, int action, int mods);


}
#endif//MBWINDOW_HPP
