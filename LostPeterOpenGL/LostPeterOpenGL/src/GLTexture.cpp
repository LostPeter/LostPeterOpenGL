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

#include "../include/GLTexture.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLTexture::GLTexture(const String& nameTexture)
        : Base(nameTexture)
        , typeTexture(F_Texture_2D)
        , pathFile("")
        , nTextureID(0)
    {

    }
    GLTexture::~GLTexture()
    {
        Destroy();
    }

    void GLTexture::Destroy()
    {
        if (this->nTextureID > 0)
        {
            Base::GetWindowPtr()->destroyGLShader(this->nTextureID);
        }
        this->nTextureID = 0;
    }

    bool GLTexture::Init(const String& path,
                         FTextureType type)
    {   
        this->typeTexture = type;
        this->pathFile = path;

        // if (!Base::GetWindowPtr()->createGLTexture(GetName(),
        //                                            type,
        //                                            path,
        //                                            this->nTextureID))
        // {
        //     F_LogError("*********************** GLTexture::Init: createGLTexture failed, name: [%s], type: [%d], path: [%s] !", GetName().c_str(), type, path.c_str());
        //     return false;
        // }
        
        return true;
    }

}; //LostPeterOpenGL