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

#include "../include/GLShaderProgram.h"
#include "../include/OpenGLWindow.h"
#include "../include/GLShader.h"

namespace LostPeterOpenGL
{
    GLShaderProgram::GLShaderProgram(const String& nameShaderProgram)
        : Base(nameShaderProgram)
        , pShaderVertex(nullptr)
        , pShaderTessellationControl(nullptr)
        , pShaderTessellationEvaluation(nullptr)
        , pShaderGeometry(nullptr)
        , pShaderFragment(nullptr)
        , pShaderCompute(nullptr)

        , nShaderProgramID(0)
    {

    }
    GLShaderProgram::~GLShaderProgram()
    {
        Destroy();
    }

    void GLShaderProgram::Destroy()
    {
        if (this->nShaderProgramID > 0)
        {
            Base::GetWindowPtr()->destroyGLShaderProgram(this->nShaderProgramID);
        }
        this->nShaderProgramID = 0;

        this->pShaderVertex = nullptr;
        this->pShaderTessellationControl = nullptr;
        this->pShaderTessellationEvaluation = nullptr;
        this->pShaderGeometry = nullptr;
        this->pShaderFragment = nullptr;
        this->pShaderCompute = nullptr;
    }

    bool GLShaderProgram::Init(GLShader* pShaderVertex,
                               GLShader* pShaderTessellationControl,
                               GLShader* pShaderTessellationEvaluation,
                               GLShader* pShaderGeometry,
                               GLShader* pShaderFragment)
    {
        this->pShaderVertex = pShaderVertex;
        this->pShaderTessellationControl = pShaderTessellationControl;
        this->pShaderTessellationEvaluation = pShaderTessellationEvaluation;
        this->pShaderGeometry = pShaderGeometry;
        this->pShaderFragment = pShaderFragment;

        if (!Base::GetWindowPtr()->createGLShaderProgram(GetName(),
                                                         pShaderVertex != nullptr ? pShaderVertex->nShaderID : 0,
                                                         pShaderTessellationControl != nullptr ? pShaderTessellationControl->nShaderID : 0,
                                                         pShaderTessellationEvaluation != nullptr ? pShaderTessellationEvaluation->nShaderID : 0,
                                                         pShaderGeometry != nullptr ? pShaderGeometry->nShaderID : 0,
                                                         pShaderFragment != nullptr ? pShaderFragment->nShaderID : 0,
                                                         this->nShaderProgramID))
        {
            F_LogError("*********************** GLShaderProgram::Init: Failed to create shader program: [%s] !", GetName().c_str());
            return false;
        }

        return true;
    }

    bool GLShaderProgram::Init(GLShader* pShaderCompute)
    {
        if (pShaderCompute == nullptr)
            return false;
        this->pShaderCompute = pShaderCompute;

        if (!Base::GetWindowPtr()->createGLShaderProgram(GetName(),
                                                         pShaderCompute->nShaderID,
                                                         this->nShaderProgramID))
        {
            F_LogError("*********************** GLShaderProgram::Init: Failed to create shader program [%s] !", GetName().c_str());
            return false;
        }

        return true;
    }

    void GLShaderProgram::BindProgram()
    {
        Base::GetWindowPtr()->bindGLShaderProgram(this->nShaderProgramID);
    }

    

}; //LostPeterOpenGL