@REM #****************************************************************************
@REM # LostPeterOpenGL - Copyright (C) 2022 by LostPeter
@REM # 
@REM # Author:   LostPeter
@REM # Time:     2025-01-26
@REM # Github:   https://github.com/LostPeter/LostPeterOpenGL
@REM # Document: https://www.zhihu.com/people/lostpeter/posts
@REM #
@REM # This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
@REM #****************************************************************************/

set debug=%1
set rebuild=%2
set depends=%3


@REM 1> Dependencies
if "%depends%" == "depends" (
    cd Dependencies
    cd Compile

    call ./Build_Windows_lib_all.bat %debug% %rebuild%

    cd ..
    cd ..
)


@REM 2> Shaders
cd Bin
cd Shader

call ./Build_Windows_Shader_GLSL_All.bat %debug% 

cd ..
cd ..


@REM 3> LostPeterOpenGL
cd LostPeterOpenGL
cd Compile

call ./Build_Windows_LostPeterOpenGL.bat %debug% %rebuild%

cd ..
cd ..


@REM 4> Sample
cd Sample
cd Compile

call ./Build_Windows_Sample_All.bat %debug% %rebuild%

cd ..
cd ..