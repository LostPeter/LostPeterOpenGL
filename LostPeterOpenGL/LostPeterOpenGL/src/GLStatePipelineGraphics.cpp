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
	std::map<uint, String> GLStatePipelineGraphics::s_mapIndex2SamplerName;
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
		if (s_mapIndex2SamplerName.size() <= 0)
		{
			s_mapIndex2SamplerName[0] = "texSampler0";
			s_mapIndex2SamplerName[1] = "texSampler1";
			s_mapIndex2SamplerName[2] = "texSampler2";
			s_mapIndex2SamplerName[3] = "texSampler3";
			s_mapIndex2SamplerName[4] = "texSampler4";
			s_mapIndex2SamplerName[5] = "texSampler5";
			s_mapIndex2SamplerName[6] = "texSampler6";
			s_mapIndex2SamplerName[7] = "texSampler7";
			s_mapIndex2SamplerName[8] = "texSampler8";
			s_mapIndex2SamplerName[9] = "texSampler9";
			s_mapIndex2SamplerName[10] = "texSampler10";
			s_mapIndex2SamplerName[11] = "texSampler11";
			s_mapIndex2SamplerName[12] = "texSampler12";
			s_mapIndex2SamplerName[13] = "texSampler13";
			s_mapIndex2SamplerName[14] = "texSampler14";
			s_mapIndex2SamplerName[15] = "texSampler15";
		}
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
		this->mapTextureVS.clear();
		this->mapTextureFS.clear();
		this->mapTextureTESC.clear();
		this->mapTextureTESE.clear();
		this->mapTextureGS.clear();
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
	void GLStatePipelineGraphics::BindTextureVS(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureVS[nBindingIndex] = pTexture;
	}
	void GLStatePipelineGraphics::BindTextureFS(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureFS[nBindingIndex] = pTexture;
	}
	void GLStatePipelineGraphics::BindTextureTESC(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureTESC[nBindingIndex] = pTexture;
	}
	void GLStatePipelineGraphics::BindTextureTESE(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureTESE[nBindingIndex] = pTexture;
	}
	void GLStatePipelineGraphics::BindTextureGS(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureGS[nBindingIndex] = pTexture;
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
		bindTextures(false);
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
		bindTextures(true);
	}
	void GLStatePipelineGraphics::bindTextures(bool enable)
	{
		//VS
		if (this->mapTextureVS.size() > 0)
			bindTexture(this->mapTextureVS, enable);
		//FS
		if (this->mapTextureFS.size() > 0)
			bindTexture(this->mapTextureFS, enable);
		//TESC
		if (this->mapTextureTESC.size() > 0)
			bindTexture(this->mapTextureTESC, enable);
		//TESE
		if (this->mapTextureTESE.size() > 0)
			bindTexture(this->mapTextureTESE, enable);
		//GS
		if (this->mapTextureGS.size() > 0)
			bindTexture(this->mapTextureGS, enable);
	}
	void GLStatePipelineGraphics::bindTexture(GLTexturePtrIDMap& mapTexture, bool enable)
	{
		OpenGLWindow* pWindow = Base::GetWindowPtr();
		for (GLTexturePtrIDMap::iterator it = mapTexture.begin();
			 it != mapTexture.end(); ++it)
		{
			GLTexture* pTexture = it->second;
			uint nBindingIndex = it->first;
			pTexture->BindTexture(nBindingIndex, enable);
			pWindow->setUniform1i(this->poShaderProgram->nShaderProgramID, s_mapIndex2SamplerName[nBindingIndex], (int)nBindingIndex);
		}
	}

}; //LostPeterOpenGL