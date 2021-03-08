#include "mbTime.hpp"


#include <GLFW/glfw3.h>
#include <iostream>


using namespace std;


// static variables
static unsigned short globalFrame = 0;
unsigned short MBG::Clock::mbFrame = 0;
double MBG::Clock::m_last_time = 0.0;





/*! mb_software: Constructor. */
MBG::Clock::Clock()
{

}

/*! mb_software: Distructor. */
MBG::Clock::~Clock()
{

}



// ��������� FPS & DeltaTime
void MBG::Clock::mbCountFPS()
{

	// ������� �����
	double currentTime = glfwGetTime();

	// ������� �����
	globalFrame++;

	// �������� ����� ��������� � ���������� �����
	double result = currentTime - m_last_time;
	
	// ��� ������ ������ ���� �������
	if (result >= 1.0)
	{
		// ����������� ���������� ������� ������ �� 1 ���
		mbFrame = globalFrame;
		// ������ ���� ��� �������� ���� �� �������
		mbDelteTime = 10.000 / (double)globalFrame;
		// ����� �������� �����
		globalFrame = 0;
		// �������� ��������� �����
		m_last_time = currentTime;

		//mbDelteTime =  (result / 60.0);
	}
}


// get deltatime
float MBG::Clock::GetDelteTime()
{

	return (float)mbDelteTime;
}


// get fps cadrs
unsigned short MBG::Clock::GetFPS()
{
	return mbFrame;
}
