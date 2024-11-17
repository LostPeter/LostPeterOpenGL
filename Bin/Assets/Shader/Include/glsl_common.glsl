/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-16
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _GLSL_COMMON_
#define _GLSL_COMMON_

#include "/glsl_constant.glsl"


///////////////////////////////// PassConstants /////////////////////////////////
//TransformConstants
struct TransformConstants
{
    mat4 mat4View;
    mat4 mat4View_Inv;
    mat4 mat4Proj;
    mat4 mat4Proj_Inv;
    mat4 mat4ViewProj;
    mat4 mat4ViewProj_Inv;
};

//CameraConstants
struct CameraConstants
{
    vec3 posEyeWorld;    
    float fNearZ;
    float fFarZ;
    float fReserved1;
    float fReserved2;
    float fReserved3;
};

//LightConstants
struct LightConstants
{
    vec4 lightCommon; // x: type; y: enable(1 or 0); z: 0-11; w: spotPower
    vec3 position; // directional/point/spot
    float falloffStart; // point/spot light only
    vec3 direction; // directional/spot light only
    float falloffEnd; // point/spot light only
    vec4 ambient; // ambient
    vec4 diffuse; // diffuse
    vec4 specular; // specular

    mat4 depthMVP; // depthMVP
};

//PassConstants
struct PassConstants
{
    //TransformConstants
    TransformConstants g_Transforms[2]; //0: Eye Left(Main); 1: Eye Right
    //CameraConstants
    CameraConstants g_Cameras[2]; //0: Eye Left(Main); 1: Eye Right
    
    //TimeConstants
    float g_TotalTime;
    float g_DeltaTime;
    float g_Pad1;
    float g_Pad2;

    //RenderTarget
    vec2 g_RenderTargetSize;
    vec2 g_RenderTargetSize_Inv;

    //Material
    vec4 g_AmbientLight;
    
    //Light
    LightConstants g_MainLight;
    LightConstants g_AdditionalLights[MAX_LIGHT_COUNT];
};


///////////////////////////////// ObjectConstants ///////////////////////////////
//ObjectConstants
struct ObjectConstants
{
    mat4 g_MatWorld;
};

//OutlineObjectConstants
struct OutlineObjectConstants
{
    mat4 g_MatWorld;

    vec4 outlineColor;
    float outlineWidth;
};

//CameraAxisObjectConstants
struct CameraAxisObjectConstants
{
    mat4 g_MatWorld;
    vec4 color;
};

//CoordinateAxisObjectConstants
struct CoordinateAxisObjectConstants
{
    mat4 g_MatWorld;
    vec4 color;
};

//GridObjectConstants
struct GridObjectConstants
{
    mat4 g_MatWorld;
    vec4 color;
};

//LineFlat2DObjectConstants
struct LineFlat2DObjectConstants
{
    vec4 color;
};

//LineFlat3DObjectConstants
struct LineFlat3DObjectConstants
{
    mat4 g_MatWorld;
    vec4 color;
};

//CopyBlitObjectConstants
struct CopyBlitObjectConstants
{
    float offsetX;
    float offsetY;
    float scaleX;
    float scaleY;
};



///////////////////////////////// MaterialConstants /////////////////////////////
//TextureConstants
struct TextureConstants
{
    float texWidth;
    float texHeight;
    float texDepth;
    float indexTextureArray;

    float texSpeedU;
    float texSpeedV;
    float texSpeedW;
    float reserve0;

    float texChunkMaxX;
    float texChunkMaxY;
    float texChunkIndexX;
    float texChunkIndexY;
};

//MaterialConstants
struct MaterialConstants
{
    vec4 factorAmbient;
    vec4 factorDiffuse;
    vec4 factorSpecular;

    float shininess;
    float alpha;
    float lighting;
    float castshadow;
    float receiveshadow;
    float reserve0;
    float reserve1;
    float reserve2;

    TextureConstants aTexLayers[MAX_TEXTURE_COUNT];
};


///////////////////////////////// InstanceConstants /////////////////////////////
//InstanceConstants
struct InstanceConstants
{
    int offsetObject;
    int indexObject;
    int offsetMaterial;
    int indexMaterial;
};


///////////////////////////////// ComputeConstants //////////////////////////////
struct TextureCopyConstants
{
    //[x,y,z,w] = [w,h,mip,processLinear]
    vec4 texInfo;
	vec4 texOffset;
	vec4 texIndexArray;
	vec4 texClearColor;
};


///////////////////////////////// GeometryConstants /////////////////////////////
//GeometryConstants
struct GeometryConstants
{
    float width;
    float height;
    float length;
	float reserve;
};


///////////////////////////////// TessellationConstants /////////////////////////
struct TessellationConstants
{
    float tessLevelOuter;
    float tessLevelInner;
    float tessAlpha;
    float tessStrength;
};


///////////////////////////////// GeometryConstants /////////////////////////////



///////////////////////////////// TerrainConstants //////////////////////////////
struct TerrainSplatConstants
{
    float splatSizeX; //size x
    float splatSizeY; //size y
    float splatOffsetX; //offset x
    float splatOffsetY; //offset y

    vec4 diffuseRemapScale; //diffuse remap scale
    float normalRemapScale; //normal remap scale
    float reserve0;
    float reserve1;
    float reserve2;
};
struct TerrainConstants
{
    mat4 matWorld; //Matrix world 
    float textureX; //HeightMap/NarmalMap Texture Size X
    float textureZ; //HeightMap/NarmalMap Texture Size Z
    float textureX_Inverse; //1/textureX
    float textureZ_Inverse; //1/textureZ
    float heightStart; //Height Low Start 
    float heightMax; //Height Max (from heightStart, heightEnd = heightStart + heightMax)
    float terrainSizeX; //Terrain Size X
    float terrainSizeZ; //Terrain Size Z

    TerrainSplatConstants aSplats[MAX_TERRAIN_SPLAT_COUNT];
};
struct TerrainObjectConstants
{
    float offsetX; //Instance offset X
    float offsetZ; //Instance offset Z
};


//////////////////////////////// CullConstants //////////////////////////////////
struct CullConstants
{
    uint nMaxLodCount; //Max Lod Count
    uint nMaxRenderCount; //Max Render Count
    uint nMaxObjectCount; //Max Object Count
    uint nIsNoCulling; //Is No Culling?

    mat4 mat4VPLast;  //VP Last
    vec4 v4FrustumPlanes[MAX_FRUSTUM_PLANE_COUNT]; //6 Frustum Planes
    vec4 v4ParamComon[4]; //Param common (0: CameraPos; 1: Min FrustumPlanes; 2: Max FrustumPlanes; 3: Hiz ScreenRes)
    vec4 v4ParamRender; //Param Render
    vec4 v4PosPlayer; //Pos Player
};
struct CullObjectConstants
{
    vec4 vPos; //xyz = pos, w = object offset
    vec4 vExt; //xyz = ext, w = isNoHizTest
    uint nRenderIndex; //Render Index
    uint nRenderCount; //Render Count
    uint nObjectOffset; //Object Offset
    uint nIsNoHizTest; //IsNoHizTest
};
struct CullObjectInstanceConstants
{
    mat4 mat4Object2World;
};
struct CullInstanceConstants
{
    uint nObjectOffset;
    float reserve0;
    float reserve1;
    float reserve2;
};

//////////////////////////////// HizDepthConstants //////////////////////////////
struct HizDepthConstants
{
    vec4 vRtDepthSize;
};



#endif /* _GLSL_COMMON_*/