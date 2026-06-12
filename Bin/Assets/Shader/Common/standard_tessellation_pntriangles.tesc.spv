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

#version 410 core
#extension GL_ARB_tessellation_shader : require
#extension GL_ARB_shading_language_include : enable

#include "/glsl_common.glsl"

layout(vertices = 3) out;

in VSOutput
{
    vec4 outPosition;
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} IN[];

out vec4 tesc_outPosition[];
out vec4 tesc_outColor[];
out vec3 tesc_outNormal[];
out vec2 tesc_outTexCoord[];

patch out vec3 tesc_pnPatchPos[7];
patch out vec3 tesc_pnPatchNormal[3];

float wij(vec3 Pi, vec3 Ni, vec3 Pj)
{
    return dot(Pj - Pi, Ni);
}

float vij(vec3 Pi, vec3 Ni, vec3 Pj, vec3 Nj)
{
    vec3 D = Pj - Pi;
    return 2.0 * dot(D, Ni + Nj) / dot(D, D);
}

void main()
{
    tesc_outPosition[gl_InvocationID] =
        IN[gl_InvocationID].outPosition;

    tesc_outColor[gl_InvocationID] =
        IN[gl_InvocationID].outColor;

    tesc_outNormal[gl_InvocationID] =
        IN[gl_InvocationID].outNormal;

    tesc_outTexCoord[gl_InvocationID] =
        IN[gl_InvocationID].outTexCoord;

    barrier();

    if(gl_InvocationID == 0)
    {
        uint instanceIndex =
            uint(IN[0].outPosition.w + 0.5);

        TessellationConstant tess =
            tessellationConsts.tes[instanceIndex];

        gl_TessLevelOuter[0] = tess.tessLevelOuter;
        gl_TessLevelOuter[1] = tess.tessLevelOuter;
        gl_TessLevelOuter[2] = tess.tessLevelOuter;

        gl_TessLevelInner[0] = tess.tessLevelInner;

        vec3 P0 = IN[0].outPosition.xyz;
        vec3 P1 = IN[1].outPosition.xyz;
        vec3 P2 = IN[2].outPosition.xyz;

        vec3 N0 = normalize(IN[0].outNormal);
        vec3 N1 = normalize(IN[1].outNormal);
        vec3 N2 = normalize(IN[2].outNormal);

        vec3 b210 =
            (2.0 * P0 + P1 -
             wij(P0,N0,P1) * N0) / 3.0;

        vec3 b120 =
            (2.0 * P1 + P0 -
             wij(P1,N1,P0) * N1) / 3.0;

        vec3 b021 =
            (2.0 * P1 + P2 -
             wij(P1,N1,P2) * N1) / 3.0;

        vec3 b012 =
            (2.0 * P2 + P1 -
             wij(P2,N2,P1) * N2) / 3.0;

        vec3 b102 =
            (2.0 * P2 + P0 -
             wij(P2,N2,P0) * N2) / 3.0;

        vec3 b201 =
            (2.0 * P0 + P2 -
             wij(P0,N0,P2) * N0) / 3.0;

        vec3 E =
            (b210+b120+b021+
             b012+b102+b201) / 6.0;

        vec3 V =
            (P0+P1+P2) / 3.0;

        vec3 b111 =
            E + (E - V) * 0.5;

        vec3 n110 =
            N0 + N1 -
            vij(P0,N0,P1,N1)*(P1-P0);

        vec3 n011 =
            N1 + N2 -
            vij(P1,N1,P2,N2)*(P2-P1);

        vec3 n101 =
            N2 + N0 -
            vij(P2,N2,P0,N0)*(P0-P2);

        tesc_pnPatchPos[0] = b210;
        tesc_pnPatchPos[1] = b120;
        tesc_pnPatchPos[2] = b021;
        tesc_pnPatchPos[3] = b012;
        tesc_pnPatchPos[4] = b102;
        tesc_pnPatchPos[5] = b201;
        tesc_pnPatchPos[6] = b111;

        tesc_pnPatchNormal[0] = n110;
        tesc_pnPatchNormal[1] = n011;
        tesc_pnPatchNormal[2] = n101;
    }
}