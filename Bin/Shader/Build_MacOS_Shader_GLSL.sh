#****************************************************************************
# LostPeterOpenGL - Copyright (C) 2022 by LostPeter
# 
# Author:   LostPeter
# Time:     2024-11-03
# Github:   https://github.com/LostPeter/LostPeterOpenGL
# Document: https://www.zhihu.com/people/lostpeter/posts
#
# This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
#****************************************************************************/

name_shader=${1}
folder_shader=${2}

folderSrc="./glsl/sample"
folderDst="../Assets/Shader"

cp -rf $folderSrc/$folder_shader/$name_shader $folderDst/$folder_shader/$name_shader.spv
