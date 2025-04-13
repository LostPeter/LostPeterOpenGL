/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2025-04-13
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _GL_STATE_PIPELINE_COMPUTE_H_
#define _GL_STATE_PIPELINE_COMPUTE_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport GLStatePipelineCompute : public Base
    {
    public:
        GLStatePipelineCompute(const String& nameState);
        virtual ~GLStatePipelineCompute();

    public:
        

    public:
        virtual void Destroy() = 0;
        
    };

}; //LostPeterOpenGL

#endif