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

@REM mode only can be dx12, gl3, gles3_android, glfw_dx12, glfw_gl3, glfwVulkan
set m_dx12=dx12
set m_gl3=gl3
set m_gles_android=gles3_android
set m_glfw_dx12=glfw_dx12
set m_glfw_gl3=glfw_gl3
set m_glfw_vulkan=glfw_vulkan

set mode=%m_glfw_gl3%
if %mode% neq %m_dx12% (
    if %mode% neq %m_gl3% (
        if %mode% neq %m_gles_android% (
            if %mode% neq %m_glfw_dx12% (
                if %mode% neq %m_glfw_gl3% (
                    if %mode% neq %m_glfw_vulkan% (
                        echo "wrong mode type: [%mode%], only can be [%m_dx12%][%m_gl3%][%m_gles_android%][%glfw_dx12%][%m_glfw_gl3%][%m_glfw_vulkan%]"
                        exit
                    )
                )     
            )
        )
    )
)
echo "mode: %mode%, %debug%"


set name_base=imgui
set name=%name_base%-1.85

if "%debug%" == "debug" (
    set name_project=%name%"_"%mode%"_d"
    set name_lib=%name%"_"%mode%"_d.lib"
    set name_dll=%name%"_"%mode%"_d.dll"
) else (
    set name_project=%name%"_"%mode%
    set name_lib=%name%"_"%mode%".lib"
    set name_dll=%name%"_"%mode%".dll"
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
set lib_folder="..\Lib\Windows"
if not exist %lib_folder% (
    mkdir %lib_folder%
)
set lib_libfile=%lib_folder%"\"%name_lib%
if exist %lib_libfile% (
    del /S/Q %lib_libfile%
)

cd ..
cd Build
cd Windows
cd %name_project%

if "%debug%" == "debug" (
    cmake -DDEBUG=1 -DPLATFORM_MODE=%mode% ../../../Sources/%name%/
    msbuild "%name_project%".sln /p:configuration=debug
    copy /Y ".\Debug\"%name_lib% "..\..\..\Lib\Windows\"%name_lib%
    copy /Y ".\Debug\"%name_dll% "..\..\..\..\Bin\Windows\"%name_dll%
) else (
    cmake -DPLATFORM_MODE=%mode% ../../../Sources/%name%/
    msbuild "%name_project%".sln /p:configuration=release
    copy /Y ".\Release\"%name_lib% "..\..\..\Lib\Windows\"%name_lib%
    copy /Y ".\Release\"%name_dll% "..\..\..\..\Bin\Windows\"%name_dll%
)


cd ..
cd ..
cd ..
cd Compile

set build_folder="..\Include\Windows\"%name%"_"%mode%
if exist %build_folder% (
    rmdir /S/Q %build_folder%
)
mkdir %build_folder%

xcopy /S /E /Y /F "..\Sources\%name%\%name_base%\*.h" %build_folder%"\"%name_base%"\"
if %mode% == %m_dx12% (
    xcopy /S /E /Y /F "..\Sources\%name%\impl_dx12\*.h" %build_folder%"\impl_dx12\"
    xcopy /S /E /Y /F "..\Sources\%name%\impl_win32\*.h" %build_folder%"\impl_win32\"
) else if %mode% == %m_gl3% (
    xcopy /S /E /Y /F "..\Sources\%name%\impl_gl3\*.h" %build_folder%"\impl_gl3\"
) else if %mode% == %m_gles_android% (
    xcopy /S /E /Y /F "..\Sources\%name%\impl_gles3_android\*.h" %build_folder%"\impl_gles3_android\"
) else if %mode% == %m_glfw_dx12% (
    xcopy /S /E /Y /F "..\Sources\%name%\impl_glfw\*.h" %build_folder%"\impl_glfw\"
    xcopy /S /E /Y /F "..\Sources\%name%\impl_dx12\*.h" %build_folder%"\impl_dx12\"
    xcopy /S /E /Y /F "..\Sources\%name%\impl_win32\*.h" %build_folder%"\impl_win32\"
) else if %mode% == %m_glfw_gl3% (
    xcopy /S /E /Y /F "..\Sources\%name%\impl_glfw\*.h" %build_folder%"\impl_glfw\"
    xcopy /S /E /Y /F "..\Sources\%name%\impl_gl3\*.h" %build_folder%"\impl_gl3\"
) else if %mode% == %m_glfw_vulkan% (
    xcopy /S /E /Y /F "..\Sources\%name%\impl_glfw\*.h" %build_folder%"\impl_glfw\"
    xcopy /S /E /Y /F "..\Sources\%name%\impl_vulkan\*.h" %build_folder%"\impl_vulkan\"
)

@echo over