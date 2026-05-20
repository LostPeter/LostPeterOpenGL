/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-16
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _GLSL_FUNCTION_
#define _GLSL_FUNCTION_


///////////////////////////////// Common  //////////////////////////////////////////////
float saturate(float x) { return clamp(x, 0.0, 1.0); }
vec2 saturate(vec2 x) { return clamp(x, 0.0, 1.0); }
vec3 saturate(vec3 x) { return clamp(x, 0.0, 1.0); }
vec4 saturate(vec4 x) { return clamp(x, 0.0, 1.0); }


///////////////////////////////// NormalMap //////////////////////////////////////////////
vec3 Func_UnpackNormalRGB(vec4 packedNormal, float scale)
{
    vec3 normal;
    normal.xyz = packedNormal.xyz * 2.0 - 1.0;
    normal.xy *= scale;
    return normalize(normal);
}

vec3 Func_UnpackNormalRGB(vec4 packedNormal)
{
    return Func_UnpackNormalRGB(packedNormal, 1.0);
}

vec3 Func_UnpackNormalXYZ(sampler2D texNormalMap,
                          vec2 uv)
{
    vec3 packedNormal = texture(texNormalMap, uv).xyz;
    return normalize(packedNormal * 2.0 - 1.0);
}
vec3 Func_UnpackNormalXY(sampler2D texNormalMap,
                         vec2 uv)
{
    vec2 packedNormal = texture(texNormalMap, uv).xy;
    vec3 normal;
    normal.xy = packedNormal.xy * 2.0 - 1.0;
    normal.z = sqrt(1.0 - saturate(dot(normal.xy, normal.xy)));
    return normalize(normal);
}

vec3 Func_CalculateNormal(sampler2D texNormalMap,
                          vec2 inTexCoord,
                          vec3 inWorldNormal,
                          vec3 inWorldTangent)
{
    vec3 normal = Func_UnpackNormalXYZ(texNormalMap,
                                       inTexCoord);

    vec3 N = normalize(inWorldNormal);
    vec3 T = normalize(inWorldTangent);
    vec3 B = normalize(cross(N, T));
    mat3 TBN = transpose(mat3(T, B, N));

    return normalize(TBN * normal);
}


///////////////////////////////// ParallaxMap ////////////////////////////////////////////
vec2 Func_ParallaxMapping_Common(sampler2D texParallaxMap,
								 vec2 uv,
								 vec3 viewDirTS,
								 float heightScale,
								 float parallaxBias)
{
	float height = 1.0 - texture(texParallaxMap, uv).w;
	vec2 p = viewDirTS.xy * (height * (heightScale * 0.5) + parallaxBias) / viewDirTS.z;
	return uv - p;
}

vec2 Func_ParallaxMapping_Steep(sampler2D texParallaxMap,
								vec2 uv, 
								vec3 viewDirTS,
								float heightScale,
								float numLayers)
{
	float layerDepth = 1.0 / numLayers;
	float currLayerDepth = 0.0;
	vec2 deltaUV = viewDirTS.xy * heightScale / (viewDirTS.z * numLayers);
	vec2 currUV = uv;
	float height = 1.0 - texture(texParallaxMap, currUV).w;
	for (int i = 0; i < numLayers; i++) 
    {
		currLayerDepth += layerDepth;
		currUV -= deltaUV;
		height = 1.0 - texture(texParallaxMap, currUV).w;
		if (height < currLayerDepth) 
        {
			break;
		}
	}
	return currUV;
}

vec2 Func_ParallaxMapping_Occlusion(sampler2D texParallaxMap,
									vec2 uv, 
									vec3 viewDirTS,
									float heightScale,
									float numLayers)
{
	float layerDepth = 1.0 / numLayers;
	float currLayerDepth = 0.0;
	vec2 deltaUV = viewDirTS.xy * heightScale / (viewDirTS.z * numLayers);
	vec2 currUV = uv;
	float height = 1.0 - texture(texParallaxMap, currUV).w;
	for (int i = 0; i < numLayers; i++) 
    {
		currLayerDepth += layerDepth;
		currUV -= deltaUV;
		height = 1.0 - texture(texParallaxMap, currUV).w;
		if (height < currLayerDepth) 
        {
			break;
		}
	}
	vec2 prevUV = currUV + deltaUV;
	float nextDepth = height - currLayerDepth;
	float prevDepth = 1.0 - texture(texParallaxMap, prevUV).w - currLayerDepth + layerDepth;
	return mix(currUV, prevUV, nextDepth / (nextDepth - prevDepth));
}



///////////////////////////////// Linear - SRGB //////////////////////////////////////////
vec4 Func_ProcessLinear(vec4 pixel)
{
	return vec4(pow(max(pixel.xyz, 1e-6), vec3(1.0 / 2.2)), pixel.w);
}

vec4 Func_LinearToSRGB(vec4 pixel)
{
	vec3 linear = max(pixel.xyz, 0.0);

	vec3 sRGBLo = linear * 12.92;
	vec3 sRGBHi = (pow(abs(linear), vec3(1.0 / 2.4)) * 1.055) - 0.055;
	vec3 sRGB = mix(sRGBHi, sRGBLo, step(linear, vec3(0.0031308)));
	return vec4(saturate(sRGB), pixel.w);
}


#endif
