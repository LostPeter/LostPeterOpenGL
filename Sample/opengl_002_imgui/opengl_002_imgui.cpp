/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-07
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "PreInclude.h"
#include "opengl_002_imgui.h"


OpenGL_002_Imgui::OpenGL_002_Imgui(int width, int height, String name)
    : OpenGLWindow(width, height, name)
{
    this->cfg_isImgui = true;
    this->imgui_IsEnable = true;
    
    this->poTypeVertex = F_MeshVertex_Pos2Color4;
    this->cfg_shaderVertex_Path = getShaderPathRelative("notrans_pos2_color4.vert.spv", ShaderSort_Common);
    this->cfg_shaderFragment_Path = getShaderPathRelative("notrans_pos2_color4.frag.spv", ShaderSort_Common);
}

void OpenGL_002_Imgui::loadModel_Custom()
{
    //1> vertices
    this->vertices.push_back(FVertex_Pos2Color4(FVector2( 0.0f,  0.5f), FVector4(1.0f, 0.0f, 0.0f, 1.0f)));
    this->vertices.push_back(FVertex_Pos2Color4(FVector2(-0.5f, -0.5f), FVector4(0.0f, 0.0f, 1.0f, 1.0f)));
    this->vertices.push_back(FVertex_Pos2Color4(FVector2( 0.5f, -0.5f), FVector4(0.0f, 1.0f, 0.0f, 1.0f)));
    this->poVertexCount = (uint32_t)this->vertices.size();
    this->poVertexBuffer_Size = this->poVertexCount * sizeof(FVertex_Pos2Color4);
    this->poVertexBuffer_Data = (uint8*)(&this->vertices[0]);
    this->poIndexCount = 0;
    this->poIndexBuffer_Size = 0;
    this->poIndexBuffer_Data = nullptr;
}


bool OpenGL_002_Imgui::beginRenderImgui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    static bool windowOpened = true;
    static bool showDemoWindow = false;
    ImGui::Begin("OpenGL_002_Imgui", &windowOpened, 0);
    ImGui::Text("Frametime: %f", this->fFPS);
    ImGui::Checkbox("Show ImGui demo window", &showDemoWindow);
    ImGui::End();
    if (showDemoWindow) 
    {
        ImGui::ShowDemoWindow();
    }

    return true;
}

void OpenGL_002_Imgui::endRenderImgui()
{
    OpenGLWindow::endRenderImgui();

}