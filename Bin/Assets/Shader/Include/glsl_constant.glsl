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

#ifndef _GLSL_CONSTANT_
#define _GLSL_CONSTANT_


///////////////////////////////// Constants /////////////////////////////////////
//Common
#define PI 3.141592
#define PI_HALF 1.570796



//Max XX Count
#define MAX_LIGHT_COUNT                 16
#define MAX_OBJECT_COUNT                1024
#define MAX_OBJECT_LINEFLAT_2D_COUNT    2048
#define MAX_OBJECT_LINEFLAT_3D_COUNT    512
#define MAX_TEXTURE_COUNT               16
#define MAX_MATERIAL_COUNT              64
#define MAX_INSTANCE_COUNT              4096
#define MAX_CULL_INSTANCE_COUNT         16384
#define MAX_TERRAIN_SPLAT_COUNT         16
#define MAX_FRUSTUM_PLANE_COUNT		    6


//Const
const float c_fOscillateDelta = 0.05;

const mat4 c_mat4Bias = mat4(0.5, 0.0, 0.0, 0.5,
                             0.0, 0.5, 0.0, 0.5,
                             0.0, 0.0, 0.5, 0.5,
                             0.0, 0.0, 0.0, 1.0);

const vec3 c_aAggressiveExtentArray[8] = vec3[8](vec3( 1,       1,      1),
                                                 vec3( 1,       1,     -1),
                                                 vec3( 1,      -1,      1),
                                                 vec3( 1,      -1,     -1),
                                                 vec3(-1,       1,      1),
                                                 vec3(-1,       1,     -1),
                                                 vec3(-1,      -1,      1),
                                                 vec3(-1,      -1,     -1));



#endif /* _GLSL_CONSTANT_*/