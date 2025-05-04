/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2025-04-12
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

vec4 Grid(vec2 texCoord, float divisions, vec4 color)
{
    float lineWidth = 2.0;

    vec2 vCoord = texCoord.xy * divisions;

    vec2 vGrid = abs(fract(vCoord - 0.5) - 0.5) / fwidth(vCoord);
    float fLine = min(vGrid.x, vGrid.y);
    float fLineResult = lineWidth - min(fLine, lineWidth);

    return vec4(color.xyz * fLineResult, 0.05 * fLineResult);
}

void main()
{
	float fDivs;
    float divisions = 1000.0;
    float step = 100.0;
    float subdivisions = 4.0;

	int viewIndex = 0;
    CameraConstants cam = passConsts.g_Cameras[viewIndex];
    vec3 viewPos = cam.posEyeWorld.xyz;
    vec4 color = gridObjectConsts.color;

	fDivs = divisions / pow(2.0, round((abs(viewPos.y) - step / subdivisions) / step));
	vec4 vGrid1 = Grid(fragTexCoord, fDivs, color) + Grid(fragTexCoord, fDivs / subdivisions, color);

	fDivs = divisions / pow(2.0, round((abs(viewPos.y + 50) - step / subdivisions) / step));
	vec4 vGrid2 = Grid(fragTexCoord, fDivs, color) + Grid(fragTexCoord, fDivs / subdivisions, color);

	float fAlpha = mod(abs(viewPos.y), step);
	fAlpha = 0.0;

    outColor = mix(vGrid1, vGrid2, fAlpha);

    vec3 vPseudoViewPos = vec3(viewPos.x, fragWorldPos.y, viewPos.z);
    float fDistanceToCamera = max(distance(fragWorldPos.xyz, vPseudoViewPos) - abs(viewPos.y), 0.0);
    
    float fAlphaDecreaseDistance = 128.0f;
    float fDecreaseDistance = 1024.0f;
    if (fDistanceToCamera > fAlphaDecreaseDistance)
    {
        float normalizedDistanceToCamera = clamp(fDistanceToCamera - fAlphaDecreaseDistance, 0.0f, fDecreaseDistance) / fDecreaseDistance;
        outColor.a *= clamp(1.0f - normalizedDistanceToCamera, 0.0f, 1.0f);
    }
    outColor.a *= color.a;
}