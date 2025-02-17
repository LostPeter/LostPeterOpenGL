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
        uint32 nVAO;
        uint32 nVBO;
        uint32 nVEO;

        FMeshVertexType typeVertex;
        size_t nBufferSize_Vertex;
        uint8* pBuffer_Vertex;
        bool bIsDelete_Vertex;
        size_t nBufferSize_Index;
        uint8* pBuffer_Index;
        bool bIsDelete_Index;


    public:
        virtual void Destroy();
        virtual bool Init(FMeshVertexType type,
                          size_t bufSize_Vertex, 
                          uint8* pBuf_Vertex,
                          bool isDelete_Vertex,
                          size_t bufSize_Index, 
                          uint8* pBuf_Index,
                          bool isDelete_Index);

        virtual void Update(FMeshVertexType type,
                            size_t bufSize_Vertex,
                            uint8* pBuf_Vertex,
                            bool isDelete_Vertex,
                            size_t bufSize_Index,
                            uint8* pBuf_Index,
                            bool isDelete_Index);

    public:
        void BindVertexArray();

    protected:
        virtual void destroyBuffer();
    };

}; //LostPeterOpenGL

#endif