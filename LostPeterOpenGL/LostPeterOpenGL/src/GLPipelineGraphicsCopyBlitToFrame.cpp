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
#include "../include/Mesh.h"

namespace LostPeterOpenGL
{
    GLPipelineGraphicsCopyBlitToFrame::GLPipelineGraphicsCopyBlitToFrame(const String& namePipelineGraphics)
        : Base(namePipelineGraphics)

        , nameDescriptorSetLayout("")
        , poDescriptorSetLayoutNames(nullptr)
        

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
            
        }


    bool GLPipelineGraphicsCopyBlitToFrame::Init(Mesh* pMesh,
                                                 const String& descriptorSetLayout,
                                                 StringVector* pDescriptorSetLayoutNames)
    {
        this->pMeshBlit = pMesh;
        this->nameDescriptorSetLayout = descriptorSetLayout;

        //1> VkBuffer
        

        //2> VkPipeline
        {
            
        }

        //3> VkDescriptorSet
        

        return true;
    }
        bool GLPipelineGraphicsCopyBlitToFrame::createBufferCopyBlitObject()
        {
            
            return true;
        }

    void GLPipelineGraphicsCopyBlitToFrame::CleanupSwapChain()
    {
        
    }  

    void GLPipelineGraphicsCopyBlitToFrame::UpdateDescriptorSets()
    {
        
    }

    void GLPipelineGraphicsCopyBlitToFrame::UpdateBuffer(const CopyBlitObjectConstants& object)
    {

    }

}; //LostPeterOpenGL