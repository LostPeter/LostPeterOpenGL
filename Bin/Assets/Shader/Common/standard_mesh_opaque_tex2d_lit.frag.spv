/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2026-03-17
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

uniform sampler2D texSampler;

out vec4 outColor;

void main()
{
    vec3 color;

    MaterialConstants mat = materialConsts[floor(fragWorldPos.w + 0.5)];
    vec3 N = normalize(fragWorldNormal);

    vec3 colorLight;
    //Main Light
    uint viewIndex = 0;
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
    vec3 colorTexture = texture(texSampler, fragTexCoord).xyz;
    //VertexColor
    vec3 colorVertex = fragColor.xyz;

    //Final Color
    color = colorLight * colorTexture * colorVertex;

    outColor = vec4(color.xyz, 1.0);
}