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

layout(vertices = 3) out;

in VSOutput
{
    vec4 outPosition;   // xyz: Object Pos; w: instanceIndex
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} IN[];

out HSOutput
{
    vec4 outPosition;
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} OUT[];


void main()
{
    if (gl_InvocationID == 0)
    {
        int instanceIndex = int(round(IN[0].outPosition.w));
        TessellationConstant tess = tessellationConsts.tes[instanceIndex];

        gl_TessLevelOuter[0] = tess.tessLevelOuter;
        gl_TessLevelOuter[1] = tess.tessLevelOuter;
        gl_TessLevelOuter[2] = tess.tessLevelOuter;
        gl_TessLevelInner[0] = tess.tessLevelInner;
    }

    OUT[gl_InvocationID].outPosition = IN[gl_InvocationID].outPosition;
    OUT[gl_InvocationID].outColor    = IN[gl_InvocationID].outColor;
    OUT[gl_InvocationID].outNormal   = IN[gl_InvocationID].outNormal;
    OUT[gl_InvocationID].outTexCoord = IN[gl_InvocationID].outTexCoord;
}
