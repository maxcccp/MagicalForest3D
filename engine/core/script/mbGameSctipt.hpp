#ifndef MB_PROGRAMMER3D_GAME_SCRIPT_HPP__
#define MB_PROGRAMMER3D_GAME_SCRIPT_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

//#define MB_PYTHON_SCRIPT
//#define MB_LUA_SCRIPT



//....................................
// inicialize macros MB_PYTHON_SCRIPT
//....................................
#ifdef MB_PYTHON_SCRIPT

#include <Python.h>

// link library VisualStudio...
#if defined (DEBUG) && defined (_MSC_VER)
	#pragma comment(lib,"python35_d.lib")
#elif defined(NDEBUG)&& defined(_MSC_VER)
	#pragma comment(lib,"python35.lib")
#endif


// function diclaration
void MB_InitPython(char** _argv);
void MB_EndPython();


#endif//END MB_PYTHON_SCRIPT





//.................................
// inicialize macros MB_LUA_SCRIPT
//.................................
#if defined MB_LUA_SCRIPT



#endif//END MB_LUA_SCRIPT


namespace MBG
{

	class mbGameSctipt
	{
	public:
		mbGameSctipt();
		virtual ~mbGameSctipt();

	private:

	};

}
#endif
