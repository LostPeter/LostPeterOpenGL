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

#ifndef _GL_STATE_PIPELINE_GRAPHICS_H_
#define _GL_STATE_PIPELINE_GRAPHICS_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport GLStatePipelineGraphics : public Base
    {
    public:
        GLStatePipelineGraphics(const String& nameState);
        virtual ~GLStatePipelineGraphics();

    public:
		String nameDescriptorSetLayout;
		StringVector* poDescriptorSetLayoutNames;
		
		bool poDepthEnabled;
		GLenum poDepthFuncCompare;
		bool poDepthTestEnabled;
		bool poDepthWriteEnabled;

		bool poStencilEnabled;
		GLenum poStencil_CompareFunction;
		GLenum poStencil_StencilFailureOp;
		GLenum poStencil_DepthFailureOp;
		GLenum poStencil_DepthStencilPassOp;
		uint32_t poStencil_ReadMask;
		uint32_t poStencil_WriteMask;

		bool poBlendEnabled;
		GLenum poBlendColorFactorSrc; 
		GLenum poBlendColorFactorDst;
		GLenum poBlendColorOp;
		GLenum poBlendAlphaFactorSrc; 
		GLenum poBlendAlphaFactorDst;
		GLenum poBlendAlphaOp;

		GLboolean poColorWriteMask_Red;
		GLboolean poColorWriteMask_Green;
		GLboolean poColorWriteMask_Blue;
		GLboolean poColorWriteMask_Alpha;


		GLShaderProgram* poShaderProgram;
		bool isDeleteShaderProgram;

		GLBufferUniformPtrIDMap mapBufferUniformVertex;
		GLBufferUniformPtrIDMap mapBufferUniformFragment;
		
		GLTexturePtrIDMap mapTextureVertex;
		GLTexturePtrIDMap mapTextureFragment;

    public:
        void Destroy();
		bool Init(GLShaderProgram* pShaderProgram,
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
				  GLboolean colorWriteMask_Alpha);
		bool Init(GLShader* pShaderVertex,
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
				  GLboolean colorWriteMask_Alpha);

		virtual void CleanupSwapChain();

	public:
		GLShaderProgram* GetShaderProgram() const { return this->poShaderProgram; }

		uint32 GetUniformBlockIndex(const String& name);
        void SetUniformBlockBinding(const String& name, uint32 nUniformBlockBinding);
        void SetUniformBlockBinding(uint32 nUniformBlockIndex, uint32 nUniformBlockBinding);
			
	public:
		void BindBufferUniformVertex(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex);
		void BindBufferUniformFragment(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex);
		void BindTextureVertex(GLTexture* pTexture, uint32 nBindingIndex);
		void BindTextureFragment(GLTexture* pTexture, uint32 nBindingIndex);

    public:
		void BindShader();
		void BindBufferUniforms();
		void BindTextures();
        
    };

}; //LostPeterOpenGL

#endif