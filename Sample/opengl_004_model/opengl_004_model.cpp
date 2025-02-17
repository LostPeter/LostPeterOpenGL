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
#include "opengl_004_model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/matrix4x4.h>
#include <assimp/postprocess.h>


static const int g_CountLen = 4;
static const char* g_pathModels[3 * g_CountLen] = 
{
    "plane",            "Assets/Mesh/Common/plane.fbx",                     "Assets/Texture/Common/texture2d.jpg", //plane
    "cube",             "Assets/Mesh/Common/cube.fbx",                      "Assets/Texture/Common/texture2d.jpg", //cube

    "viking_room",      "Assets/Mesh/Model/viking_room/viking_room.obj",    "Assets/Texture/Model/viking_room/viking_room.png", //viking_room
    "bunny",            "Assets/Mesh/Model/bunny/bunny.obj",                "Assets/Texture/Common/default_white.bmp", //bunny
};

static FVector3 g_tranformModels[3 * g_CountLen] = 
{
    FVector3(   0,   0,    0),     FVector3(     0, 0, 0),      FVector3(0.01f,  0.01f,  0.01f), //plane
    FVector3(   0,   0,    0),     FVector3(     0, 0, 0),      FVector3(0.01f,  0.01f,  0.01f), //cube

    FVector3(   0,   0,    0),     FVector3(     0, 0, 0),      FVector3( 1.0f,   1.0f,   1.0f), //viking_room
    FVector3(   0,   0,    0),     FVector3(     0, 180, 0),    FVector3( 1.0f,   1.0f,   1.0f), //bunny
};

static FMatrix4 g_tranformLocalModels[g_CountLen] = 
{
    FMath::ms_mat4Unit, //plane
    FMath::ms_mat4Unit, //cube

    FMath::RotateX(-90.0f), //viking_room
    FMath::ms_mat4Unit, //bunny
};
static FMatrix4 g_tranformLocal = FMath::ms_mat4Unit;
static bool g_isTranformLocalModels[] = 
{
    false, //plane
    false, //cube

    true, //viking_room
    false, //bunny
};
static bool g_isTranformLocal = false;

static bool g_isShowModels[g_CountLen] = 
{
    false, //plane
    false, //cube

    false, //viking_room
    false, //bunny
};
static void s_EnableShowModels(int index)
{
    g_isShowModels[index] = true;
}
static void s_DisableAllShowModels()
{
    for (int i = 0; i < g_CountLen; i++)
    {
        g_isShowModels[i] = false;
    }
}

static bool g_isFlipYModels[g_CountLen] = 
{
    true, //plane
    true, //cube

    false, //viking_room
    false, //bunny
};
static bool g_isFlipY = false;

static FVector3 g_vCameraPos[g_CountLen] = 
{
    FVector3(0.0f, 2.0f, -1.0f), //plane
    FVector3(0.0f, 2.0f, -1.0f), //cube

    FVector3(0.0f, 2.5f, -2.0f), //viking_room
    FVector3(0.0f, 3.0f, -1.5f), //bunny
};
static float g_fCameraFov[g_CountLen] =
{
    45.0f, //plane
    45.0f, //cube

    45.0f, //viking_room
    60.0f, //bunny
};


OpenGL_004_Model::OpenGL_004_Model(int width, int height, String name)
    : OpenGLWindow(width, height, name)
{
    this->cfg_isImgui = true;
    this->imgui_IsEnable = true;
    this->cfg_isRotate = true;

    this->poTypeVertex = F_MeshVertex_Pos3Color4Tex2;
    this->cfg_shaderVertex_Path = getShaderPathRelative("pos3_color4_tex2_ubo.vert.spv", ShaderSort_Common);
    this->cfg_shaderFragment_Path = getShaderPathRelative("pos3_color4_tex2_ubo.frag.spv", ShaderSort_Common);

    this->poDescriptorSetLayoutName = "PassConstants-ObjectConstants";

    resetSetting(0);
}

