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

#include "../include/GLBufferVertex.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLBufferVertex::GLBufferVertex(const String& nameRenderPass)
        : GLBuffer(nameRenderPass)
    {

    }
    GLBufferVertex::~GLBufferVertex()
    {
        Destroy();
    }

    void GLBufferVertex::Destroy()
    {

    }

}; //LostPeterOpenGL