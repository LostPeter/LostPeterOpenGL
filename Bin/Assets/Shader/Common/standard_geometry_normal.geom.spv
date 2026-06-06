/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2026-06-06
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#version 410 core
#extension GL_ARB_gpu_shader5 : enable
#extension GL_ARB_geometry_shader4 : require
#extension GL_ARB_shading_language_include : enable
#include "/glsl_common.glsl"

layout(triangles) in; 
layout(line_strip, max_vertices = 6) out; 

in vec4 vs_outPosition[];
in vec3 vs_outNormal[];

out vec3 outColor;

void main()
{
    uint viewIndex = 0;
    TransformConstants trans = passConsts.g_Transforms[viewIndex];
    uint instanceIndex = uint(vs_outPosition[0].w + 0.5);
    
    ObjectConstant obj = objectConsts.objs[instanceIndex];
    GeometryConstant geom = geometryConsts.geo[instanceIndex];
    float normalLength = geom.length;

    for (int i = 0; i < 3; i++)
    {
        vec3 pos    = vs_outPosition[i].xyz;
        vec3 normal = vs_outNormal[i].xyz;

        mat4 worldMat = obj.g_MatWorld;
        mat4 viewProj = trans.mat4Proj * trans.mat4View;

        //0
        vec4 worldPos0 = worldMat * vec4(pos, 1.0);
        gl_Position    = viewProj * worldPos0;
        outColor       = vec3(1.0, 0.0, 0.0);
        EmitVertex();

        //1
        vec4 worldPos1 = worldMat * vec4(pos + normal * normalLength, 1.0);
        gl_Position    = viewProj * worldPos1;
        outColor       = vec3(0.0, 0.0, 1.0);
        EmitVertex();

        //2
        EndPrimitive();
    }
}