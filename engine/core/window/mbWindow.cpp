#include "mbWindow.hpp"



#include "mbKey.hpp"
#include "../texture/stb_image.h"
#include "../../common/mbType.hpp"

#include "../../../resources.hpp"

using namespace std;






namespace MBG
{

	/*! note: Static Variebles. */
	bool mbWindow::m_open               = true;
	bool mbWindow::m_Resize             = false;
	mbWindow* mbWindow::m_this_class    = nullptr;
	GLFWwindow* mbWindow::w_AppWindow   = nullptr;
	double mbWindow::m_mouseX = 0.0;
	double mbWindow::m_mouseY = 0.0;
	double mbWindow::m_scrolY = 0.0f;

	int mbWindow::m_width = 0;
	int mbWindow::m_height = 0;
	int mbWindow::m_cursor = GLFW_CURSOR_DISABLED; // скрыть курсор


    BufferShader mbWindow::m_update_shader = BufferShader();

	void mbInformationEngineConsole()
	{

        // note: Information to Console.

		/*---------------------------------------------------------------------------------------*/
		/*--------------------------- INFORMATION RENDERER --------------------------------------*/
		const char* Developer       = "Max";
		const char* Site            = "mbprogrammer.com";
		const char* GitHub          = "github.com/maxcccp";
		const char* Vender          = (const char*)glGetString(GL_VENDOR);
		const char* Renderer        = (const char*)glGetString(GL_RENDERER);
		const char* VersionOpenGL   = (const char*)glGetString(GL_VERSION);
		const char* VersionGLSL     = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

		std::cout << "=======================================================" << std::endl;
		std::cout << "\t\t\tInformation:" << std::endl;
		printf("Vendor:          %s\n", Vender);
		printf("Renderer:        %s\n", Renderer);
		printf("Version OpenGL:  %s\n", VersionOpenGL);
		printf("Version GLSL:    %s\n", VersionGLSL);
		std::cout << std::endl;
		printf("After:		%s\n", Developer);
		printf("Site-After:	%s\n", Site);
		printf("GitHab-After:	%s\n", GitHub);

		std::cout << "=======================================================" << std::endl << std::endl;

		std::cout << "################## Logs work program: #################" << std::endl << std::endl;

		/*------------------------------ END INFORMATION RENDERER ----------------------------*/
	}



