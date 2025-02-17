/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2022-10-30
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _PRE_MACRO_H_
#define _PRE_MACRO_H_

#include "FPreMacro.h"

#if F_PLATFORM == F_PLATFORM_WINDOW
	#if defined(OPENGL_EXPORTS)
		#define openglExport        	__declspec(dllexport) 
	#else
		#define openglExport      		__declspec(dllimport)
	#endif
#elif F_PLATFORM == F_PLATFORM_ANDROID
	#define openglExport				__attribute__ ((visibility("default")))
#else
	#define openglExport
#endif


#endif