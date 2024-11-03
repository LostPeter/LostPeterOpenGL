/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-03
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "../include/GLBufferIndex.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLBufferIndex::GLBufferIndex(const String& nameRenderPass)
        : GLBuffer(nameRenderPass)
    {

    }
    GLBufferIndex::~GLBufferIndex()
    {
        Destroy();
    }

    void GLBufferIndex::Destroy()
    {

    }

}; //LostPeterOpenGL