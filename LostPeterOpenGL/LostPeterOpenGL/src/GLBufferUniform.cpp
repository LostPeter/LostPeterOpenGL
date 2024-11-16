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

#include "../include/GLBufferUniform.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLBufferUniform::GLBufferUniform(const String& nameRenderPass)
        : GLBuffer(nameRenderPass)

        , nBufferSize(0)
        , pBuffer(nullptr)
        , bIsDelete(true)

        , nBufferUniformID(0)
    {

    }
    GLBufferUniform::~GLBufferUniform()
    {
        Destroy();
    }
        void GLBufferUniform::destroyBuffer()
        {
            if (this->bIsDelete && this->pBuffer != nullptr)
            {
                F_DELETE_T(this->pBuffer)
            }
            this->pBuffer = nullptr;
        }

    void GLBufferUniform::Destroy()
    {
        destroyBuffer();
        if (this->nBufferUniformID > 0)
        {
            Base::GetWindowPtr()->destroyGLBufferUniform(this->nBufferUniformID);
        }
        this->nBufferUniformID = 0;
    }

    bool GLBufferUniform::Init(size_t bufSize, 
                               uint8* pBuf,
                               bool isDelete)
    {
        this->nBufferSize = bufSize;
        this->pBuffer = pBuf;
        this->bIsDelete = isDelete;

        if (!Base::GetWindowPtr()->createGLBufferUniform(GetName(),
                                                         bufSize, 
                                                         pBuf, 
                                                         this->nBufferUniformID))
        {
            F_LogError("*********************** GLBufferUniform::Init: Failed to create buffer uniform: [%s] !", GetName().c_str());
            return false;
        }
        return true;
    }

    void GLBufferUniform::Update(size_t bufSize, 
                                 uint8* pBuf,
                                 bool isDelete)
    {
        destroyBuffer();

        this->nBufferSize = bufSize;
        this->pBuffer = pBuf;
        this->bIsDelete = isDelete;

        Base::GetWindowPtr()->updateGLBufferUniform(bufSize, 
                                                    pBuf, 
                                                    this->nBufferUniformID);
    }

    void GLBufferUniform::Update(size_t offset,
                                 size_t bufSize, 
                                 uint8* pBuf)
    {
        Base::GetWindowPtr()->updateGLBufferUniform(offset,
                                                    bufSize, 
                                                    pBuf, 
                                                    this->nBufferUniformID);
    }                        

    void GLBufferUniform::BindBufferUniform()
    {
        Base::GetWindowPtr()->bindGLBufferUniform(this->nBufferUniformID);
    }

}; //LostPeterOpenGL