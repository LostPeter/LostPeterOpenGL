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

set name_folder=glsl
set folderSrc=.\%name_folder%\sample
set folderDst=..\Assets\Shader

if not exist %folderDst% (
    mkdir %folderDst%
)

if exist %folderDst%\Include (
    rmdir /S/Q %folderDst%\Include
)
mkdir %folderDst%\Include

if exist %folderDst%\Common (
    rmdir /S/Q %folderDst%\Common
)
mkdir %folderDst%\Common

if exist %folderDst%\Windows (
    rmdir /S/Q %folderDst%\Windows
)
mkdir %folderDst%\Windows




echo "************** Shader Source .vert/.tesc/.tese/.geom/.frag/.comp **************"
xcopy /S /E /Y /F %folderSrc%\Include %folderDst%"\Include\"
call :buildShader %folderSrc%\Common Common
call :buildShader %folderSrc%\Windows Windows
echo "************** Shader Source .vert/.tesc/.tese/.geom/.frag/.comp **************"

echo "************** Shader Copy ****************************************************"
for %%i in (%folderDst%\Include\*.*) do echo %%i
for %%i in (%folderDst%\Common\*.*) do echo %%i
for %%i in (%folderDst%\Windows\*.*) do echo %%i
echo "************** Shader Copy ****************************************************"

exit /b %errorlevel%
:buildShader
    echo folder is: %~1

	for /F %%i in ('Dir %~1\*.* /B') do (
		echo %~1\%%i

        call ./Build_Windows_Shader_GLSL.bat %%i %~2
	) 

exit /b 0 
