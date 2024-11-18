/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-14
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#version 330 core
#extension GL_ARB_shading_language_include : enable
#include "/glsl_common.glsl"

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoord;

out vec4 fragColor;
out vec2 fragTexCoord;

void main()
{
    float x = inPosition.x * objectCopyBlit.scaleX + objectCopyBlit.offsetX;
    float y = inPosition.y * objectCopyBlit.scaleY + objectCopyBlit.offsetY;
    gl_Position = vec4(x, y, 0.0, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}