#include "mbGENGINE.hpp"

#include <iostream>
#include "core/mbGCORE.hpp"



using namespace std;


//-------------------------------------------------------
MBG::mbGENGINE::mbGENGINE()
{
    m_GCORE = nullptr;
}
//-------------------------------------------------------
MBG::mbGENGINE::~mbGENGINE()
{
    delete m_GCORE;
    m_GCORE = nullptr;
}
//-------------------------------------------------------
bool MBG::mbGENGINE::Init(int samples,int major,int minor,std::string title)
{
    m_GCORE = new mbGCORE;
    if(m_GCORE->Init( samples, major, minor, title))
        cout << "[info] Init engine..." << endl;

return true;
}
//-------------------------------------------------------
MBG::mbWindow* MBG::mbGENGINE::Window(std::string title, int width,int height)
{
    return m_GCORE->CreateWindow(title, width, height);
}
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
