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

layout(triangles, equal_spacing, ccw) in;


layout(binding = 4) uniform sampler2D texDisplacementMap;


in HSOutput {
    vec4 outPosition;  // xyz: Object Pos; w: instanceIndex
    vec4 outColor;
    vec3 outNormal;
    vec2 outTexCoord;
} IN[];


layout(location = 0) out vec4 outWorldPos;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec3 outWorldNormal;
layout(location = 3) out vec2 outTexCoord;


void main() {
    vec3 uvw = gl_TessCoord.xyz;

    uint viewIndex = 0;
    TransformConstants trans = passConsts.g_Transforms[viewIndex];

    uint instanceIndex = uint(IN[0].outPosition.w);

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

    TessellationConstants tess = tessellationConsts[instanceIndex];
    float displacement = texture(texDisplacementMap, texCoord).a;
    displacement = max(displacement, 0.0);
    posObject += normalize(normalObject) * displacement * tess.tessStrength;

    ObjectConstants obj = objectConsts[instanceIndex];
    vec4 posWorld = obj.g_MatWorld * vec4(posObject, 1.0);

    vec4 posView   = trans.mat4View * posWorld;
    vec4 posClip   = trans.mat4Proj * posView;
	
    gl_Position        = posClip;
    outWorldPos.xyz    = posWorld.xyz / posWorld.w;
    outWorldPos.w      = float(instanceIndex);
    outColor           = color;
    outWorldNormal     = mat3(obj.g_MatWorld) * normalObject;
    outTexCoord        = texCoord;
}