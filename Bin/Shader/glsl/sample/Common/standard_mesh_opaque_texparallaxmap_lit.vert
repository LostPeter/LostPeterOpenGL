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
layout (location = 3) in vec3 inTangent;
layout (location = 4) in vec2 inTexCoord;

out vec4 fragWorldPos;
out vec4 fragColor;
out vec3 fragWorldNormal;
out vec3 fragWorldTangent
out vec2 fragTexCoord;
out vec3 fragTSPos;
out vec3 fragTSEyePos;

void main()
{
	int viewIndex = 0;
	TransformConstants trans = passConsts.g_Transforms[viewIndex];
	CameraConstants cam = passConsts.g_Cameras[viewIndex];
	ObjectConstant obj = objectConsts.objs[gl_InstanceID];

    fragWorldPos = obj.g_MatWorld * vec4(inPosition, 1.0);
    gl_Position = trans.mat4Proj * trans.mat4View * fragWorldPos;
    fragWorldPos.xyz /= fragWorldPos.w;
    fragWorldPos.w = gl_InstanceID;
    fragColor = inColor;
    mat3 matW = transpose(inverse(mat3(obj.g_MatWorld)));
	fragWorldNormal = normalize(matW * inNormal);
	fragWorldTangent = normalize(matW, inTangent);
    fragTexCoord = inTexCoord;

	float3 N = normalize(inNormal);
	float3 T = normalize(inTangent);
	float3 B = normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);
    fragTSPos = TBN * fragWorldPos.xyz;
    fragTSEyePos = TBN * cam.posEyeWorld.xyz;
}