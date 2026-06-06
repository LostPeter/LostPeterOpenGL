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
in float tesc_pnPatch[];

out vec4 fragWorldPos;
out vec4 fragColor;
out vec3 fragWorldNormal;
out vec2 fragTexCoord;

out DSOutput {
    vec4 outWorldPos;
    vec4 outColor;
    vec3 outWorldNormal;
    vec2 outTexCoord;
};

struct PnPatch {
    float b210; float b120; float b021; float b012; float b102; float b201; float b111;
    float n110; float n011; float n101;
};

PnPatch GetPnPatch(float pnPatch[10]) {
    PnPatch output;
    output.b210 = pnPatch[0];
    output.b120 = pnPatch[1];
    output.b021 = pnPatch[2];
    output.b012 = pnPatch[3];
    output.b102 = pnPatch[4];
    output.b201 = pnPatch[5];
    output.b111 = pnPatch[6];
    output.n110 = pnPatch[7];
    output.n011 = pnPatch[8];
    output.n101 = pnPatch[9];
    return output;
}

void main() {
    vec3 uvw = gl_TessCoord.xyz;

    uint viewIndex = 0;
    TransformConstants trans = passConsts.g_Transforms[viewIndex];
    uint instanceIndex = uint(tesc_outPosition[0].w + 0.5);
    ObjectConstant obj = objectConsts.objs[instanceIndex];
    TessellationConstant tess = tessellationConsts.tes[instanceIndex];

    float patch0[10], patch1[10], patch2[10];
    for(int i=0;i<10;i++) { patch0[i] = tesc_pnPatch[0*10+i]; }
    for(int i=0;i<10;i++) { patch1[i] = tesc_pnPatch[1*10+i]; }
    for(int i=0;i<10;i++) { patch2[i] = tesc_pnPatch[2*10+i]; }

    PnPatch pnPatch0 = GetPnPatch(patch0);
    PnPatch pnPatch1 = GetPnPatch(patch1);
    PnPatch pnPatch2 = GetPnPatch(patch2);

    vec3 uvwSquared = uvw * uvw;
    vec3 uvwCubed = uvwSquared * uvw;

    vec3 b210 = vec3(pnPatch0.b210, pnPatch1.b210, pnPatch2.b210);
    vec3 b120 = vec3(pnPatch0.b120, pnPatch1.b120, pnPatch2.b120);
    vec3 b021 = vec3(pnPatch0.b021, pnPatch1.b021, pnPatch2.b021);
    vec3 b012 = vec3(pnPatch0.b012, pnPatch1.b012, pnPatch2.b012);
    vec3 b102 = vec3(pnPatch0.b102, pnPatch1.b102, pnPatch2.b102);
    vec3 b201 = vec3(pnPatch0.b201, pnPatch1.b201, pnPatch2.b201);
    vec3 b111 = vec3(pnPatch0.b111, pnPatch1.b111, pnPatch2.b111);

    vec3 n110 = normalize(vec3(pnPatch0.n110, pnPatch1.n110, pnPatch2.n110));
    vec3 n011 = normalize(vec3(pnPatch0.n011, pnPatch1.n011, pnPatch2.n011));
    vec3 n101 = normalize(vec3(pnPatch0.n101, pnPatch1.n101, pnPatch2.n101));

    //Normal
    vec3 barNormal = uvw.z * tesc_outNormal[0] + uvw.x * tesc_outNormal[1] + uvw.y * tesc_outNormal[2];
    vec3 pnNormal =
        tesc_outNormal[0] * uvwCubed.z +
        tesc_outNormal[1] * uvwCubed.x +
        tesc_outNormal[2] * uvwCubed.y +
        n110 * uvw.z * uvw.x +
        n011 * uvw.x * uvw.y +
        n101 * uvw.z * uvw.y;

    vec3 outNormal = tess.tessAlpha * pnNormal + (1.0 - tess.tessAlpha) * barNormal;

    //Position
    vec3 barPos = uvw.z * tesc_outPosition[0].xyz + uvw.x * tesc_outPosition[1].xyz + uvw.y * tesc_outPosition[2].xyz;
    uvwSquared *= 3.0;

    vec3 pnPos =
        tesc_outPosition[0].xyz * uvwCubed.z +
        tesc_outPosition[1].xyz * uvwCubed.x +
        tesc_outPosition[2].xyz * uvwCubed.y +
        b210 * uvwSquared.z * uvw.x +
        b120 * uvwSquared.x * uvw.z +
        b201 * uvwSquared.z * uvw.y +
        b021 * uvwSquared.x * uvw.y +
        b102 * uvwSquared.y * uvw.z +
        b012 * uvwSquared.y * uvw.x +
        b111 * 6.0 * uvw.x * uvw.y * uvw.z;

    vec3 finalPos = tess.tessAlpha * pnPos + (1.0 - tess.tessAlpha) * barPos;

    vec4 posWorld = obj.g_MatWorld * vec4(finalPos, 1.0);
    gl_Position = trans.mat4Proj * trans.mat4View * posWorld;

    outWorldPos = posWorld;
    outWorldPos.xyz /= outWorldPos.w;
    outWorldPos.w = float(instanceIndex);
    outColor = uvw.z * tesc_outColor[0] + uvw.x * tesc_outColor[1] + uvw.y * tesc_outColor[2];
    outWorldNormal = mat3(obj.g_MatWorld) * outNormal;
    outTexCoord = uvw.z * tesc_outTexCoord[0] + uvw.x * tesc_outTexCoord[1] + uvw.y * tesc_outTexCoord[2];
}