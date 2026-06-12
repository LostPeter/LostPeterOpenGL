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

patch in vec3 tesc_pnPatchPos[7];
patch in vec3 tesc_pnPatchNormal[3];

out vec4 fragWorldPos;
out vec4 fragColor;
out vec3 fragWorldNormal;
out vec2 fragTexCoord;

void main()
{
    vec3 uvw = gl_TessCoord.xyz;

    uint viewIndex = 0;

    TransformConstants trans =
        passConsts.g_Transforms[viewIndex];

    uint instanceIndex =
        uint(tesc_outPosition[0].w + 0.5);

    ObjectConstant obj =
        objectConsts.objs[instanceIndex];

    TessellationConstant tess =
        tessellationConsts.tes[instanceIndex];

    vec3 uvw2 = uvw * uvw;
    vec3 uvw3 = uvw2 * uvw;

    vec3 b210 = tesc_pnPatchPos[0];
    vec3 b120 = tesc_pnPatchPos[1];
    vec3 b021 = tesc_pnPatchPos[2];
    vec3 b012 = tesc_pnPatchPos[3];
    vec3 b102 = tesc_pnPatchPos[4];
    vec3 b201 = tesc_pnPatchPos[5];
    vec3 b111 = tesc_pnPatchPos[6];

    vec3 n110 = normalize(tesc_pnPatchNormal[0]);
    vec3 n011 = normalize(tesc_pnPatchNormal[1]);
    vec3 n101 = normalize(tesc_pnPatchNormal[2]);

    vec3 barNormal =
        uvw.z * tesc_outNormal[0] +
        uvw.x * tesc_outNormal[1] +
        uvw.y * tesc_outNormal[2];

    vec3 pnNormal =
        tesc_outNormal[0] * uvw3.z +
        tesc_outNormal[1] * uvw3.x +
        tesc_outNormal[2] * uvw3.y +
        n110 * uvw.z * uvw.x +
        n011 * uvw.x * uvw.y +
        n101 * uvw.z * uvw.y;

    vec3 finalNormal =
        mix(barNormal, pnNormal, tess.tessAlpha);

    vec3 barPos =
        uvw.z * tesc_outPosition[0].xyz +
        uvw.x * tesc_outPosition[1].xyz +
        uvw.y * tesc_outPosition[2].xyz;

    uvw2 *= 3.0;

    vec3 pnPos =
        tesc_outPosition[0].xyz * uvw3.z +
        tesc_outPosition[1].xyz * uvw3.x +
        tesc_outPosition[2].xyz * uvw3.y +

        b210 * uvw2.z * uvw.x +
        b120 * uvw2.x * uvw.z +

        b201 * uvw2.z * uvw.y +
        b021 * uvw2.x * uvw.y +

        b102 * uvw2.y * uvw.z +
        b012 * uvw2.y * uvw.x +

        b111 * 6.0 *
        uvw.x * uvw.y * uvw.z;

    vec3 finalPos =
        mix(barPos, pnPos, tess.tessAlpha);

    vec4 worldPos =
        obj.g_MatWorld *
        vec4(finalPos, 1.0);

    gl_Position =
        trans.mat4Proj *
        trans.mat4View *
        worldPos;

    fragWorldPos = worldPos;

    fragWorldPos.xyz /=
        fragWorldPos.w;

    fragWorldPos.w =
        float(instanceIndex);

    fragColor =
        uvw.z * tesc_outColor[0] +
        uvw.x * tesc_outColor[1] +
        uvw.y * tesc_outColor[2];

    fragWorldNormal =
        normalize(
            mat3(obj.g_MatWorld) *
            finalNormal);

    fragTexCoord =
        uvw.z * tesc_outTexCoord[0] +
        uvw.x * tesc_outTexCoord[1] +
        uvw.y * tesc_outTexCoord[2];
}