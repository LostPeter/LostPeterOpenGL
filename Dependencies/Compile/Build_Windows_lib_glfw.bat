@REM #****************************************************************************
@REM # LostPeterOpenGL - Copyright (C) 2022 by LostPeter
@REM # 
@REM # Author:   LostPeter
@REM # Time:     2022-10-30
@REM # Github:   https://github.com/LostPeter/LostPeterOpenGL
@REM # Document: https://www.zhihu.com/people/lostpeter/posts
@REM #
@REM # This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
@REM #****************************************************************************/

@echo off
set debug=%1
set rebuild=%2

echo %debug%
echo %rebuild%

set name="glfw-3.3.6"
if "%debug%" == "debug" (
    set name_project=%name%"_d"
    set name_lib=%name%"_d.lib"
    set name_dll="glfw3.dll"
) else (
    set name_project=%name%
    set name_lib=%name%".lib"
    set name_dll="glfw3.dll"
)

@rem build folder
set build_folder="..\Build\Windows\"%name_project%
if exist %build_folder% (
    if "%rebuild%" == "rebuild" (
        rmdir /S/Q %build_folder%
    )
)
mkdir %build_folder%


@rem Lib folder/file
set plugins_folder="..\Lib\Windows"
if not exist %plugins_folder% (
    mkdir %plugins_folder%
)
set plugins_libfile=%plugins_folder%"\"%name_lib%
if exist %plugins_libfile% (
    del /S/Q %plugins_libfile%
)


cd ..
cd Build
cd Windows
cd %name_project%

if "%debug%" == "debug" (
    cmake -DDEBUG=1 "../../../Sources/%name%/"
    msbuild GLFW.sln /p:configuration=debug
    copy /Y ".\src\Debug\glfw3dll.lib" "..\..\..\Lib\Windows\"%name_lib%
    copy /Y ".\src\Debug\glfw3.dll" "..\..\..\..\Bin\Windows\"%name_dll%
) else (
    cmake "../../../Sources/%name%/"
    msbuild GLFW.sln /p:configuration=release
    copy /Y ".\src\Release\glfw3dll.lib" "..\..\..\Lib\Windows\"%name_lib%
    copy /Y ".\src\Release\glfw3.dll" "..\..\..\..\Bin\Windows\"%name_dll%
)


cd ..
cd ..
cd ..
cd Compile

set include_folder="..\Include\Windows\"%name%"\GLFW"
if exist %include_folder% (
    rmdir /S/Q %include_folder%
)
mkdir %include_folder%

xcopy /S /E /Y /F "..\Sources\%name%\include\GLFW\*.h" %include_folder%"\"