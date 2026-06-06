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


in HSOutput {
    vec4 outPosition;  // xyz: Object Pos; w: instanceIndex
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} IN[];


out vec4 fragWorldPos;
out vec4 fragColor;
out vec3 fragWorldNormal;
out vec2 fragTexCoord;


void main() {
    vec3 uvw = gl_TessCoord.xyz;

    int viewIndex = 0;
    TransformConstants trans = passConsts.g_Transforms[viewIndex];

    int instanceIndex = int(round(IN[0].outPosition.w));

    vec3 posObject  = uvw.x * IN[0].outPosition.xyz
                    + uvw.y * IN[1].outPosition.xyz
                    + uvw.z * IN[2].outPosition.xyz;

    vec3 normalObject = uvw.x * IN[0].outNormal
                      + uvw.y * IN[1].outNormal
                      + uvw.z * IN[2].outNormal;

    vec2 texCoord   = uvw.x * IN[0].outTexCoord
                    + uvw.y * IN[1].outTexCoord
                    + uvw.z * IN[2].outTexCoord;

    vec4 color      = uvw.x * IN[0].outColor
                    + uvw.y * IN[1].outColor
                    + uvw.z * IN[2].outColor;

    ObjectConstant obj = objectConsts.objs[instanceIndex];
    vec4 posWorld = obj.g_MatWorld * vec4(posObject, 1.0);

    vec4 posView   = trans.mat4View * posWorld;
    vec4 posClip   = trans.mat4Proj * posView;
	
    gl_Position        = posClip;
    fragWorldPos.xyz   = posWorld.xyz / posWorld.w;
    fragWorldPos.w     = float(instanceIndex);
    fragColor          = color;
    fragWorldNormal    = mat3(obj.g_MatWorld) * normalObject;
    fragTexCoord       = texCoord;
}