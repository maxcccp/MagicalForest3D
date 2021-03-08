#include "mbGameSctipt.hpp"



MBG::mbGameSctipt::mbGameSctipt()
{
}


MBG::mbGameSctipt::~mbGameSctipt()
{
}



// MB_PYTHON_SCRIPT*
#ifdef MB_PYTHON_SCRIPT

void MB_InitPython(char** _argv)
{
	Py_SetProgramName((wchar_t*)_argv[0]);

	// set PYTHONHOME=C:\Python2.x 3.x(откуда запускать интерпретатор )
	Py_SetPythonHome(Py_GetPath());
	Py_Initialize();
	PyRun_SimpleString("print( 'Init Python C++') ");
}

void MB_EndPython()
{
	Py_Finalize();
}


#endif//MB_PYTHON_SCRIPT