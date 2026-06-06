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

in vec4 vs_outPosition[];
in vec4 vs_outColor[];
in vec3 vs_outNormal[];
in vec2 vs_outTexCoord[];

out vec4 tesc_outPosition[];
out vec4 tesc_outColor[];
out vec3 tesc_outNormal[];
out vec2 tesc_outTexCoord[];
out float tesc_pnPatch[3*10];

struct PnPatch {
    float b210;
    float b120;
    float b021;
    float b012;
    float b102;
    float b201;
    float b111;
    float n110;
    float n011;
    float n101;
};

void SetPnPatch(out float output[10], PnPatch patch) {
    output[0] = patch.b210;
    output[1] = patch.b120;
    output[2] = patch.b021;
    output[3] = patch.b012;
    output[4] = patch.b102;
    output[5] = patch.b201;
    output[6] = patch.b111;
    output[7] = patch.n110;
    output[8] = patch.n011;
    output[9] = patch.n101;
}

float wij(vec4 iPos, vec3 iNormal, vec4 jPos) {
    return dot(jPos.xyz - iPos.xyz, iNormal);
}

float vij(vec4 iPos, vec3 iNormal, vec4 jPos, vec3 jNormal) {
    vec3 Pj_minus_Pi = jPos.xyz - iPos.xyz;
    vec3 Ni_plus_Nj  = iNormal + jNormal;
    return 2.0 * dot(Pj_minus_Pi, Ni_plus_Nj) / dot(Pj_minus_Pi, Pj_minus_Pi);
}

void main() {
    uint idx = gl_InvocationID;

    tesc_outPosition[idx] = vs_outPosition[idx];
    tesc_outColor[idx]    = vs_outColor[idx];
    tesc_outNormal[idx]   = vs_outNormal[idx];
    tesc_outTexCoord[idx] = vs_outTexCoord[idx];

    if (idx == 0) {
        uint instanceIndex = uint(vs_outPosition[0].w + 0.5);
        TessellationConstant tess = tessellationConsts.tes[instanceIndex];
        gl_TessLevelOuter[0] = tess.tessLevelOuter;
        gl_TessLevelOuter[1] = tess.tessLevelOuter;
        gl_TessLevelOuter[2] = tess.tessLevelOuter;
        gl_TessLevelInner[0] = tess.tessLevelInner;
    }

    float P0 = vs_outPosition[0][idx];
    float P1 = vs_outPosition[1][idx];
    float P2 = vs_outPosition[2][idx];
    float N0 = vs_outNormal[0][idx];
    float N1 = vs_outNormal[1][idx];
    float N2 = vs_outNormal[2][idx];

    PnPatch pnPatch;
    pnPatch.b210 = (2.0 * P0 + P1 - wij(vs_outPosition[0], vs_outNormal[0], vs_outPosition[1]) * N0) / 3.0;
    pnPatch.b120 = (2.0 * P1 + P0 - wij(vs_outPosition[1], vs_outNormal[1], vs_outPosition[0]) * N1) / 3.0;
    pnPatch.b021 = (2.0 * P1 + P2 - wij(vs_outPosition[1], vs_outNormal[1], vs_outPosition[2]) * N1) / 3.0;
    pnPatch.b012 = (2.0 * P2 + P1 - wij(vs_outPosition[2], vs_outNormal[2], vs_outPosition[1]) * N2) / 3.0;
    pnPatch.b102 = (2.0 * P2 + P0 - wij(vs_outPosition[2], vs_outNormal[2], vs_outPosition[0]) * N2) / 3.0;
    pnPatch.b201 = (2.0 * P0 + P2 - wij(vs_outPosition[0], vs_outNormal[0], vs_outPosition[2]) * N0) / 3.0;

    float E = (pnPatch.b210 + pnPatch.b120 + pnPatch.b021 + pnPatch.b012 + pnPatch.b102 + pnPatch.b201) / 6.0;
    float V = (P0 + P1 + P2) / 3.0;
    pnPatch.b111 = E + (E - V) * 0.5;

    pnPatch.n110 = N0 + N1 - vij(vs_outPosition[0], vs_outNormal[0], vs_outPosition[1], vs_outNormal[1]) * (P1 - P0);
    pnPatch.n011 = N1 + N2 - vij(vs_outPosition[1], vs_outNormal[1], vs_outPosition[2], vs_outNormal[2]) * (P2 - P1);
    pnPatch.n101 = N2 + N0 - vij(vs_outPosition[2], vs_outNormal[2], vs_outPosition[0], vs_outNormal[0]) * (P0 - P2);

    float tmp[10];
    SetPnPatch(tmp, pnPatch);

    for (int i = 0; i < 10; i++) {
        tesc_pnPatch[idx * 10 + i] = tmp[i];
    }
}