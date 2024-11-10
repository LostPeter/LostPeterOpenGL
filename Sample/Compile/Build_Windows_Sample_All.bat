@REM #****************************************************************************
@REM # LostPeterOpenGL - Copyright (C) 2022 by LostPeter
@REM # 
@REM # Author:   LostPeter
@REM # Time:     2024-10-17
@REM # Github:   https://github.com/LostPeter/LostPeterOpenGL
@REM # Document: https://www.zhihu.com/people/lostpeter/posts
@REM #
@REM # This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
@REM #****************************************************************************/

set debug=%1
set rebuild=%2

call ./Build_Windows_Sample.bat opengl_000_window %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_001_triangle %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_002_imgui %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_003_texture %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_004_model %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_005_camera %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_006_depth %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_007_stencil %debug% %rebuild%
call ./Build_Windows_Sample.bat opengl_008_blend %debug% %rebuild%