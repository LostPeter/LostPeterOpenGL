/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-10
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _OPENGL_004_MODEL_H_
#define _OPENGL_004_MODEL_H_

#include "OpenGLWindow.h"
using namespace LostPeterOpenGL; 

class OpenGL_004_Model : public OpenGLWindow
{
public:
    OpenGL_004_Model(int width, int height, String name);

public:
    std::vector<FVertex_Pos2Color4Tex2> vertices;

protected:
    //Create Pipeline

    //Load Assets
        //Geometry
            virtual void loadModel_Custom();

    //Render/Update
        virtual bool beginRenderImgui();
        virtual void endRenderImgui();

public:

};


#endif