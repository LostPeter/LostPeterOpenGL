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
rm -rf $dirDst"/Include"
rm -rf $dirDst"/Common"
rm -rf $dirDst"/MacOS"

mkdir -p $dirDst"/Include"
mkdir -p $dirDst"/Common"
mkdir -p $dirDst"/MacOS"

function compile_shader() {
    for file in `ls $1`
    do 
        echo $1/$file
        ./Build_MacOS_Shader_GLSL.sh $file $2
    done
}

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


echo "************** Shader Source .vert/.tesc/.tese/.geom/.frag/.comp **************"
{
    for file in ${dirSrc}/Include/*.glsl
    do 
        cp -rfp $file $dirDst/Include
    done

    compile_shader $dirSrc/Common Common
    compile_shader $dirSrc/MacOS MacOS
}
echo "************** Shader Source .vert/.tesc/.tese/.geom/.frag/.comp **************"


echo "************** Shader Copy ****************************************************"
{
    read_dir $dirDst/Include
    read_dir $dirDst/Common
    read_dir $dirDst/MacOS
}
echo "************** Shader Copy ****************************************************"