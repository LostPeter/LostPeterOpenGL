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
		static std::map<uint, String> s_mapIndex2SamplerName;

    public:
        DescriptorSetLayout* poDescriptorSetLayout;

		GLShaderProgram* poShaderProgram;
		bool isDeleteShaderProgram;

		Uint2UintMap mapBindIndex2UniformBlockIndex;
		GLBufferUniformPtrIDMap mapBufferUniform;
		GLTexturePtrIDMap mapTextureCS;
		GLTexturePtrIDMap mapTextureImageCS;

    public:
        virtual void Destroy();
		bool Init(DescriptorSetLayout* pDescriptorSetLayout,
				  GLShaderProgram* pShaderProgram,
				  bool deleteShaderProgram);
		bool Init(DescriptorSetLayout* pDescriptorSetLayout,
				  GLShader* pShaderCompute);

		virtual void CleanupSwapChain();
					
	public:
		GLShaderProgram* GetShaderProgram() const { return this->poShaderProgram; }

		uint32 GetUniformBlockIndex(const String& name);
        void BindUniformBlockBinding(uint32 nUniformBlockIndex, uint32 nUniformBlockBinding);

	public:
		void BindBufferUniform(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex);
		void BindTextureCS(GLTexture* pTexture, uint32 nBindingIndex);
		void BindTextureImageCS(GLTexture* pTexture, uint32 nBindingIndex);

	public:
		void BindState();
		void UnBindState();
		void BindShader();
		void BindBufferUniforms();
		void BindTextures();

	protected:
		void bindTextures(bool enable);
		void bindTexture(GLTexturePtrIDMap& mapTexture, bool enable);

		void bindTextureImages(bool enable);
		void bindTextureImage(GLTexturePtrIDMap& mapTexture, bool enable);
    };

}; //LostPeterOpenGL

#endif