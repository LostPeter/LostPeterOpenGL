/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2023-10-04
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _EDITOR_BASE_H_
#define _EDITOR_BASE_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport EditorBase : public Base
    {
    public:
        EditorBase(const String& nameEditor);
        virtual ~EditorBase();
    
    public:
        //Meshes
        MeshInfoPtrVector aMeshInfos;
        MeshPtrVector aMeshes;
        MeshPtrMap mapMeshes;

        //Shaders
        ShaderModuleInfoVector aShaderModuleInfos;
        GLShaderPtrVector aShaders;
        GLShaderPtrMap mapShaders;

        //DescriptorSetLayouts
        String nameDescriptorSetLayout;
		DescriptorSetLayout* pDescriptorSetLayout;

        //GLStatePipelineGraphics
        GLStatePipelineGraphics* pPipelineGraphics;

	public:
		GLShader* GetShader(const String& nameShader);

    public:
        virtual void Destroy() = 0;
			virtual void destroyInternal();

        virtual void Init();

        virtual void UpdateCBs() = 0;
		virtual void BindUniformPass() { }
        virtual void Draw();

    public:
        virtual void CleanupSwapChain();
        virtual void RecreateSwapChain();

    protected:
        virtual void initConfigs() = 0;
        virtual void initMeshes();
        virtual void initShaders();
        virtual void initBufferUniforms() = 0;
        virtual void initDescriptorSetLayout();
        virtual void initPipelineLayout();
        virtual void initPipelineGraphics() = 0;
        virtual void updateDescriptorSets_Graphics() = 0;

        virtual void destroyMeshes();
        virtual void destroyShaders();
        virtual void destroyBufferUniforms() = 0;
        virtual void destroyPipelineGraphics();
        virtual void destroyPipelineLayout();
        virtual void destroyDescriptorSetLayout();
    };

}; //LostPeterOpenGL

#endif