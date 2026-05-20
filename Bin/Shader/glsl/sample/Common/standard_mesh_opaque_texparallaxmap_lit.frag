/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2026-05-09
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#version 330 core
#extension GL_ARB_shading_language_include : enable
#include "/glsl_common.glsl"
#include "/glsl_function.glsl"
#include "/glsl_lighting_lambert.glsl"

in vec4 fragWorldPos;
in vec4 fragColor;
in vec3 fragWorldNormal;
in vec3 fragWorldTangent;
in vec2 fragTexCoord;
in vec3 fragTSPos;
in vec3 fragTSEyePos;

uniform sampler2D texSampler0;
uniform sampler2D texSampler1;

out vec4 outColor;

void main()
{
    vec3 color;

    MaterialConstant mat = materialConsts.mats[int(round(fragWorldPos.w))];
	int viewIndex = 0;
    CameraConstants cam = passConsts.g_Cameras[viewIndex];

	vec3 V = normalize(cam.posEyeWorld - fragWorldPos.xyz);
    vec3 VT = normalize(fragTSEyePos - fragTSPos);
    vec3 N = vec3(0,0,1);
    float parallaxMapFlag = mat.aTexLayers[1].indexTextureArray;  
    vec2 uv = fragTexCoord;
    if (parallaxMapFlag == 1 ||
        parallaxMapFlag == 2)
    {
        N = Func_CalculateNormal(texSampler1,
                                 uv,
                                 fragWorldNormal,
                                 fragWorldTangent);
    }
    else if (parallaxMapFlag == 3)
    {
        float heightScale = mat.aTexLayers[1].texSpeedU;
        float parallaxBias = mat.aTexLayers[1].texSpeedV;
        uv = Func_ParallaxMapping_Common(texSampler1, 
										 uv, 
										 VT, 
										 heightScale, 
										 parallaxBias);
        N = Func_CalculateNormal(texSampler1,
                                 uv,
                                 fragWorldNormal,
                                 fragWorldTangent);
    }
    else if (parallaxMapFlag == 4)
    {
        float heightScale = mat.aTexLayers[1].texSpeedU;
        float numLayers = mat.aTexLayers[1].texSpeedW;
        uv = Func_ParallaxMapping_Steep(texSampler1, 
										uv, 
										VT, 
										heightScale, 
										numLayers);
        N = Func_CalculateNormal(texSampler1,
                                 uv,
                                 fragWorldNormal,
                                 fragWorldTangent);
    }
    else if (parallaxMapFlag == 5)
    {
        float heightScale = mat.aTexLayers[1].texSpeedU;
        float numLayers = mat.aTexLayers[1].texSpeedW;
        uv = Func_ParallaxMapping_Occlusion(texSampler1, 
											uv, 
											VT, 
											heightScale, 
											numLayers);
        N = Func_CalculateNormal(texSampler1,
                                 uv,
                                 fragWorldNormal,
                                 fragWorldTangent);
    }
    else
    {
        N = normalize(fragWorldNormal);
    }

    // Discard fragments at texture border
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) 
    {
		discard;
    }

    vec3 colorLight;
    //Main Light
    vec3 colorMainLight = calculate_Light(passConsts.g_AmbientLight.rgb,
                                          passConsts.g_MainLight,
                                          mat,
                                          fragWorldPos.xyz,
                                          cam.posEyeWorld, 
                                          N);
    colorLight = colorMainLight;

    //Additional Light



    //Texture
    vec3 colorTexture = texture(texSampler0, fragTexCoord).xyz;
    //VertexColor
    vec3 colorVertex = fragColor.xyz;

    //Final Color
    if (parallaxMapFlag == 0)
    {
        color = colorTexture;
    }
    else if (parallaxMapFlag == 1)
    {
        color = N;
    }
    else
    {
        color = colorLight * colorTexture * colorVertex;
    }

    outColor = vec4(color.xyz, 1.0);
}