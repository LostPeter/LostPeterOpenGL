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

#include "../include/GLFrameBuffer.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLFrameBuffer::GLFrameBuffer(const String& nameFrameBuffer)
        : Base(nameFrameBuffer)

        , nWidth(0)
        , nHeight(0)
        , nLayers(0)

        , nFrameBufferID(0)
    {

    }
    GLFrameBuffer::~GLFrameBuffer()
    {
        Destroy();
    }

    void GLFrameBuffer::Destroy()
    {
        if (this->nFrameBufferID > 0)
        {
            Base::GetWindowPtr()->destroyGLFrameBuffer(this->nFrameBufferID);
        }
        this->nFrameBufferID = 0;
    }

    bool GLFrameBuffer::Init(uint32_t width,
                             uint32_t height,
                             uint32_t layers)
    {
        this->nWidth = width;
        this->nHeight = height;
        this->nLayers = layers;

        this->nFrameBufferID = Base::GetWindowPtr()->createGLFrameBuffer();
        if (this->nFrameBufferID <= 0)
        {
            return false;
        }
        return true;
    }

}; //LostPeterOpenGL