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
    vec4 outPosition;   // xyz: Object Pos; w: instanceIndex
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} IN[];

out vec4 tesc_outPosition[];
out vec4 tesc_outColor[];
out vec3 tesc_outNormal[];
out vec2 tesc_outTexCoord[];
out float tesc_pnPatch[];


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

void SetPnPatch(out float outVals[10], PnPatch pnPatch) {
    outVals[0] = pnPatch.b210;
    outVals[1] = pnPatch.b120;
    outVals[2] = pnPatch.b021;
    outVals[3] = pnPatch.b012;
    outVals[4] = pnPatch.b102;
    outVals[5] = pnPatch.b201;
    outVals[6] = pnPatch.b111;
    outVals[7] = pnPatch.n110;
    outVals[8] = pnPatch.n011;
    outVals[9] = pnPatch.n101;
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

    tesc_outPosition[idx] = IN[idx].outPosition;
    tesc_outColor[idx]    = IN[idx].outColor;
    tesc_outNormal[idx]   = IN[idx].outNormal;
    tesc_outTexCoord[idx] = IN[idx].outTexCoord;

    if (idx == 0) {
        uint instanceIndex = uint(IN[0].outPosition.w + 0.5);
        TessellationConstant tess = tessellationConsts.tes[instanceIndex];

        gl_TessLevelOuter[0] = tess.tessLevelOuter;
        gl_TessLevelOuter[1] = tess.tessLevelOuter;
        gl_TessLevelOuter[2] = tess.tessLevelOuter;
        gl_TessLevelInner[0] = tess.tessLevelInner;
    }

    float P0 = IN[0].outPosition[idx];
    float P1 = IN[1].outPosition[idx];
    float P2 = IN[2].outPosition[idx];
    float N0 = IN[0].outNormal[idx];
    float N1 = IN[1].outNormal[idx];
    float N2 = IN[2].outNormal[idx];

    PnPatch pnPatch;
    pnPatch.b210 = (2.0 * P0 + P1 - wij(IN[0].outPosition, IN[0].outNormal, IN[1].outPosition) * N0) / 3.0;
    pnPatch.b120 = (2.0 * P1 + P0 - wij(IN[1].outPosition, IN[1].outNormal, IN[0].outPosition) * N1) / 3.0;
    pnPatch.b021 = (2.0 * P1 + P2 - wij(IN[1].outPosition, IN[1].outNormal, IN[2].outPosition) * N1) / 3.0;
    pnPatch.b012 = (2.0 * P2 + P1 - wij(IN[2].outPosition, IN[2].outNormal, IN[1].outPosition) * N2) / 3.0;
    pnPatch.b102 = (2.0 * P2 + P0 - wij(IN[2].outPosition, IN[2].outNormal, IN[0].outPosition) * N2) / 3.0;
    pnPatch.b201 = (2.0 * P0 + P2 - wij(IN[0].outPosition, IN[0].outNormal, IN[2].outPosition) * N0) / 3.0;

    float E = (pnPatch.b210 + pnPatch.b120 + pnPatch.b021 + pnPatch.b012 + pnPatch.b102 + pnPatch.b201) / 6.0;
    float V = (P0 + P1 + P2) / 3.0;
    pnPatch.b111 = E + (E - V) * 0.5;

    pnPatch.n110 = N0 + N1 - vij(IN[0].outPosition, IN[0].outNormal, IN[1].outPosition, IN[1].outNormal) * (P1 - P0);
    pnPatch.n011 = N1 + N2 - vij(IN[1].outPosition, IN[1].outNormal, IN[2].outPosition, IN[2].outNormal) * (P2 - P1);
    pnPatch.n101 = N2 + N0 - vij(IN[2].outPosition, IN[2].outNormal, IN[0].outPosition, IN[0].outNormal) * (P0 - P2);

    float tempPatch[10];
    SetPnPatch(tempPatch, pnPatch);
	for (int i = 0; i < 10; i++) {
		tesc_pnPatch[i] = tempPatch[i];
	}
}