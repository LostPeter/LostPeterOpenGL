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

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inTexCoord;

out vec4 fragWorldPos;
out vec4 fragColor;
out vec3 fragWorldNormal;
out vec2 fragTexCoord;

void main()
{
	int viewIndex = 0;
	TransformConstants trans = passConsts.g_Transforms[viewIndex];
	ObjectConstant obj = objectConsts.objs[gl_InstanceID];
	MaterialConstant mat = materialConsts.mats[gl_InstanceID];

    fragWorldPos = obj.g_MatWorld * vec4(inPosition, 1.0);
    gl_Position = trans.mat4Proj * trans.mat4View * fragWorldPos;
    fragWorldPos.xyz /= fragWorldPos.w;
    fragWorldPos.w = gl_InstanceID;
    fragColor = inColor;
    mat3 normalMatrix = transpose(inverse(mat3(obj.g_MatWorld)));
	fragWorldNormal = normalize(normalMatrix * inNormal);
    fragTexCoord = inTexCoord;
}