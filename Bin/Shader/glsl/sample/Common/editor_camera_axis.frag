/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2025-04-26
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#version 330 core
#extension GL_ARB_shading_language_include : enable
#include "/glsl_common.glsl"

in vec4 fragWorldPos;
in vec4 fragColor;
in vec2 fragTexCoord;

out vec4 outColor;

void main()
{
	int index = int(floor(fragWorldPos.w + 0.5));
	CameraAxisObjectConstant obj = cameraAxisObjectConsts.objs[index];
	
	outColor = obj.color;
}