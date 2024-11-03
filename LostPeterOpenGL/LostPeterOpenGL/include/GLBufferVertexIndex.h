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

#ifndef _GL_BUFFER_ERTEX_INDEX_H_
#define _GL_BUFFER_ERTEX_INDEX_H_

#include "GLBuffer.h"

namespace LostPeterOpenGL
{
    class openglExport GLBufferVertexIndex : public GLBuffer
    {
    public:
        GLBufferVertexIndex(const String& nameBuffer);
        virtual ~GLBufferVertexIndex();

    public:
        

    public:
        virtual void Destroy();


    };

}; //LostPeterOpenGL

#endif