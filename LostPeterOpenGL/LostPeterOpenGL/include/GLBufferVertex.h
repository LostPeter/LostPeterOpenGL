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

#ifndef _GL_BUFFER_VERTEX_H_
#define _GL_BUFFER_VERTEX_H_

#include "GLBuffer.h"

namespace LostPeterOpenGL
{
    class openglExport GLBufferVertex : public GLBuffer
    {
    public:
        GLBufferVertex(const String& nameBuffer);
        virtual ~GLBufferVertex();

    public:
        

    public:
        virtual void Destroy();


    };

}; //LostPeterOpenGL

#endif