/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-07
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _GL_TEXTURE_H_
#define _GL_TEXTURE_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport GLTexture : public Base
    {
    public:
        GLTexture(const String& nameTexture);
        virtual ~GLTexture();

    public:
        FTextureType typeTexture;
        FTextureAddressingType typeTextureAddressing_S;
        FTextureAddressingType typeTextureAddressing_T;
        FTextureFilterType typeTextureFilter_Min;
        FTextureFilterType typeTextureFilter_Mag;
        FMSAASampleCountType typeMSAASampleCount;

        String pathFile;

        uint32 nTextureID;

    public:
        void Destroy();
        bool Init(const String& path,
                  FTextureType type);

    public:
        
    };

}; //LostPeterOpenGL

#endif