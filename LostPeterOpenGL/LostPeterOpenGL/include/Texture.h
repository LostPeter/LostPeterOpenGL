/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2023-10-04
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport Texture : public Base
    {
    public:
        Texture(uint32 _group,
                const String& _nameTexture);
        virtual ~Texture();

    public:
       
    };

}; //LostPeterOpenGL

#endif