#ifndef MB_PROGRAMMER3D_FILE_SYSTEM_HPP__
#define MB_PROGRAMMER3D_FILE_SYSTEM_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <string>
#include <vector>
//#include <tchar.h>
#include <stdio.h>
#include <iostream>
//#include <windows.h>
#include <typeindex>



class mbFileSystem
{
public:
	mbFileSystem();
	virtual ~mbFileSystem();

	const std::string& getAllPath()const;
	const std::string& getNameProga()const;
	const std::string& getFolderProj()const;
	std::vector<std::wstring> serch(std::string directory);
private:
	std::string sys_AllPath;
	std::string sys_NameProgram;
	std::string sys_FolderProject;

};





#endif
