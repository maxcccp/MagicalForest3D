#ifndef MB_PROGRAMMER3D_GCORE_HPP__
#define MB_PROGRAMMER3D_GCORE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/


#include <string>


namespace MBG
{

    class mbWindow;
    class mbGCORE
    {
        public:
            mbGCORE();
            virtual ~mbGCORE();

            bool Init(int& samples,int& major,int& minor,std::string& title);
            mbWindow* CreateWindow( const std::string &title, int &width, int &height );

        private:
            mbWindow* m_Window;

    };
}
#endif
