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

version=${1}
debug=${2}
rebuild=${3}

name=glad-$version
if [ "$debug" == "debug" ]; then
    name_project=$name"_d"
    name_lib="lib"$name"_d.a"
else
    name_project=$name
    name_lib="lib"$name".a"
fi

if [ "$rebuild" == "rebuild" ]; then
    rm -rf "../Build/MacOS/"$name_project
fi
mkdir -p "../Build/MacOS/"$name_project

rm -rf "../Lib/MacOS/"$name_lib
mkdir -p "../Lib/MacOS"

cd ..
cd Build
cd MacOS
cd $name_project

#lib
if [ "$debug" == "debug" ]; then
    cmake -DDEBUG=1 -DCMAKE_BUILD_TYPE=Debug ../../../Sources/$name/
else
    cmake ../../../Sources/$name/
fi
make

cd ..
cd ..
cd ..
cd Compile

cp -rfp "../Build/MacOS/"$name_project"/"$name_lib "../Lib/MacOS/"$name_lib


folderSrc="../Sources/$name/include"
folderDst="../Include/MacOS/"$name
rm -rf $folderDst
mkdir -p $folderDst

mkdir -p ${folderDst}/glad
for file in ${folderSrc}/glad/*.h
do 
    cp -rfp $file ${folderDst}/glad
done

mkdir -p ${folderDst}/KHR
for file in ${folderSrc}/KHR/*.h
do 
    cp -rfp $file ${folderDst}/KHR
done