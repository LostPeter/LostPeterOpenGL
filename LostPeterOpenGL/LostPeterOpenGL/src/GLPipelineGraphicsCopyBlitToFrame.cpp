/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-15
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "../include/GLPipelineGraphicsCopyBlitToFrame.h"
#include "../include/OpenGLWindow.h"
#include "../include/GLBufferUniform.h"
#include "../include/GLShader.h"
#include "../include/GLShaderProgram.h"
#include "../include/GLStatePipelineGraphics.h"
#include "../include/Mesh.h"

namespace LostPeterOpenGL
{
    GLPipelineGraphicsCopyBlitToFrame::GLPipelineGraphicsCopyBlitToFrame(const String& namePipelineGraphics)
        : Base(namePipelineGraphics)

        , nameDescriptorSetLayout("")
        , poDescriptorSetLayoutNames(nullptr)

        , pBuffer_CopyBlit(nullptr)
        
        , pStatePipelineGraphics(nullptr)
        , pMeshBlit(nullptr)
    {

    }

    GLPipelineGraphicsCopyBlitToFrame::~GLPipelineGraphicsCopyBlitToFrame()
    {
        Destroy();
    }

    void GLPipelineGraphicsCopyBlitToFrame::Destroy()
    {
        CleanupSwapChain();
        destroyBufferCopyBlitObject();
    }
        void GLPipelineGraphicsCopyBlitToFrame::destroyBufferCopyBlitObject()
        {
            F_DELETE(this->pBuffer_CopyBlit)

        }


    bool GLPipelineGraphicsCopyBlitToFrame::Init(GLShader* pShaderVertex,
                                                 GLShader* pShaderFragment,
                                                 Mesh* pMesh,
                                                 const String& descriptorSetLayout,
                                                 StringVector* pDescriptorSetLayoutNames)
    {
        this->pMeshBlit = pMesh;
        this->nameDescriptorSetLayout = descriptorSetLayout;
        this->poDescriptorSetLayoutNames = pDescriptorSetLayoutNames;

        //1> GLBufferUniform
        if (this->pBuffer_CopyBlit == nullptr)
        {
            if (!createBufferCopyBlitObject())
            {
                F_LogError("*********************** GLPipelineGraphicsCopyBlitToFrame::Init: createBufferCopyBlitObject failed !");
                return false;
            }
        }

        //2> GLStatePipelineGraphics
        {
			OpenGLWindow* pWindow = Base::GetWindowPtr();
            String nameStatePipelineGraphics = "StatePipelineGraphics-" + GetName();
			this->pStatePipelineGraphics = pWindow->createStatePipelineGraphics(nameStatePipelineGraphics,
																				pShaderVertex,
																				nullptr,
																				nullptr,
																				nullptr,
																				pShaderFragment,
																				pWindow->HasConfig_DepthStencil(),
																				GL_LEQUAL,
																				false,
																				false,
																				false,
																				GL_LEQUAL,
																				GL_KEEP,
																				GL_KEEP,
																				GL_KEEP,
																				0,
																				0,
																				false,
																				GL_ONE,
																				GL_ZERO,
																				GL_FUNC_ADD,
																				GL_ONE,
																				GL_ZERO,
																				GL_FUNC_ADD,
																				true,
																				true,
																				true,
																				true);
			if (this->pStatePipelineGraphics == nullptr)
			{
				F_LogError("*********************** GLPipelineGraphicsCopyBlitToFrame::Init: StatePipelineGraphics failed, name: [%s] !", nameStatePipelineGraphics.c_str());
				return false;
			}
        }

        //3> Binding
        UpdateDescriptorSets();

        return true;
    }
        bool GLPipelineGraphicsCopyBlitToFrame::createBufferCopyBlitObject()
        {
            this->objectCB_CopyBlit.offsetX = 0.0f;
            this->objectCB_CopyBlit.offsetY = 0.0f;
            this->objectCB_CopyBlit.scaleX = 2.0f;
            this->objectCB_CopyBlit.scaleY = 2.0f;
            Base::GetWindowPtr()->createBufferUniform("CopyBlitObjectConstants-" + this->name, 
                                                      DescriptorSet_ObjectCopyBlit,
                                                      GL_DYNAMIC_DRAW,
                                                      sizeof(CopyBlitObjectConstants), 
                                                      (uint8*)(&this->objectCB_CopyBlit), 
                                                      false);
            return true;
        }

    void GLPipelineGraphicsCopyBlitToFrame::CleanupSwapChain()
    {
        this->poDescriptorSetLayoutNames = nullptr;
        F_DELETE(this->pStatePipelineGraphics)
    }  

    void GLPipelineGraphicsCopyBlitToFrame::UpdateDescriptorSets()
    {
        String nameCopyBlit = (*this->poDescriptorSetLayoutNames)[0];
        this->pStatePipelineGraphics->SetUniformBlockBinding(nameCopyBlit, DescriptorSet_ObjectCopyBlit);
    }

    void GLPipelineGraphicsCopyBlitToFrame::UpdateBuffer()
    {
        if (this->pBuffer_CopyBlit != nullptr)
        {
            this->pBuffer_CopyBlit->Update(0, sizeof(CopyBlitObjectConstants), (uint8*)(&this->objectCB_CopyBlit));
        }
    }
    void GLPipelineGraphicsCopyBlitToFrame::UpdateBuffer(const CopyBlitObjectConstants& object)
    {
        this->objectCB_CopyBlit = object;
        UpdateBuffer();
    }

}; //LostPeterOpenGL