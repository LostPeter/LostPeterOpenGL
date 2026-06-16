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

#include "../include/GLStatePipelineCompute.h"
#include "../include/OpenGLWindow.h"
#include "../include/GLShaderProgram.h"
#include "../include/GLShader.h"
#include "../include/GLBufferUniform.h"
#include "../include/GLTexture.h"

namespace LostPeterOpenGL
{
	std::map<uint, String> GLStatePipelineCompute::s_mapIndex2SamplerName;
    GLStatePipelineCompute::GLStatePipelineCompute(const String& nameState)
        : Base(nameState)

		, poDescriptorSetLayout(nullptr)

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
    GLStatePipelineCompute::~GLStatePipelineCompute()
    {
		Destroy();
    }

	void GLStatePipelineCompute::Destroy()
	{
		CleanupSwapChain();
	}
	
	bool GLStatePipelineCompute::Init(DescriptorSetLayout* pDescriptorSetLayout,
									  GLShaderProgram* pShaderProgram,
									  bool deleteShaderProgram)
	{
		this->poShaderProgram = pShaderProgram;
		this->isDeleteShaderProgram = deleteShaderProgram;

		this->poDescriptorSetLayout = pDescriptorSetLayout;

		return true;
	}
	bool GLStatePipelineCompute::Init(DescriptorSetLayout* pDescriptorSetLayout,
									  GLShader* pShaderCompute)
	{
		String nameShaderProgram = GetName();
		GLShaderProgram* pShaderProgram = Base::GetWindowPtr()->createShaderProgram(nameShaderProgram,
																				    pShaderCompute);
		if (pShaderProgram == nullptr)
		{
			String msg = "*********************** GLStatePipelineCompute::Init: Failed to create shader program: " + nameShaderProgram;
			F_LogError(msg.c_str());
			return false;
		}

		return Init(pDescriptorSetLayout,
					pShaderProgram,
					true);
	}

	void GLStatePipelineCompute::CleanupSwapChain()
	{
		this->poDescriptorSetLayout = nullptr;
		
		if (this->isDeleteShaderProgram)
		{
			F_DELETE(this->poShaderProgram)
		}
		this->poShaderProgram = nullptr;

		this->mapBindIndex2UniformBlockIndex.clear();
		this->mapBufferUniform.clear();
		this->mapTextureCS.clear();
		this->mapTextureImageCS.clear();
	}

	uint32 GLStatePipelineCompute::GetUniformBlockIndex(const String& name)
	{
		return this->poShaderProgram->GetUniformBlockIndex(name);
	}
	void GLStatePipelineCompute::BindUniformBlockBinding(uint32 nUniformBlockIndex, uint32 nUniformBlockBinding)
	{
		this->mapBindIndex2UniformBlockIndex[nUniformBlockBinding] = nUniformBlockIndex;
		this->poShaderProgram->SetUniformBlockBinding(nUniformBlockIndex, nUniformBlockBinding);
	}

	void GLStatePipelineCompute::BindBufferUniform(GLBufferUniform* pBufferUnifom, uint32 nBindingIndex)
	{
		this->mapBufferUniform[nBindingIndex] = pBufferUnifom;
	}

	void GLStatePipelineCompute::BindTextureCS(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureCS[nBindingIndex] = pTexture;
	}
	void GLStatePipelineCompute::BindTextureImageCS(GLTexture* pTexture, uint32 nBindingIndex)
	{
		this->mapTextureImageCS[nBindingIndex] = pTexture;
	}


	void GLStatePipelineCompute::BindState()
	{

	}
	void GLStatePipelineCompute::UnBindState()
	{	

		bindTextures(false);
	}
	void GLStatePipelineCompute::BindShader()
	{
		this->poShaderProgram->BindProgram();
	}
	void GLStatePipelineCompute::BindBufferUniforms()
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
	void GLStatePipelineCompute::BindTextures()
	{
		bindTextures(true);
		bindTextureImages(true);
	}

	void GLStatePipelineCompute::bindTextures(bool enable)
	{
		//CS
		if (this->mapTextureCS.size() > 0)
			bindTexture(this->mapTextureCS, enable);
	}
	void GLStatePipelineCompute::bindTexture(GLTexturePtrIDMap& mapTexture, bool enable)
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


	void GLStatePipelineCompute::bindTextureImages(bool enable)
	{
		//Image CS
		if (this->mapTextureImageCS.size() > 0)
			bindTextureImage(this->mapTextureImageCS, enable);
	}
	void GLStatePipelineCompute::bindTextureImage(GLTexturePtrIDMap& mapTexture, bool enable)
	{
		OpenGLWindow* pWindow = Base::GetWindowPtr();
		for (GLTexturePtrIDMap::iterator it = mapTexture.begin();
			 it != mapTexture.end(); ++it)
		{
			GLTexture* pTexture = it->second;
			uint nBindingIndex = it->first;
			pTexture->BindTextureImage(nBindingIndex, GL_WRITE_ONLY, enable);
		}
	}

}; //LostPeterOpenGL