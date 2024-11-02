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
folder_include=${3}
debug=${4}

name_vert="\.vert"
name_tesc="\.tesc"
name_tese="\.tese"
name_geom="\.geom"
name_frag="\.frag"
name_comp="\.comp"

name_profile=""
if [[ $name_shader =~ $name_vert ]]; then
    name_profile="vs_6_1"
	# echo "file is .vert !"
elif [[ $name_shader =~ $name_tesc ]]; then
    name_profile="hs_6_1"
	# echo "file is .tesc !"
elif [[ $name_shader =~ $name_tese ]]; then
    name_profile="ds_6_1"
	# echo "file is .tese !"
elif [[ $name_shader =~ $name_geom ]]; then
    name_profile="gs_6_1"
	# echo "file is .geom !"
elif [[ $name_shader =~ $name_frag ]]; then
    name_profile="ps_6_1"
	# echo "file is .frag !"
elif [[ $name_shader =~ $name_comp ]]; then
    name_profile="cs_6_1"
	# echo "file is .comp !"
else
	echo "Ignore file, is not [.vert/.tesc/.tese/.geom/.frag.comp], name: $name_shader"
	exit
fi


folderSrc=$folder_shader
folderShader="../Assets/Shader"
mkdir -p $folderShader

