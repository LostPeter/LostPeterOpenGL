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

name_folder="glsl"
dirSrc="./$name_folder/sample"
dirDst="../Assets/Shader"

mkdir -p $dirDst
rm -rf $dirDst"/Common"
rm -rf $dirDst"/MacOS"

cp -pr $dirSrc"/Common" $dirDst
cp -pr $dirSrc"/MacOS" $dirDst

function read_dir() {
    for file in `ls $1`
    do 
        if [ -d $1"/"$file ]; then
            read_dir $1"/"$file 
        else
            echo $1"/"$file 
        fi
    done
}


echo "************** Shader Copy ********************************************"
{
    read_dir $dirDst
}
echo "************** Shader Copy ********************************************"