/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-10
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "PreInclude.h"
#include "opengl_007_stencil.h"


OpenGL_007_Stencil::OpenGL_007_Stencil(int width, int height, String name)
    : OpenGLWindow(width, height, name)
{
    this->cfg_isImgui = true;
    this->imgui_IsEnable = true;

    this->poTypeVertex = F_MeshVertex_Pos2Color4Tex2;
    this->cfg_shaderVertex_Path = getShaderPathRelative("notrans_pos2_color4_tex2.vert.spv", ShaderSort_Common);
    this->cfg_shaderFragment_Path = getShaderPathRelative("notrans_pos2_color4_tex2.frag.spv", ShaderSort_Common);
    this->cfg_texture_Path = "Assets/Texture/Common/texture2d.jpg";
}

void OpenGL_007_Stencil::loadModel_Custom()
{
    //1> vertices
    this->vertices.push_back(FVertex_Pos2Color4Tex2(FVector2(-0.5f,  0.5f), FVector4(1.0f, 1.0f, 1.0f, 1.0f), FVector2(0.0f, 0.0f)));
    this->vertices.push_back(FVertex_Pos2Color4Tex2(FVector2( 0.5f,  0.5f), FVector4(1.0f, 1.0f, 1.0f, 1.0f), FVector2(1.0f, 0.0f)));
    this->vertices.push_back(FVertex_Pos2Color4Tex2(FVector2( 0.5f, -0.5f), FVector4(1.0f, 1.0f, 1.0f, 1.0f), FVector2(1.0f, 1.0f)));
    this->vertices.push_back(FVertex_Pos2Color4Tex2(FVector2( 0.5f, -0.5f), FVector4(1.0f, 1.0f, 1.0f, 1.0f), FVector2(1.0f, 1.0f)));
    this->vertices.push_back(FVertex_Pos2Color4Tex2(FVector2(-0.5f, -0.5f), FVector4(1.0f, 1.0f, 1.0f, 1.0f), FVector2(0.0f, 1.0f)));
    this->vertices.push_back(FVertex_Pos2Color4Tex2(FVector2(-0.5f,  0.5f), FVector4(1.0f, 1.0f, 1.0f, 1.0f), FVector2(0.0f, 0.0f)));
    this->poVertexCount = (uint32_t)this->vertices.size();
    this->poVertexBuffer_Size = this->poVertexCount * sizeof(FVertex_Pos2Color4Tex2);
    this->poVertexBuffer_Data = (uint8*)(&this->vertices[0]);
    this->poIndexCount = 0;
    this->poIndexBuffer_Size = 0;
    this->poIndexBuffer_Data = nullptr;
}


bool OpenGL_007_Stencil::beginRenderImgui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    static bool windowOpened = true;
    ImGui::Begin("OpenGL_007_Stencil", &windowOpened, 0);
    {
        //0> Common
        commonConfig();
        
    }
    ImGui::End();

    return true;
}

void OpenGL_007_Stencil::endRenderImgui()
{
    OpenGLWindow::endRenderImgui();

}