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

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 inColor;

out vec4 fragColor;

void main()
{
    gl_Position = vec4(inPosition.xy, 0.0, 1.0);
    fragColor = inColor;
}