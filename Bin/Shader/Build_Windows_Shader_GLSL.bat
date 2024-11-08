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

set name_shader=%1
set folder_shader=%2

set folderSrc=.\glsl\sample
set folderDst=..\Assets\Shader

copy %folderSrc%\%folder_shader%\%name_shader% %folderDst%\%folder_shader%\%name_shader%.spv