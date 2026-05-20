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
#include "/glsl_lighting_lambert.glsl"

in vec4 fragWorldPos;
in vec4 fragColor;
in vec3 fragWorldNormal;
in vec2 fragTexCoord;

uniform sampler2D texSampler0;
uniform sampler2D texSampler1;

out vec4 outColor;

void main()
{
    vec3 color;

    MaterialConstant mat = materialConsts.mats[int(round(fragWorldPos.w))];
    vec3 N = normalize(fragWorldNormal);

	//BumpMap, Need Sample four times to get dx,dy
    float bumpMapType = mat.aTexLayers[1].indexTextureArray;
    if (bumpMapType == 1)
    {
        float bumpScale = mat.aTexLayers[1].texSpeedU;
        float bumpValueU = texture(texSampler1, fragTexCoord + vec2(-1.0 / mat.aTexLayers[1].texWidth, 0.0)).r -
                       texture(texSampler1, fragTexCoord + vec2(1.0 / mat.aTexLayers[1].texWidth, 0.0)).r;
        float bumpValueV = texture(texSampler1, fragTexCoord + vec2(0.0, -1.0 / mat.aTexLayers[1].texHeight)).r -
                        texture(texSampler1, fragTexCoord + vec2(0.0, 1.0 / mat.aTexLayers[1].texHeight)).r;
        N = vec3(N.x + bumpValueU * bumpScale, N.y * bumpValueV * bumpScale, N.z);
    }

    vec3 colorLight;
    //Main Light
    int viewIndex = 0;
    CameraConstants cam = passConsts.g_Cameras[viewIndex];
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
	if (bumpMapType == 0)
    {
        color = colorTexture;
    }
    else
    {
        color = colorLight * colorTexture * colorVertex;
    }

    outColor = vec4(color.xyz, 1.0);
}