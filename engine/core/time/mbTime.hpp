#ifndef MB_PROGRAMMER3D_TIME_HPP_
#define MB_PROGRAMMER3D_TIME_HPP_
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/



namespace MBG
{


	class Clock
	{

	public:
		Clock();
		virtual~Clock();
		void mbCountFPS();

		float GetDelteTime();
		unsigned short GetFPS();
	private:
		double mbDelteTime;
		static double m_last_time;
		static unsigned short mbFrame;
	};

}
#endif


