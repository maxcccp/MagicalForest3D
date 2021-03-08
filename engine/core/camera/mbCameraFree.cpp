#include "mbCameraFree.hpp"


#include "../window/mbWindow.hpp"

using namespace std;




namespace MBG
{



	// (NOTE) mb_software: ����������� ���������� ��� ������.
	float MBG::mbCameraFree::PosX = 0.0f;
	float MBG::mbCameraFree::PosY = 0.0f;





	// (NOTE) mb_software: ����������� ��������� ������.
	mbCameraFree::mbCameraFree(float x, float y, float z)
		:mbCamera(glm::vec3(x, y, z))
	{
		// ����� ���� ��� ��������� ������� ���� � �����.
		lastX = (float)(mbWindow::GetWidth() >> 1);
		lastY = (float)(mbWindow::GetHeight() >> 1);

		// ������� ����������.
		m_view = glm::lookAt(this->m_Position, this->m_Position + this->m_Front, this->m_Up);
		// ������� ��������.
		m_projection = glm::perspective(glm::radians(this->m_Zoom), (float)mbWindow::GetWidth() / (float)mbWindow::GetHeight(), 0.1f, 1000.0f);

	}



	// (NOTE) mb_software: ���������� ��������� ������.
	mbCameraFree::~mbCameraFree()
	{}




	// (NOTE) mb_software: ���������� ���������  ������.
	void mbCameraFree::Translate(const float& deltaTime)
	{

		//  ���� ������ ������ � ��������� �������� � �������.
		if (mbWindow::GetCursorState() == mbStateCursor::disabled)
		{

			float speedMove = 0.7f;

			// MOUSE KEYBORD MOVED //
			if (glfwGetKey(mbWindow::w_AppWindow, GLFW_KEY_W) == GLFW_PRESS)
			{
				this->Keyboard(MBG::FORWARD, speedMove*deltaTime);
			}
			if (glfwGetKey(mbWindow::w_AppWindow, GLFW_KEY_S) == GLFW_PRESS)
			{
				this->Keyboard(MBG::BACKWARD, speedMove*deltaTime);
			}
			if (glfwGetKey(mbWindow::w_AppWindow, GLFW_KEY_A) == GLFW_PRESS)
			{
				this->Keyboard(MBG::LEFT, speedMove*deltaTime);
			}
			if (glfwGetKey(mbWindow::w_AppWindow, GLFW_KEY_D) == GLFW_PRESS)
			{
				this->Keyboard(MBG::RIGHT, speedMove*deltaTime);
			}


			// MOUSE MOVE //
			float xpos = (float)mbWindow::GetMouseX();
			float ypos = (float)mbWindow::GetMouseY();


			float xoffset = (xpos - lastX) * 0.2f;
			float yoffset = (lastY - ypos) * 0.2f; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			// ������� ������ � ������� �����.
			MouseMovement(xoffset, yoffset);

			// ���� ��������� �������������� ������ �����.
			MouseScroll((float)mbWindow::GetScroll());

			// update ������� ����������.
			m_view = glm::lookAt(this->m_Position, this->m_Position + this->m_Front, this->m_Up);
			// �������� ���� ������ ��� ������� ��������� ������.
			m_projection = glm::perspective(glm::radians(this->m_Zoom), (float)mbWindow::GetWidth() / (float)mbWindow::GetHeight(), 0.1f, 1000.0f);

		}


		// ���� ��������� ��������� �������� ����.
		if (mbWindow::GetResize())
			m_projection = glm::perspective(glm::radians(this->GetZoom()), (float)mbWindow::GetWidth() / (float)mbWindow::GetHeight(), 0.1f, 1000.0f);


		// ������������� ������ �� ������ ������
		//glfwSetCursorPos(mbWindow::w_AppWindow, lastX, lastY);

	}



	// (NOTE) mb_software: ������� ������� ���������.
	const glm::mat4& mbCameraFree::GetView()
	{
		return m_view;
	}


	// (NOTE) mb_software: �������������� ���������� ������� ��������
	const glm::mat4& mbCameraFree::GetProj()
	{
		return m_projection;
	}



}
