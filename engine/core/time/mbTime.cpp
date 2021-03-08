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



// Посчитать FPS & DeltaTime
void MBG::Clock::mbCountFPS()
{

	// текущее время
	double currentTime = glfwGetTime();

	// считаем кадры
	globalFrame++;

	// вычитаем время прошедшое с последнего кадра
	double result = currentTime - m_last_time;
	
	// как только прошла одна секунда
	if (result >= 1.0)
	{
		// присваеваем переменной сколько кадров за 1 сек
		mbFrame = globalFrame;
		// дельта тайм для привязки игры ко времени
		mbDelteTime = 10.000 / (double)globalFrame;
		// сброс счетчика кадра
		globalFrame = 0;
		// обновить прошедшое время
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
