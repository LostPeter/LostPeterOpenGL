@REM #****************************************************************************
@REM # LostPeterOpenGL - Copyright (C) 2022 by LostPeter
@REM # 
@REM # Author:   LostPeter
@REM # Time:     2024-11-03
@REM # Github:   https://github.com/LostPeter/LostPeterOpenGL
@REM # Document: https://www.zhihu.com/people/lostpeter/posts
@REM #
@REM # This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
@REM #****************************************************************************/

@echo off

set debug=%1

set name_folder=glsl
set folderSrc=.\%name_folder%
set folderShader=..\Assets\Shader
set folderInclude=.\%name_folder%

if exist %folderShader% (
    rmdir /S/Q %folderShader%
)
mkdir %folderShader%

echo "************** Shader Source .vert/.tesc/.tese/.geom/.frag/.comp **************"
call :buildShader %folderSrc% %debug%
echo "************** Shader Source .vert/.tesc/.tese/.geom/.frag/.comp **************"

echo "************** Shader Compile .spv ********************************************"
for %%i in (%folderShader%\*.*) do echo %%i
echo "************** Shader Compile .spv ********************************************"

exit /b %errorlevel%
:buildShader
    echo folder is: %~1

	for /F %%i in ('Dir %~1\*.* /B') do (
		echo %%i

		if exist %~1\%%i\nul (
            call :buildShader %~1\%%i %~2
        ) else (
            call ./Build_Windows_Shader_GLSL.bat %%i %~1 %folderInclude% %~2
        )
	) 

exit /b 0 
