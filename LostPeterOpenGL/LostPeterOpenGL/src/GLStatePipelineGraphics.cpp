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

#include "../include/GLStatePipelineGraphics.h"
#include "../include/OpenGLWindow.h"
#include "../include/GLShaderProgram.h"
#include "../include/GLShader.h"
#include "../include/GLTexture.h"

namespace LostPeterOpenGL
{
    GLStatePipelineGraphics::GLStatePipelineGraphics(const String& nameState)
        : Base(nameState)

		, nameDescriptorSetLayout("")
        , poDescriptorSetLayoutNames(nullptr)

		, poDepthEnabled(false)
		, poDepthFuncCompare(GL_LEQUAL)
		, poDepthTestEnabled(false)
		, poDepthWriteEnabled(false)

		, poStencilEnabled(false)
		, poStencil_CompareFunction(GL_LEQUAL)
		, poStencil_StencilFailureOp(GL_KEEP)
		, poStencil_DepthFailureOp(GL_KEEP)
		, poStencil_DepthStencilPassOp(GL_KEEP)
		, poStencil_ReadMask(0)
		, poStencil_WriteMask(0)
		
		, poBlendEnabled(false)
		, poBlendColorFactorSrc(GL_ONE)
		, poBlendColorFactorDst(GL_ZERO)
		, poBlendColorOp(GL_FUNC_ADD)
		, poBlendAlphaFactorSrc(GL_ONE)
		, poBlendAlphaFactorDst(GL_ZERO)
		, poBlendAlphaOp(GL_FUNC_ADD)

		, poColorWriteMask_Red(true)
		, poColorWriteMask_Green(true)
		, poColorWriteMask_Blue(true)
		, poColorWriteMask_Alpha(true)

		, poShaderProgram(nullptr)
		, isDeleteShaderProgram(true)

    {

    }
    GLStatePipelineGraphics::~GLStatePipelineGraphics()
    {
		Destroy();
    }

	void GLStatePipelineGraphics::Destroy()
	{
		CleanupSwapChain();
	}

	bool GLStatePipelineGraphics::Init(GLShaderProgram* pShaderProgram,
									   bool deleteShaderProgram,
									   bool depthEnabled,
									   GLenum depthFuncCompare,
									   bool depthTestEnabled,
									   bool depthWriteEnabled,
									   bool stencilEnabled,
									   GLenum stencil_CompareFunction,
									   GLenum stencil_StencilFailureOp,
									   GLenum stencil_DepthFailureOp,
									   GLenum stencil_DepthStencilPassOp,
									   uint32_t stencil_ReadMask,
									   uint32_t stencil_WriteMask,
									   bool blendEnabled,
									   GLenum blendColorFactorSrc, 
									   GLenum blendColorFactorDst,
									   GLenum blendColorOp,
									   GLenum blendAlphaFactorSrc, 
									   GLenum blendAlphaFactorDst,
									   GLenum blendAlphaOp,
									   GLboolean colorWriteMask_Red,
									   GLboolean colorWriteMask_Green,
									   GLboolean colorWriteMask_Blue,
									   GLboolean colorWriteMask_Alpha)
	{
		this->poShaderProgram = pShaderProgram;
		this->isDeleteShaderProgram = deleteShaderProgram;

		this->poDepthEnabled = depthEnabled;
		this->poDepthFuncCompare = depthFuncCompare;
		this->poDepthTestEnabled = depthTestEnabled;
		this->poDepthWriteEnabled = depthWriteEnabled;

		this->poStencilEnabled = stencilEnabled;
		this->poStencil_CompareFunction = stencil_CompareFunction;
		this->poStencil_StencilFailureOp = stencil_StencilFailureOp;
		this->poStencil_DepthFailureOp = stencil_DepthFailureOp;
		this->poStencil_DepthStencilPassOp = stencil_DepthStencilPassOp;
		this->poStencil_ReadMask = stencil_ReadMask;
		this->poStencil_WriteMask = stencil_WriteMask;

		this->poBlendEnabled = blendEnabled;
		this->poBlendColorFactorSrc = blendColorFactorSrc; 
		this->poBlendColorFactorDst = blendColorFactorDst;
		this->poBlendColorOp = blendColorOp;
		this->poBlendAlphaFactorSrc = blendAlphaFactorSrc; 
		this->poBlendAlphaFactorDst = blendAlphaFactorDst;
		this->poBlendAlphaOp = blendAlphaOp;

		this->poColorWriteMask_Red = colorWriteMask_Red;
		this->poColorWriteMask_Green = colorWriteMask_Green;
		this->poColorWriteMask_Blue = colorWriteMask_Blue;
		this->poColorWriteMask_Alpha = colorWriteMask_Alpha;

		return true;
	}

