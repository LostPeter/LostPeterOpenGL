/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2022-10-30
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "../include/PreDefine.h"
#include "../include/OpenGLDefine.h"

namespace LostPeterOpenGL
{   
////////////////////////////// Typedef /////////////////////////////
    


////////////////////////////// Enum ////////////////////////////////
    //WindowType
    static String s_nameWindows[] = 
    {
        "Main",             //0:    Main
        "Game",             //1:    Game
        "Scene",            //2:    Scene
    };
    const String& Util_GetWindowTypeName(WindowType type)
    {
        return s_nameWindows[(int)type];
    }
    const String& Util_GetWindowTypeName(int type)
    {
        return s_nameWindows[(int)type];
    }
    WindowType Util_ParseWindowType(const String& strName)
    {
        for (size_t i = 0; i < (int)Window_Count; i++)
        {
            if (s_nameWindows[i] == strName)
                return (WindowType)(i);
        }
        F_Assert(false && "Util_ParseWindowType: Wrong type name !")
        return Window_Main;
    }


    //PixelFormatComponentType
    static String s_namePixelFormatComponents[] = 
    {
        "ByteU",            //0: Byte unsigned
        "ByteS",            //1: Byte signed
        "ShortU",           //2: Short unsigned
        "ShortS",           //3: Short signed
        "IntU",             //4: Int unsigned
        "IntS",             //5: Int signed
        "LongU",            //6: Long unsigned
        "LongS",            //7: Long signed
        "Float16",          //8: Float 16
        "Float32",          //9: Float 32
        "Double"            //10: Double
    };
    const String& Util_GetPixelFormatComponentTypeName(PixelFormatComponentType type)
    {   
        return s_namePixelFormatComponents[(int)type];
    }
    const String& Util_GetPixelFormatComponentTypeName(int type)
    {
        return s_namePixelFormatComponents[type];
    }


    //ShaderSortType
    static String s_nameShaderSort[] = 
    {
        "Common",               //0:    Common
        "Platform",             //1:    Platform

    };
    const String& Util_GetShaderSortTypeName(ShaderSortType type)
    {
        return s_nameShaderSort[(int)type];
    }
    const String& Util_GetShaderSortTypeName(int type)
    {
        return s_nameShaderSort[(int)type];
    }
    ShaderSortType Util_ParseShaderSortType(const String& strName)
    {
        for (size_t i = 0; i < (int)ShaderSort_Platform; i++)
        {
            if (s_nameShaderSort[i] == strName)
                return (ShaderSortType)(i);
        }
        F_Assert(false && "Util_ParseShaderSortType: Wrong type name !")
        return ShaderSort_Common;
    }


////////////////////////////// OpenGL //////////////////////////////   
    void Util_CreateAttributeDescriptions(FMeshVertexType type)
    {
        switch ((int)type)
        {
            case F_MeshVertex_Pos2Color4: 
                {
                    Vertex_Pos2Color4::createAttributeDescriptions(); 
                    return;
                }
            case F_MeshVertex_Pos3Color4:
                {
                    Vertex_Pos3Color4::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Normal3:
                {
                    Vertex_Pos3Normal3::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Normal3Tex2:
                {
                    Vertex_Pos3Normal3Tex2::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos2Color4Tex2:
                {
                    Vertex_Pos2Color4Tex2::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Color4Tex2:
                {
                    Vertex_Pos3Color4Tex2::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Color4Normal3Tex2:
                {
                    Vertex_Pos3Color4Normal3Tex2::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Color4Normal3Tex4:
                {
                    Vertex_Pos3Color4Normal3Tex4::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Color4Normal3Tangent3Tex2:
                {
                    Vertex_Pos3Color4Normal3Tangent3Tex2::createAttributeDescriptions();
                    return;
                }
            case F_MeshVertex_Pos3Color4Normal3Tangent3Tex4:
                {
                    Vertex_Pos3Color4Normal3Tangent3Tex4::createAttributeDescriptions();
                    return;
                }
        }
        F_Assert(false && "Util_CreateAttributeDescriptions: Wrong type !")
    }

    GLenum Util_Transform2GLShaderType(FShaderType type)
    {
        switch ((int)type)
        {
            case F_Shader_Vertex:
                return GL_VERTEX_SHADER;
            case F_Shader_TessellationControl:
                return GL_TESS_CONTROL_SHADER;
            case F_Shader_TessellationEvaluation:
                return GL_TESS_EVALUATION_SHADER;
            case F_Shader_Geometry:
                return GL_GEOMETRY_SHADER;
            case F_Shader_Fragment:
                return GL_FRAGMENT_SHADER;
            case F_Shader_Compute:
        #if F_PLATFORM == F_PLATFORM_MAC
                F_Assert(false && "Util_Transform2GLShaderType: MacOS only support 4.1, can not support compute shader !")
                return GL_VERTEX_SHADER;
        #else
                return GL_COMPUTE_SHADER;
        #endif
        }
        F_Assert(false && "Util_Transform2GLShaderType: Wrong type !")
        return GL_VERTEX_SHADER;
    }
  

////////////////////////////// Class ///////////////////////////////
    MeshInfo::MeshInfo()
        : group(0)
        , nameMesh("")
        , pathMesh("")
        , typeMesh(F_Mesh_File)
        , typeVertex(F_MeshVertex_Pos3Color4Tex2)
        , typeGeometryType(F_MeshGeometry_EntityGrid)
        , pMeshCreateParam(nullptr)
        , isFlipY(false)
        , isTransformLocal(false)
        , matTransformLocal(FMath::ms_mat4Unit)
    {

    }
    MeshInfo::MeshInfo(const String& _nameMesh,
                       const String& _pathMesh,
                       FMeshType _typeMesh,
                       FMeshVertexType _typeVertex,
                       FMeshGeometryType _typeGeometryType,
                       FMeshCreateParam* _pMeshCreateParam,
                       bool _isFlipY,
                       bool _isTransformLocal,
                       const FMatrix4& _matTransformLocal)
        : group(0)
        , nameMesh(_nameMesh)
        , pathMesh(_pathMesh)
        , typeMesh(_typeMesh)
        , typeVertex(_typeVertex)
        , typeGeometryType(_typeGeometryType)
        , pMeshCreateParam(_pMeshCreateParam)
        , isFlipY(_isFlipY)
        , isTransformLocal(_isTransformLocal)
        , matTransformLocal(_matTransformLocal)
    {

    }
    MeshInfo::~MeshInfo()
    {
        F_DELETE(this->pMeshCreateParam)
    }


  


}; //LostPeterOpenGL