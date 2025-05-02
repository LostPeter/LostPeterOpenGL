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

		FMeshVertexType poTypeVertex;

		GLenum poTypePrimitive;
        bool poIsCull;
        GLenum poTypeFrontFace;
        GLenum poTypeCulling;
        GLenum poTypePolygonMode;
		
		bool poDepthEnabled;
		GLenum poDepthFuncCompare;
		bool poDepthTestEnabled;
		bool poDepthWriteEnabled;

		bool poStencilEnabled;
		GLenum poStencil_CompareFunction;
		GLenum poStencil_StencilFailureOp;
		GLenum poStencil_DepthFailureOp;
		GLenum poStencil_DepthStencilPassOp;
		uint32_t poStencil_Ref;
		uint32_t poStencil_Mask;

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

		Uint2UintMap mapBindIndex2UniformBlockIndex;
		GLBufferUniformPtrIDMap mapBufferUniform;
		GLTexturePtrIDMap mapTexture;


    public:
        void Destroy();
		bool Init(GLShaderProgram* pShaderProgram,
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
				  GLboolean colorWriteMask_Alpha);
		bool Init(GLShader* pShaderVertex,
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
				  GLboolean colorWriteMask_Alpha);

		virtual void CleanupSwapChain();

	public:
		GLShaderProgram* GetShaderProgram() const { return this->poShaderProgram; }

		uint32 GetUniformBlockIndex(const String& name);
        void BindUniformBlockBinding(uint32 nUniformBlockIndex, uint32 nUniformBlockBinding);
			
	public:
		void BindBufferUniform(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex);
		void BindTexture(GLTexture* pTexture, uint32 nBindingIndex);

    public:
		void BindState();
		void UnBindState();
		void BindShader();
		void BindBufferUniforms();
		void BindTextures();

	protected:
		void bindStateDepth(bool depthEnable);
		void bindStateStencil(bool stencilEnable);
		void bindStateBlend(bool blendEnable);
        
    };

}; //LostPeterOpenGL

#endif