#include "mbFileSystem.hpp"


using namespace std;

typedef unsigned char bute;











//mbFileSystem file;//"data/textures/*.png"







// Constructor
//............
mbFileSystem::mbFileSystem()
{




}








// Distructor
//...........
mbFileSystem::~mbFileSystem()
{
}




// Вернуть весь путь до бинарника (*.exe )
//........................................
const std::string& mbFileSystem::getAllPath() const
{
	return sys_AllPath;
}



// Вернуть название программмы
//............................
const std::string& mbFileSystem::getNameProga() const
{
	return sys_NameProgram;
}




// Вернуть путь с папке проекта
//.............................
const std::string& mbFileSystem::getFolderProj() const
{
	return sys_FolderProject;
}




// Для поиска файлов папок
//........................
std::vector<std::wstring> mbFileSystem::serch(std::string directory)
{
    return std::vector<std::wstring> ();
}





