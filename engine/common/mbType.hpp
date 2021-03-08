#ifndef MB_PROGRAMMER3D_TYPE_HPP__
#define MB_PROGRAMMER3D_TYPE_HPP__
/*
*	www.mbprogrammer.com
*	www.github.com/maxcccp
*   Copyright © 2018-2019
*/

#include <string>
#include <assert.h>
#include <iostream>


namespace MBG
{


	// std iostream
	#if defined _IOSTREAM_
		using std::cout;
		using std::endl;
	#endif

	// std map
	#if defined _MAP_
		using std::map;
	#endif
	// std vector
	#if defined _VECTOR_
		using std::vector;
	#endif

	#if defined _XSTRING_ || defined _STRING_
			using std::string;
	#endif



	// note: TYPEDEF
	typedef char			MBchar;		// size in bit: 8(1byt)  signed: -127 to 127
	typedef char			MBbyte;		// size in bit: 8(1byt)  signed: -127 to 127
	typedef unsigned char	MBubyte;	// size in bit: 8(1byt)  ansigned: 0 to 255
	typedef unsigned char	MBuhar;
	typedef short			MBshort;	// size in bit: 16(2byt) signed: -32767 to 32767
	typedef unsigned short	MBushort;	// size in bit: 16(2byt) ansigned: 0 to 65535
	typedef int				MBint;		// size in bit: 32(4byt) signed: -2,147,483,647 to 2,147,483,647
	typedef unsigned int	MBuint;		// size in bit: 32(4byt) unsigned: 0 to 4,294,967,295
	typedef long long int	MBint64;	// size in bit: 64(8byt) signed: -9,223,372,036,854,775,807 to 9,223,372,036,854,775,807
	typedef float			MBflt;		// size in bit: 32(4byt) signed float
	typedef double			MBdouble;	// size in bit: 64(8byt) signed double





	// note: DEFINED
	#define mbSizeVar(arg)		(sizeof(arg))								// learning byts?
	#define mbSizeArray(arg)	( ( sizeof(arg) )/( sizeof(arg[0]) ) )		// lerning count elements array
	#define mbDeletePtr(p)		{ if(p){delete (p); (p)=nullptr;} }			// delete point prt
	#define mbDeleteArray(p)	{ if(p){delete[] (p); (p)=nullptr;} }		// delete dynamic ptr


	#define FOR(q,n) for(int q=0;q<n;q++)
	#define SFOR(q,s,e) for(int q=s;q<=e;q++)
	#define RFOR(q,n) for(int q=n;q>=0;q--)
	#define RSFOR(q,s,e) for(int q=s;q>=e;q--)

	#define ESZ(elem) (int)elem.size()


	// note: note:передать с строку в другую си сторку байтово с помощю функции memcpy "language С"
	#define mbToText(Target_C_STR,In_c_string) memcpy(Target_C_STR, In_c_string, sizeof(In_c_string));

	// note: Переыод из числа в строку
	#define MB_NUM_IN_STRING(x) std::to_string(x)




	#define mbToCharPtr(p)        reinterpret_cast<char*>(p)                   // Cast to char*
    #define mbToWCharPtr(p)       reinterpret_cast<wchar_t*>(p)                // Cast to wchar_t*
    #define mbToConstCharPtr(p)   reinterpret_cast<const char*>(p)             // Cast to const char*
    #define mbToConstWCharPtr(p)  reinterpret_cast<const wchar_t*>(p)          // Cast to const wchar_t*
    #define mbToConstUCharPtr(p)  reinterpret_cast<const unsigned char*>(p)    // Cast to const unsigned char*
    #define mbToUCharPtr(n)       reinterpret_cast<unsigned char*>(n)          // Cast to unsigned char*
    #define mbToVoidPtr(p)        reinterpret_cast<void*>(p)                   // Cast to void*
    #define mbToConstVoidPtr(p)   reinterpret_cast<const void*>(p)             // Cast to const void*
    #define mbToIntPtr(n)         reinterpret_cast<int*>(n)                    // Cast to int*
    #define mbToConstIntPtr(p)    reinterpret_cast<const int*>(p)              // Cast to const int*
    #define mbToDoublePtr(n)      reinterpret_cast<double*>(n)                 // Cast to double*
    #define mbToConstDoublePtr(n) reinterpret_cast<const double*>(n)           // Cast to const double*
    #define mbToBoolPtr(n)        reinterpret_cast<bool*>(n)                   // Cast to bool*
    #define mbToConstBoolPtr(n)   reinterpret_cast<const bool*>(n)             // Cast to const bool*

    // General Cast
    #define toGeneralCast(T, p)            reinterpret_cast<T>(p)            // Cast to T


}
#endif