	bool GLStatePipelineGraphics::Init(GLShader* pShaderVertex,
									   GLShader* pShaderTessellationControl,
									   GLShader* pShaderTessellationEvaluation,
									   GLShader* pShaderGeometry,
									   GLShader* pShaderFragment,
									   bool depthEnabled,
									   GLenum depthFuncCompare,
									   bool depthTestEnabled,
									   bool depthWriteEnabled,
									   bool stencilEnabled,
									   GLenum stencil_CompareFunction,
									   GLenum stencil_StencilFailureOp,
									   GLenum stencil_DepthFailureOp,
									   GLenum stencil_DepthStencilPassOp,
									   uint32_t stencil_ReadMask,
									   uint32_t stencil_WriteMask,
									   bool blendEnabled,
									   GLenum blendColorFactorSrc, 
									   GLenum blendColorFactorDst,
									   GLenum blendColorOp,
									   GLenum blendAlphaFactorSrc, 
									   GLenum blendAlphaFactorDst,
									   GLenum blendAlphaOp,
									   GLboolean colorWriteMask_Red,
									   GLboolean colorWriteMask_Green,
									   GLboolean colorWriteMask_Blue,
									   GLboolean colorWriteMask_Alpha)
	{
		String nameShaderProgram = GetName();
		GLShaderProgram* pShaderProgram = Base::GetWindowPtr()->createShaderProgram(nameShaderProgram,
																				    pShaderVertex,
																				    pShaderTessellationControl,
																				    pShaderTessellationEvaluation,
																				    pShaderGeometry,
																				    pShaderFragment);
		if (pShaderProgram == nullptr)
		{
			String msg = "*********************** GLStatePipelineGraphics::Init: Failed to create shader program: " + nameShaderProgram;
			return false;
		}

		return Init(pShaderProgram,
					true,
					depthEnabled,
					depthFuncCompare,
					depthTestEnabled,
					depthWriteEnabled,
					stencilEnabled,
					stencil_CompareFunction,
					stencil_StencilFailureOp,
					stencil_DepthFailureOp,
					stencil_DepthStencilPassOp,
					stencil_ReadMask,
					stencil_WriteMask,
					blendEnabled,
					blendColorFactorSrc, 
					blendColorFactorDst,
					blendColorOp,
					blendAlphaFactorSrc, 
					blendAlphaFactorDst,
					blendAlphaOp,
					colorWriteMask_Red,
					colorWriteMask_Green,
					colorWriteMask_Blue,
					colorWriteMask_Alpha);
	}

	void GLStatePipelineGraphics::CleanupSwapChain()
	{
		this->poDescriptorSetLayoutNames = nullptr;
		
		if (this->isDeleteShaderProgram)
		{
			F_DELETE(this->poShaderProgram)
		}
		this->poShaderProgram = nullptr;

		this->mapBufferUniformVertex.clear();
		this->mapBufferUniformFragment.clear();
		this->mapTextureVertex.clear();
		this->mapTextureFragment.clear();
	}

