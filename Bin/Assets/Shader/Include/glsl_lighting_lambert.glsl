/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2026-03-17
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _GLSL_LIGHTING_LAMBERT_
#define _GLSL_LIGHTING_LAMBERT_

#include "/glsl_common.glsl"


vec3 calculate_Light_Ambient(vec3 ambientGlobal, 
                             vec3 ambientMaterial, 
                             vec3 ambientLight)
{
    return ambientGlobal * ambientMaterial * ambientLight;
}
vec3 calculate_Light_Diffuse_Lambert(vec3 diffuseMaterial, 
                                     vec3 diffuseLight,
                                     vec3 L,
                                     vec3 N)
{
    return diffuseMaterial * diffuseLight * max(dot(N, L), 0);
}
vec3 calculate_Specular_Phong(vec3 specularMaterial, 
                              vec3 specularLight,
                              float shininess,
                              vec3 posWorld,
                              vec3 posEye,
                              vec3 L,
                              vec3 N)
{
    vec3 V = normalize(posEye - posWorld);
    vec3 R = normalize(2 * max(dot(N, L), 0) * N - L);
    
    return specularMaterial * specularLight * pow(max(dot(V, R), 0), shininess);
}
vec3 calculate_Specular_BlinnPhong(vec3 specularMaterial, 
                                   vec3 specularLight,
                                   float shininess,
                                   vec3 posWorld,
                                   vec3 posEye,
                                   vec3 L,
                                   vec3 N)
{
    vec3 V = normalize(posEye - posWorld);
    vec3 H = normalize(L + V);

    return specularMaterial * specularLight * pow(max(dot(N, H), 0), shininess);
}

vec3 calculate_Light(vec3 ambientGlobal,
                     LightConstants lightCB,
                     MaterialConstants matCB,
                     vec3 posWorld,
                     vec3 posEye,
                     vec3 N)
{
    if (lightCB.lightCommon.z == 0 || matCB.lighting != 1)
        return vec3(1, 1, 1);
    
    vec3 L;
    if (lightCB.lightCommon.x == 0)
    {
        L = - lightCB.direction;
    }
    else
    {
        vec3 posLight = lightCB.position;
        L = normalize(posLight - posWorld);
    }

    //Ambient
    vec3 colorAmbient = vec3(0,0,0); 
    if (lightCB.lightCommon.z == 1 ||
        lightCB.lightCommon.z == 5 ||
        lightCB.lightCommon.z == 6 ||
        lightCB.lightCommon.z == 7 ||
        lightCB.lightCommon.z == 10 ||
        lightCB.lightCommon.z == 11)
    {
        colorAmbient = calculate_Light_Ambient(ambientGlobal,
                                               matCB.factorAmbient.rgb,
                                               lightCB.ambient.rgb);
    }
    
    //Diffuse
    vec3 colorDiffuse = vec3(0,0,0); 
    if (lightCB.lightCommon.z == 2 ||
        lightCB.lightCommon.z == 5 ||
        lightCB.lightCommon.z == 8 ||
        lightCB.lightCommon.z == 9 ||
        lightCB.lightCommon.z == 10 ||
        lightCB.lightCommon.z == 11)
    {
        colorDiffuse = calculate_Light_Diffuse_Lambert(matCB.factorDiffuse.rgb,
                                                       lightCB.diffuse.rgb,
                                                       L,
                                                       N);
    }
    
    //Specular
    vec3 colorSpecular = vec3(0,0,0);
    if (lightCB.lightCommon.z == 3 ||
        lightCB.lightCommon.z == 6 ||
        lightCB.lightCommon.z == 8 ||
        lightCB.lightCommon.z == 10)
    {
        //Phong
        colorSpecular = calculate_Specular_Phong(matCB.factorSpecular.rgb, 
                                                 lightCB.specular.rgb,
                                                 matCB.shininess,
                                                 posWorld,
                                                 posEye,
                                                 L,
                                                 N);
    }
    else if (lightCB.lightCommon.z == 4 ||
             lightCB.lightCommon.z == 7 ||
             lightCB.lightCommon.z == 9 ||
             lightCB.lightCommon.z == 11)
    {
        //BlinnPhong
        colorSpecular = calculate_Specular_BlinnPhong(matCB.factorSpecular.rgb,
                                                      lightCB.specular.rgb,
                                                      matCB.shininess,
                                                      posWorld,
                                                      posEye,
                                                      L,
                                                      N);
    }

    return colorAmbient + colorDiffuse + colorSpecular;
}


#endif /* _GLSL_LIGHTING_LAMBERT_*/