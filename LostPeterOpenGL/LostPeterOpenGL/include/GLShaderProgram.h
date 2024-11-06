/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-06
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _GL_SHADER_PROGRAM_H_
#define _GL_SHADER_PROGRAM_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport GLShaderProgram : public Base
    {
    public:
        GLShaderProgram(const String& nameShaderProgram);
        virtual ~GLShaderProgram();

    public:
        GLShader* pShaderVertex;
        GLShader* pShaderTessellationControl;
        GLShader* pShaderTessellationEvaluation;
        GLShader* pShaderGeometry;
        GLShader* pShaderFragment;
        GLShader* pShaderCompute;

        uint32 nShaderProgramID;


    public:
        void Destroy();
        bool Init(GLShader* pShaderVertex,
                  GLShader* pShaderTessellationControl,
                  GLShader* pShaderTessellationEvaluation,
                  GLShader* pShaderGeometry,
                  GLShader* pShaderFragment);
        bool Init(GLShader* pShaderCompute);

    public:
        void BindProgram();
        

    public:


    };

}; //LostPeterOpenGL

#endif