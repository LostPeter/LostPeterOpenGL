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

in vec4 fragColor;
in vec2 fragTexCoord;

uniform sampler2D texSampler;

out vec4 outColor;

void main()
{
    vec3 color = texture(texSampler, fragTexCoord).xyz * fragColor.xyz;
    outColor = vec4(color.xyz, 1.0);
}