	uint32 GLStatePipelineGraphics::GetUniformBlockIndex(const String& name)
	{
		return this->poShaderProgram->GetUniformBlockIndex(name);
	}
	void GLStatePipelineGraphics::SetUniformBlockBinding(const String& name, uint32 nUniformBlockBinding)
	{
		this->poShaderProgram->SetUniformBlockBinding(name, nUniformBlockBinding);
	}
	void GLStatePipelineGraphics::SetUniformBlockBinding(uint32 nUniformBlockIndex, uint32 nUniformBlockBinding)
	{
		this->poShaderProgram->SetUniformBlockBinding(nUniformBlockIndex, nUniformBlockBinding);
	}

	void GLStatePipelineGraphics::BindBufferUniformVertex(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex)
	{

	}
	void GLStatePipelineGraphics::BindBufferUniformFragment(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex)
	{
		
	}
	void GLStatePipelineGraphics::BindTextureVertex(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureVertex[nBindingIndex] = pTexture;
	}
	void GLStatePipelineGraphics::BindTextureFragment(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureFragment[nBindingIndex] = pTexture;
	}

	void GLStatePipelineGraphics::BindState()
	{
		bindStateDepth(this->poDepthEnabled);
		bindStateStencil(this->poStencilEnabled);
		bindStateBlend(this->poBlendEnabled);
	}
	void GLStatePipelineGraphics::UnBindState()
	{
		bindStateDepth(false);
		bindStateStencil(false);
		bindStateBlend(false);
	}
	void GLStatePipelineGraphics::bindStateDepth(bool depthEnable)
	{
		OpenGLWindow* pWindow = Base::GetWindowPtr();
		pWindow->setEnable(GL_DEPTH_TEST, depthEnable);
		if (depthEnable)
		{
			pWindow->setDepthFunc(this->poDepthFuncCompare);
			pWindow->setDepthWrite(this->poDepthWriteEnabled);
		}
	}
	void GLStatePipelineGraphics::bindStateStencil(bool stencilEnable)
	{
		OpenGLWindow* pWindow = Base::GetWindowPtr();
		pWindow->setEnable(GL_STENCIL_TEST, stencilEnable);
		if (stencilEnable)
		{
			pWindow->setStencilFunc(this->poStencil_CompareFunction, this->poStencil_WriteMask, this->poStencil_ReadMask);
			pWindow->setStencilOp(this->poStencil_StencilFailureOp, this->poStencil_DepthFailureOp, this->poStencil_DepthStencilPassOp);
			pWindow->setStencilMask(this->poStencil_WriteMask);
		}
	}
	void GLStatePipelineGraphics::bindStateBlend(bool blendEnable)
	{
		OpenGLWindow* pWindow = Base::GetWindowPtr();
		pWindow->setEnable(GL_BLEND, blendEnable);
		if (blendEnable)
		{
			pWindow->setBlendFunc(this->poBlendColorFactorSrc, this->poBlendColorFactorDst);
		}
	}

	void GLStatePipelineGraphics::BindShader()
	{	
		this->poShaderProgram->BindProgram();
	}

	void GLStatePipelineGraphics::BindBufferUniforms()
	{

	}
	void GLStatePipelineGraphics::BindTextures()
	{
		size_t count = 0;

		//Vertex
		{
			count = this->mapTextureVertex.size();
			if (count > 0)
			{
				for (GLTexturePtrIDMap::iterator it = this->mapTextureVertex.begin();
					 it != this->mapTextureVertex.end(); ++it)
				{
					it->second->BindTexture();
				}
			}
		}
		//Fragment
		{
			count = this->mapTextureFragment.size();
			if (count > 0)
			{
				for (GLTexturePtrIDMap::iterator it = this->mapTextureFragment.begin();
					 it != this->mapTextureFragment.end(); ++it)
				{
					it->second->BindTexture();
				}
			}
		}
	}

}; //LostPeterOpenGL