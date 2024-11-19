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

#ifndef _GL_BUFFER_UNIFORM_H_
#define _GL_BUFFER_UNIFORM_H_

#include "GLBuffer.h"

namespace LostPeterOpenGL
{
    class openglExport GLBufferUniform : public GLBuffer
    {
    public:
        GLBufferUniform(const String& nameBuffer);
        virtual ~GLBufferUniform();

    public:
        size_t nBufferSize;
        uint8* pBuffer;
        bool bIsDelete;
        GLenum eUsage;
        
        uint32 nBindingIndex;
        uint32 nBufferUniformID;

    public:
        virtual void Destroy();
        virtual bool Init(uint32 bindingIndex,
                          GLenum usage,
                          size_t bufSize, 
                          uint8* pBuf,
                          bool isDelete);

        virtual void Update(size_t bufSize, 
                            uint8* pBuf,
                            bool isDelete);
        virtual void Update(size_t offset,
                            size_t bufSize, 
                            uint8* pBuf);

    public:
        void BindBufferUniform();
        void BindBufferUniformBlockIndex(uint32 nUniformBlockIndex);

    protected:
        virtual void destroyBuffer();
        
    };

}; //LostPeterOpenGL

#endif