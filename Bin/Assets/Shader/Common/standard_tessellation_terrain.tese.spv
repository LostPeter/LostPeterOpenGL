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

layout(triangles, fractional_odd_spacing, ccw) in;

in vec4 tesc_outPosition[];
in vec4 tesc_outColor[];
in vec3 tesc_outNormal[];
in vec2 tesc_outTexCoord[];
in float tesc_pnPatch[3*10];

out DSOutput {
    vec4 outWorldPos;
    vec4 outColor;
    vec3 outWorldNormal;
    vec2 outTexCoord;
};

struct PnPatch {
    float b210, b120, b021, b012, b102, b201, b111;
    float n110, n011, n101;
};

PnPatch GetPnPatch(float input[10]) {
    PnPatch res;
    res.b210 = input[0];
    res.b120 = input[1];
    res.b021 = input[2];
    res.b012 = input[3];
    res.b102 = input[4];
    res.b201 = input[5];
    res.b111 = input[6];
    res.n110 = input[7];
    res.n011 = input[8];
    res.n101 = input[9];
    return res;
}

void main() {
    vec3 uvw = gl_TessCoord.xyz;
    uint viewIndex = 0;
    TransformConstants trans = passConsts.g_Transforms[viewIndex];
    uint instanceIndex = uint(tesc_outPosition[0].w);
    ObjectConstant obj = objectConsts.objs[instanceIndex];
    TessellationConstant tess = tessellationConsts.tess[instanceIndex];

    float patch0[10], patch1[10], patch2[10];
    for (int i=0; i<10; i++) { patch0[i] = tesc_pnPatch[0*10+i]; }
    for (int i=0; i<10; i++) { patch1[i] = tesc_pnPatch[1*10+i]; }
    for (int i=0; i<10; i++) { patch2[i] = tesc_pnPatch[2*10+i]; }

    PnPatch pn0 = GetPnPatch(patch0);
    PnPatch pn1 = GetPnPatch(patch1);
    PnPatch pn2 = GetPnPatch(patch2);

    vec3 b210 = vec3(pn0.b210, pn1.b210, pn2.b210);
    vec3 b120 = vec3(pn0.b120, pn1.b120, pn2.b120);
    vec3 b021 = vec3(pn0.b021, pn1.b021, pn2.b021);
    vec3 b012 = vec3(pn0.b012, pn1.b012, pn2.b012);
    vec3 b102 = vec3(pn0.b102, pn1.b102, pn2.b102);
    vec3 b201 = vec3(pn0.b201, pn1.b201, pn2.b201);
    vec3 b111 = vec3(pn0.b111, pn1.b111, pn2.b111);

    vec3 n110 = normalize(vec3(pn0.n110, pn1.n110, pn2.n110));
    vec3 n011 = normalize(vec3(pn0.n011, pn1.n011, pn2.n011));
    vec3 n101 = normalize(vec3(pn0.n101, pn1.n101, pn2.n101));

	//Normal
    vec3 barNormal = uvw.z * tesc_outNormal[0]
                   + uvw.x * tesc_outNormal[1]
                   + uvw.y * tesc_outNormal[2];

    vec3 uvwSquared = uvw * uvw;
    vec3 uvwCubed   = uvwSquared * uvw;

    vec3 pnNormal = tesc_outNormal[0] * uvwSquared.z
                  + tesc_outNormal[1] * uvwSquared.x
                  + tesc_outNormal[2] * uvwSquared.y
                  + n110 * uvw.z * uvw.x
                  + n011 * uvw.x * uvw.y
                  + n101 * uvw.z * uvw.y;

    vec3 outNormal = tess.tessAlpha * pnNormal + (1.0 - tess.tessAlpha) * barNormal;

    //Position
    vec3 barPos = uvw.z * tesc_outPosition[0].xyz
                + uvw.x * tesc_outPosition[1].xyz
                + uvw.y * tesc_outPosition[2].xyz;

    uvwSquared *= 3.0;

    vec3 pnPos = tesc_outPosition[0].xyz * uvwCubed.z
               + tesc_outPosition[1].xyz * uvwCubed.x
               + tesc_outPosition[2].xyz * uvwCubed.y
               + b210 * uvwSquared.z * uvw.x
               + b120 * uvwSquared.x * uvw.z
               + b201 * uvwSquared.z * uvw.y
               + b021 * uvwSquared.x * uvw.y
               + b102 * uvwSquared.y * uvw.z
               + b012 * uvwSquared.y * uvw.x
               + b111 * 6.0 * uvw.x * uvw.y * uvw.z;

    vec3 finalPos = tess.tessAlpha * pnPos + (1.0 - tess.tessAlpha) * barPos;

    vec4 posWorld = obj.g_MatWorld * vec4(finalPos, 1.0);
    gl_Position   = trans.mat4Proj * trans.mat4View * posWorld;

    outWorldPos       = posWorld;
    outWorldPos.xyz  /= outWorldPos.w;
    outWorldPos.w     = float(instanceIndex);
    outColor          = uvw.z * tesc_outColor[0] + uvw.x * tesc_outColor[1] + uvw.y * tesc_outColor[2];
    outWorldNormal    = mat3(obj.g_MatWorld) * outNormal;
    outTexCoord       = uvw.z * tesc_outTexCoord[0] + uvw.x * tesc_outTexCoord[1] + uvw.y * tesc_outTexCoord[2];
}