void OpenGL_004_Model::resetSetting(int index)
{
    s_DisableAllShowModels();
    s_EnableShowModels(index);
    g_tranformLocal = g_tranformLocalModels[index];
    g_isTranformLocal = g_isTranformLocalModels[index];
    g_isFlipY = g_isFlipYModels[index];
    this->cfg_cameraPos = g_vCameraPos[index];
    this->cfg_cameraFov = g_fCameraFov[index];

    this->poMatWorld = FMath::FromTRS(g_tranformModels[index * 3 + 0],
                                      g_tranformModels[index * 3 + 1],
                                      g_tranformModels[index * 3 + 2]); 
    this->cfg_model_Path = g_pathModels[index * 3 + 1]; 
    this->cfg_texture_Path = g_pathModels[index * 3 + 2];
}
void OpenGL_004_Model::changeModel(int index)
{
    //0> setting
    resetSetting(index);

    //1> Model
    cleanupVertexIndexBuffer();
    loadVertexIndexBuffer();

    //2> Texture
    cleanupTexture();
    loadTexture();
    updateDescriptorSets(this->pDescriptorSetLayout, this->poShaderProgram);
}


void OpenGL_004_Model::loadModel_Default()
{
    FMeshData meshData;
    meshData.bIsFlipY = g_isFlipY;
    unsigned int eMeshParserFlags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
    if (!FMeshDataLoader::LoadMeshData(this->cfg_model_Path, meshData, eMeshParserFlags))
    {
        F_LogError("*********************** OpenGL_004_Model::loadModel_Default load model failed: [%s] !", this->cfg_model_Path.c_str());
        return;
    }

    int count_vertex = (int)meshData.vertices.size();
    this->vertices.clear();
    this->vertices.reserve(count_vertex);
    for (int i = 0; i < count_vertex; i++)
    {
        FMeshVertex& vertex = meshData.vertices[i];
        FVertex_Pos3Color4Tex2 v;
        v.pos = vertex.pos;
        v.color = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
        v.texCoord = vertex.texCoord;

        if (g_isTranformLocal)
        {
            v.pos = FMath::Transform(g_tranformLocal, v.pos);
        }
        this->vertices.push_back(v);
    }

    int count_index = (int)meshData.indices32.size();
    this->indices.clear();
    this->indices.reserve(count_index);
    for (int i = 0; i < count_index; i++)
    {
        this->indices.push_back(meshData.indices32[i]);
    }

    this->poVertexCount = (uint32_t)this->vertices.size();
    this->poVertexBuffer_Size = this->poVertexCount * sizeof(FVertex_Pos3Color4Tex2);
    this->poVertexBuffer_Data = (uint8*)(&this->vertices[0]);
    this->poIndexCount = (uint32_t)this->indices.size();
    this->poIndexBuffer_Size = this->poIndexCount * sizeof(uint32_t);
    this->poIndexBuffer_Data = (uint8*)(&this->indices[0]);

    F_LogInfo("Vertex count: [%d], Index count: [%d] !", (int)this->vertices.size(), (int)this->indices.size());
}

void OpenGL_004_Model::buildObjectCB()
{
    ObjectConstants objectConstants;
    this->objectCBs.push_back(objectConstants);
}

bool OpenGL_004_Model::beginRenderImgui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    static bool windowOpened = true;
    ImGui::Begin("OpenGL_004_Model", &windowOpened, 0);
    {
        //0> Common
        commonConfig();
        
        //1> Model
        modelConfig();

    }
    ImGui::End();

    return true;
}
    void OpenGL_004_Model::modelConfig()
    {
        if (ImGui::CollapsingHeader("Model Settings"))
        {
            if (ImGui::BeginTable("split_model", 1))
            {
                static String s_Name = "Model - ";
                for (int i = 0; i < g_CountLen; i++)
                {
                    ImGui::TableNextColumn(); 
                    bool isShowModel = g_isShowModels[i];
                    String nameModel = s_Name + g_pathModels[3 * i + 0];
                    if (isShowModel)
                    {
                        nameModel += "(" + FUtilString::SaveSizeT(this->vertices.size()) + 
                                    "/" + FUtilString::SaveSizeT(this->indices.size()) +
                                    ")";
                    }
                    ImGui::Checkbox(nameModel.c_str(), &isShowModel);
                    if (!g_isShowModels[i] && isShowModel != g_isShowModels[i])
                    {
                        changeModel(i);
                    }
                }

                ImGui::EndTable();
            }
        }
    }

void OpenGL_004_Model::endRenderImgui()
{
    OpenGLWindow::endRenderImgui();

}