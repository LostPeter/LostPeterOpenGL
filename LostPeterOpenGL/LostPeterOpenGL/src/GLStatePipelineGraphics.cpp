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
#include "../include/GLBufferUniform.h"
#include "../include/GLTexture.h"

namespace LostPeterOpenGL
{
    GLStatePipelineGraphics::GLStatePipelineGraphics(const String& nameState)
        : Base(nameState)

        , poDescriptorSetLayout(nullptr)

		, poTypeVertex(F_MeshVertex_Pos3Color4Normal3Tangent3Tex2)

		, poTypePrimitive(GL_TRIANGLES)
		, poIsCull(true)
        , poTypeFrontFace(GL_CW)
        , poTypeCulling(GL_BACK)
        , poTypePolygonMode(GL_FILL)

		, poDepthEnabled(false)
		, poDepthFuncCompare(GL_LEQUAL)
		, poDepthTestEnabled(false)
		, poDepthWriteEnabled(false)

		, poStencilEnabled(false)
		, poStencil_CompareFunction(GL_LEQUAL)
		, poStencil_StencilFailureOp(GL_KEEP)
		, poStencil_DepthFailureOp(GL_KEEP)
		, poStencil_DepthStencilPassOp(GL_KEEP)
		, poStencil_Ref(0)
		, poStencil_Mask(0)
		
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

