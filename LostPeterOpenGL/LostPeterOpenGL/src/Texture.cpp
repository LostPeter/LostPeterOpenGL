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

#include "../include/Texture.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    Texture::Texture(uint32 _group,
                     const String& _nameTexture)
        : Base(_group, _nameTexture)
    {

    }
    Texture::~Texture()
    {

    }

}; //LostPeterOpenGL