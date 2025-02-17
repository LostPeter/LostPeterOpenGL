#****************************************************************************
# LostPeterOpenGL - Copyright (C) 2022 by LostPeter
# 
# Author:   LostPeter
# Time:     2024-10-17
# Github:   https://github.com/LostPeter/LostPeterOpenGL
# Document: https://www.zhihu.com/people/lostpeter/posts
#
# This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
#****************************************************************************/

debug=${1}
rebuild=${2}

./Build_MacOS_Sample.sh opengl_000_window $debug $rebuild
./Build_MacOS_Sample.sh opengl_001_triangle $debug $rebuild
./Build_MacOS_Sample.sh opengl_002_imgui $debug $rebuild
./Build_MacOS_Sample.sh opengl_003_texture $debug $rebuild
./Build_MacOS_Sample.sh opengl_004_model $debug $rebuild
./Build_MacOS_Sample.sh opengl_005_camera $debug $rebuild
./Build_MacOS_Sample.sh opengl_006_depth $debug $rebuild
./Build_MacOS_Sample.sh opengl_007_stencil $debug $rebuild
./Build_MacOS_Sample.sh opengl_008_blend $debug $rebuild
