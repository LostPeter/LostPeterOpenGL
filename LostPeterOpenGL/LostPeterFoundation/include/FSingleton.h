/****************************************************************************
* LostPeterFoundation - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2023-06-17
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _F_SINGLETON_H_
#define _F_SINGLETON_H_

#include "FPreDefine.h"
#include "FNonCopyable.h"

namespace LostPeterFoundation
{
    #if F_PLATFORM == F_PLATFORM_WINDOW
        #pragma warning (disable : 4311)
        #pragma warning (disable : 4312)
        #pragma warning (disable : 4661)
    #endif

    template<typename T>
    class FSingleton : public FNonCopyable
    {
    public:
        FSingleton()
        {
            F_Assert(!ms_Singleton && "FSingleton::FSingleton")
			ms_Singleton = static_cast<T*>(this);
        }
        
        ~FSingleton()
        {
            F_Assert(ms_Singleton && "FSingleton::~FSingleton")
			ms_Singleton = nullptr;  
        }

    public:
    protected:
        static T* ms_Singleton;

    public: 
        static T& GetSingleton()
		{
			F_Assert(ms_Singleton && "FSingleton::GetSingleton")
			return (*ms_Singleton); 
		}

		static T* GetSingletonPtr()
		{
			return ms_Singleton;
		}
    };

}; //LostPeterFoundation

#endif