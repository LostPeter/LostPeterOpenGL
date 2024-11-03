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

#ifndef _GL_FRAME_BUFFER_H_
#define _GL_FRAME_BUFFER_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport GLFrameBuffer : public Base
    {
    public:
        GLFrameBuffer(const String& nameFrameBuffer);
        virtual ~GLFrameBuffer();

    public:
        uint32_t nWidth;
        uint32_t nHeight;
        uint32_t nLayers;

        uint32 nFrameBufferID;

    public:
        void Destroy();
        bool Init(uint32_t width,
                  uint32_t height,
                  uint32_t layers);

    };

}; //LostPeterOpenGL

#endif