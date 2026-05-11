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

out vec4 fragPosition;
out vec4 fragColor;
out vec3 fragWorldNormal;
out vec3 fragTexCoord;

void main()
{
	int viewIndex = 0;
	TransformConstants trans = passConsts.g_Transforms[viewIndex];
	ObjectConstant obj = objectConsts.objs[gl_InstanceID];
	MaterialConstant mat = materialConsts.mats[gl_InstanceID];
		
    fragPosition = vec4(inPosition, gl_InstanceID);
    fragColor = inColor;
	fragWorldNormal = inNormal;
    fragTexCoord = inPosition;
	gl_Position = fragPosition;
}