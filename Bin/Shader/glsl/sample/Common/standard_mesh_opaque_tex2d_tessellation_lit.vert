/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2026-06-06
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#version 330 core
#extension GL_ARB_shading_language_include : enable
#include "/glsl_common.glsl"

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inTexCoord;


out VSOutput
{
    vec4 outPosition;
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} vsOut;


void main()
{
    int instanceIndex = gl_InstanceID;

    vsOut.outPosition = vec4(inPosition, instanceIndex);
    vsOut.outColor = inColor;
    vsOut.outNormal = inNormal;
    vsOut.outTexCoord = inTexCoord;

    gl_Position = vsOut.outPosition;
}