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




// ������� ���� ���� �� ��������� (*.exe )
//........................................
const std::string& mbFileSystem::getAllPath() const
{
	return sys_AllPath;
}



// ������� �������� ����������
//............................
const std::string& mbFileSystem::getNameProga() const
{
	return sys_NameProgram;
}




// ������� ���� � ����� �������
//.............................
const std::string& mbFileSystem::getFolderProj() const
{
	return sys_FolderProject;
}




// ��� ������ ������ �����
//........................
std::vector<std::wstring> mbFileSystem::serch(std::string directory)
{
    return std::vector<std::wstring> ();
}