	bool GLStatePipelineGraphics::Init(DescriptorSetLayout* pDescriptorSetLayout,
									   GLShaderProgram* pShaderProgram,
									   bool deleteShaderProgram,
									   FMeshVertexType typeVertex,
									   GLenum typePrimitive,
									   bool isCull,
									   GLenum typeFrontFace,
									   GLenum typeCulling,
									   GLenum typePolygonMode,
									   bool depthEnabled,
									   GLenum depthFuncCompare,
									   bool depthTestEnabled,
									   bool depthWriteEnabled,
									   bool stencilEnabled,
									   GLenum stencil_CompareFunction,
									   GLenum stencil_StencilFailureOp,
									   GLenum stencil_DepthFailureOp,
									   GLenum stencil_DepthStencilPassOp,
									   uint32_t stencil_Ref,
									   uint32_t stencil_Mask,
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

		this->poDescriptorSetLayout = pDescriptorSetLayout;
		this->poTypeVertex = typeVertex;
		
		this->poTypePrimitive = typePrimitive;
        this->poIsCull = isCull;
        this->poTypeFrontFace = typeFrontFace;
        this->poTypeCulling = typeCulling;
        this->poTypePolygonMode = typePolygonMode;

		this->poDepthEnabled = depthEnabled;
		this->poDepthFuncCompare = depthFuncCompare;
		this->poDepthTestEnabled = depthTestEnabled;
		this->poDepthWriteEnabled = depthWriteEnabled;

		this->poStencilEnabled = stencilEnabled;
		this->poStencil_CompareFunction = stencil_CompareFunction;
		this->poStencil_StencilFailureOp = stencil_StencilFailureOp;
		this->poStencil_DepthFailureOp = stencil_DepthFailureOp;
		this->poStencil_DepthStencilPassOp = stencil_DepthStencilPassOp;
		this->poStencil_Ref = stencil_Ref;
		this->poStencil_Mask = stencil_Mask;

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

	bool GLStatePipelineGraphics::Init(DescriptorSetLayout* pDescriptorSetLayout,
									   GLShader* pShaderVertex,
									   GLShader* pShaderTessellationControl,
									   GLShader* pShaderTessellationEvaluation,
									   GLShader* pShaderGeometry,
									   GLShader* pShaderFragment,
									   FMeshVertexType typeVertex,
									   GLenum typePrimitive,
									   bool isCull,
									   GLenum typeFrontFace,
									   GLenum typeCulling,
									   GLenum typePolygonMode,
									   bool depthEnabled,
									   GLenum depthFuncCompare,
									   bool depthTestEnabled,
									   bool depthWriteEnabled,
									   bool stencilEnabled,
									   GLenum stencil_CompareFunction,
									   GLenum stencil_StencilFailureOp,
									   GLenum stencil_DepthFailureOp,
									   GLenum stencil_DepthStencilPassOp,
									   uint32_t stencil_Ref,
									   uint32_t stencil_Mask,
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

		return Init(pDescriptorSetLayout,
					pShaderProgram,
					true,
					typeVertex,
					typePrimitive,
					isCull,
					typeFrontFace,
					typeCulling,
					typePolygonMode,
					depthEnabled,
					depthFuncCompare,
					depthTestEnabled,
					depthWriteEnabled,
					stencilEnabled,
					stencil_CompareFunction,
					stencil_StencilFailureOp,
					stencil_DepthFailureOp,
					stencil_DepthStencilPassOp,
					stencil_Ref,
					stencil_Mask,
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
		this->poDescriptorSetLayout = nullptr;
		
		if (this->isDeleteShaderProgram)
		{
			F_DELETE(this->poShaderProgram)
		}
		this->poShaderProgram = nullptr;

		this->mapBindIndex2UniformBlockIndex.clear();
		this->mapBufferUniform.clear();
		this->mapTexture.clear();
	}

	uint32 GLStatePipelineGraphics::GetUniformBlockIndex(const String& name)
	{
		return this->poShaderProgram->GetUniformBlockIndex(name);
	}
	void GLStatePipelineGraphics::BindUniformBlockBinding(uint32 nUniformBlockIndex, uint32 nUniformBlockBinding)
	{
		this->mapBindIndex2UniformBlockIndex[nUniformBlockBinding] = nUniformBlockIndex;
		this->poShaderProgram->SetUniformBlockBinding(nUniformBlockIndex, nUniformBlockBinding);
	}

	void GLStatePipelineGraphics::BindBufferUniform(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex)
	{
		this->mapBufferUniform[nBindingIndex] = pBufferUnifom;
	}
	void GLStatePipelineGraphics::BindTexture(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTexture[nBindingIndex] = pTexture;
	}

	void GLStatePipelineGraphics::BindState()
	{
		OpenGLWindow* pWindow = Base::GetWindowPtr();
		pWindow->setFrontFace(this->poTypeFrontFace);
		pWindow->setEnable(GL_CULL_FACE, this->poIsCull);
		pWindow->setCullFace(this->poTypeCulling);
		pWindow->setPolygonMode(GL_FRONT_AND_BACK, this->poTypePolygonMode);

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
			if (!this->poDepthTestEnabled)
				pWindow->setDepthFunc(GL_ALWAYS);
			else
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
			pWindow->setStencilFunc(this->poStencil_CompareFunction, this->poStencil_Ref, this->poStencil_Mask);
			pWindow->setStencilOp(this->poStencil_StencilFailureOp, this->poStencil_DepthFailureOp, this->poStencil_DepthStencilPassOp);
			pWindow->setStencilMask(this->poStencil_Mask);
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
		size_t count = this->mapBindIndex2UniformBlockIndex.size();
		if (count > 0)
		{
			for (Uint2UintMap::iterator it = this->mapBindIndex2UniformBlockIndex.begin();
				 it != this->mapBindIndex2UniformBlockIndex.end(); ++it)
			{
				uint32 nBindIndex = it->first;
				GLBufferUniformPtrIDMap::iterator itFind = this->mapBufferUniform.find(nBindIndex);
				if (itFind != this->mapBufferUniform.end())
				{
					itFind->second->BindBufferUniformBlockIndex();
				}
			}
		}
	}
	void GLStatePipelineGraphics::BindTextures()
	{
		size_t count = this->mapTexture.size();
		if (count > 0)
		{
			for (GLTexturePtrIDMap::iterator it = this->mapTexture.begin();
				 it != this->mapTexture.end(); ++it)
			{
				it->second->BindTexture();
			}
		}
	}

}; //LostPeterOpenGL