/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-16
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "../include/GLBufferStorage.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLBufferStorage::GLBufferStorage(const String& nameBuffer)
        : GLBuffer(nameBuffer)
    {

    }
    GLBufferStorage::~GLBufferStorage()
    {
        Destroy();
    }

    void GLBufferStorage::Destroy()
    {

    }


}; //LostPeterOpenGL