    //-----------------------------------------------------------------------------------------------------------
	mbWindow::mbWindow()
	{
	}
	//-----------------------------------------------------------------------------------------------------------
	mbWindow::~mbWindow()
	{
		glfwSetWindowShouldClose(mbWindow::w_AppWindow, true);
	}
    //-----------------------------------------------------------------------------------------------------------
	bool mbWindow::Open()
	{
        // note: open or close Window.

		// note: Если пользователь захотел показать курсор что бы выйти из сотояние заблокированного курсора.
		if ( glfwGetKey(w_AppWindow, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
			// показать курсор
			m_cursor = GLFW_CURSOR_NORMAL;
			glfwSetInputMode( w_AppWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
		}


		return m_open; // glfwWindowShouldClose(w_AppWindow) - возвращает значение флага закрытия указанного окна. int;
	}
    //-----------------------------------------------------------------------------------------------------------
	void mbWindow::Clear(const float * color, const float * depth)
	{

        // note: Современная очистка экрана.

		OPENGL::VIEWPORT(m_width, m_height);
		glClearBufferfv(GL_COLOR, 0, color);
		glClearBufferfv(GL_DEPTH, 0, depth);
	}
    //-----------------------------------------------------------------------------------------------------------
	void mbWindow::AddShader(const mbShader& shaderName)
	{
        // note: Добавления шейдора для обновления в процессе работы.

		m_update_shader.push_back(shaderName);
	}
    //-----------------------------------------------------------------------------------------------------------
	void mbWindow::Show()
	{
        // note: Показать окно.
		glfwShowWindow(w_AppWindow);
	}
    //-----------------------------------------------------------------------------------------------------------
	void mbWindow::Update()
	{

        // note: Обноввление окна.

		// Тут все переменные которые нужно обнулить!!!
		m_scrolY = 0.0f;
		m_Resize = false;

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(w_AppWindow);
		glfwPollEvents();

	}
    //-----------------------------------------------------------------------------------------------------------
	void mbWindow::KeyEventPrivate(int& key, int& action)
	{

        // note: Событие встроеных кнопок один раз которые нажаты.


		// note: для различных предупреждений
		static int message = 0;

		if (key == mbkey::KEY_0 && action == GLFW_PRESS)
		{

			if (!m_update_shader.empty())
            {
                for(size_t i=0; i < m_update_shader.size(); i++)
                    m_update_shader[i].Update();
			}
			else// для вывода информации когда клиенту не понятно!!!
			{
				if (message == 0) {
					printf("There are none to update the shader!\n");
					message++;
				}
				else if (message == 1) {
					printf("Добавь шейдор для обнавления!\n");
					message = 0;
				}
             }
          }
     }
    //-----------------------------------------------------------------------------------------------------------
	bool mbWindow::Create(const std::string &title, int &w, int &h)
	{

        // note: Вспомогательная функция создание главного окна программы.

		if (!m_this_class) m_this_class = this;
		else cout << "Class mbWindow attrach!" << endl;

		m_width = w;
		m_height = h;

		// если еще указательне указывает на какое либо окно то создаем.
		if (!w_AppWindow)
		{
			// note: создание окна. С проверкой создано оно или нет.
			w_AppWindow = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
			if (w_AppWindow == NULL)
			{
				std::cout << "Failed to create GLFW3 window." << std::endl;
				glfwTerminate();
			}

			// note: контекст.
			glfwMakeContextCurrent(w_AppWindow);


            // note: create icon app window.
			GLFWimage logo;
            logo.pixels = stbi_load( MF3D_PATN_IMG_PNG , &logo.width, &logo.height, nullptr, 4);
            if( logo.pixels ){
                glfwSetWindowIcon( w_AppWindow, 1, &logo );
                stbi_image_free( logo.pixels );
            }
            else{
                cout << " Loaded not logo!!!" << endl;
                stbi_image_free( logo.pixels );
            }

			// note: можете получить текущее состояние видимости с помощью
			//int visible = glfwGetWindowAttrib(w_AppWindow, GLFW_VISIBLE);

			// подключаем функции обратного вызова.
			glfwSetWindowCloseCallback(w_AppWindow, glfw_onWindowClose);
			glfwSetKeyCallback(w_AppWindow,	glfw_onKey);
			//glfwSetFramebufferSizeCallback(w_AppWindow, glfw_onResize);
			//glfwSetWindowSizeCallback(w_AppWindow,	glfw_onResize);
			glfwSetWindowSizeCallback(w_AppWindow,	glfw_onResize);


			glfwSetCursorPosCallback(w_AppWindow,	glfw_onMouseMove);
			glfwSetMouseButtonCallback(w_AppWindow, glfw_onMouseButton);
			glfwSetScrollCallback(w_AppWindow,		glfw_onMouseScroll);
			glfwSetCursorEnterCallback(w_AppWindow, glfw_onCursorEnter);
			// Пользователь может изменить размер окна без ограничений размера, но размер будет ограничен,
			// чтобы поддерживать соотношение сторон.
            //glfwSetWindowAspectRatio(w_AppWindow, 16, 9);

			// не показывать курсор и зафиксировать курсор в  центре окне glfw заботится об этом.
			glfwSetInputMode(w_AppWindow, GLFW_CURSOR, m_cursor);

			/*------------------------------------------------------------------------------------*/
			/*------------------------------- SETTINGS OPEN-GL -----------------------------------*/

			// note: Для подключения расширений opengl.
			OPENGL::InitLibGLEW();

			OPENGL::VIEWPORT(m_width, m_height);
			// note: Включить проверку глубины
			OPENGL::ON_DEPTH();
			// note: Примите фрагмент, если он ближе к камере, чем предыдущий(используемое для сравнения буфера глубины , определяет условия, при которых будет рисоваться пиксель.)
			glDepthFunc(GL_LESS);
			// note: Setup some OpenGL options
			glEnable(GL_DEPTH_CLAMP);

			// note: Enable blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// note: показать каркас треугольников
			//OPENGL::RENDERER_POLIGON();

			/*-------------------------------- END SETINGS OPEN-GL -------------------------------------*/

			// Вывести информацию в консоль о двигатели.
			mbInformationEngineConsole();

		}
		else
		{
            return false;
        }

		return true;
	}
    //-----------------------------------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------------------------------
	const int& mbWindow::GetWidth()
	{
		return m_width;
	}
    //-----------------------------------------------------------------------------------------------------------
	const int&mbWindow::GetHeight()
	{
		return m_height;
	}
    //-----------------------------------------------------------------------------------------------------------
	const bool& mbWindow::GetResize()
	{
		return m_Resize;
	}
    //-----------------------------------------------------------------------------------------------------------
	const double& mbWindow::GetMouseX()
	{
		return m_mouseX;
	}
    //-----------------------------------------------------------------------------------------------------------
	const double& mbWindow::GetMouseY()
	{
		return m_mouseY;
	}
    //-----------------------------------------------------------------------------------------------------------
	const double& mbWindow::GetScroll()
	{
		return m_scrolY;
	}
    //-----------------------------------------------------------------------------------------------------------
	const int& mbWindow::GetCursorState()
	{
		return m_cursor;
	}
    //-----------------------------------------------------------------------------------------------------------
	//mbWindow* mbWindow::GetThisClass()
	//{
	//	return m_this_class;
	//}
    //-----------------------------------------------------------------------------------------------------------



    //-----------------------------------------------------------------------------------------------------------
	void glfw_onWindowClose(GLFWwindow* window)
	{
		mbWindow::m_open = false;
	}
    //-----------------------------------------------------------------------------------------------------------
	void glfw_onCursorEnter(GLFWwindow* window, int entered)
	{
        // mb_software: Получать уведомления, когда курсор входит или покидает клиентскую область окна.

		// Курсор введен в клиентскую область окна
		if (entered)
		{


		}
		// Курсор покидает клиентскую область окна.
		else
		{

		}
	}
    //-----------------------------------------------------------------------------------------------------------
	void glfw_onFrameBufferSize(GLFWwindow* window, int w, int h)
	{

        /*  mb_software:
        *	OpenGL работает с пикселями. Размер, который вы передаете glViewport, например, должен быть в пикселях.
        *	На некоторых машинах координаты экрана и пиксели одинаковы, а на других их не будет. Существует второй
        *	набор функций для извлечения размера в пикселях фреймбуфера окна.
        *
        */

		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		//MBG::OPENGL::VIEWPORT(w, h);

	}
    //-----------------------------------------------------------------------------------------------------------
	void glfw_onResize(GLFWwindow* window, int width, int height)
	{
        /*	mb_software:
        *	glfw: всякий раз, когда размер окна изменяется (по изменению размера ОС или пользователя),
        *	эта функция обратного вызова выполняет.
        */

		mbWindow::m_width = width;
		mbWindow::m_height = height;


		mbWindow::m_Resize = true;
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		MBG::OPENGL::VIEWPORT(width, height);
	}
    //-----------------------------------------------------------------------------------------------------------
	void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
        // mb_software: glfw:  всякий раз, когда нажимаются кнопки клавиатуры выполняется эта функция.
		//mbWindow::GetThisClass()->KeyEventPrivate(key, action);
		MBG::mbWindow::KeyEventPrivate(key, action);

	}
    //-----------------------------------------------------------------------------------------------------------
	void glfw_onMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
        // mb_software: glfw: всякий раз, когда мышка перемещаеться выполняется эта функция.

		mbWindow::m_mouseX = xpos;
		mbWindow::m_mouseY = ypos;
		//cout << xpos << "X" << ypos << endl;
	}
    //-----------------------------------------------------------------------------------------------------------
	void glfw_onMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
        // mb_software: glfw: всякий раз, когда мышка скролинг колеса.

		mbWindow::m_scrolY = yoffset;
	}
    //------------------------------------------------------------------------------------------------------------
	void glfw_onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{

        // mb_software: glfw: всякий раз, когда нажата кнопка мыши.

		// когда нажата правая клавиша мышки.
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {

		}

		// когда нажата правая клавиша мышки.
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

			// снова поменять сотояние курсора скрыть и отключить.
			if (mbWindow::m_cursor == mbStateCursor::normal) {
				mbWindow::m_cursor = mbStateCursor::disabled;
				glfwSetInputMode(mbWindow::w_AppWindow, GLFW_CURSOR, mbWindow::m_cursor);
			}



		}
	}
    //------------------------------------------------------------------------------------------------------------
	bool KeyPress(int key)
	{
        // mb_software: События нажание на клавишу.

		if (glfwGetKey(mbWindow::w_AppWindow, key) == GLFW_PRESS)
			return true;

		return false;
	}
    //------------------------------------------------------------------------------------------------------------
	bool BtnPress(int btn)
	{
        // mb_software: События нажание на кнопку мышки.

		if (glfwGetMouseButton(mbWindow::w_AppWindow, btn) == GLFW_PRESS)
			return true;

		return false;
	}
    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------


} // end namespace mbg...
