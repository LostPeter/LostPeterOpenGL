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

name_sample=${1}
debug=${2}
rebuild=${3}

if [ "$debug" == "debug" ]; then
    name_project=$name_sample"_d"
else
    name_project=$name_sample
fi

#Build Sample
if [ "$rebuild" == "rebuild" ]; then
    rm -rf "../Build/MacOS/"$name_project
fi
mkdir -p "../Build/MacOS/"$name_project

rm -rf "../../Bin/MacOS/"$name_project
mkdir -p "../../Bin/MacOS"

cd ..
cd Build
cd MacOS
cd $name_project

if [ "$debug" == "debug" ]; then
    cmake -DDEBUG=1 ../../../$name_sample
else
    cmake ../../../$name_sample
fi
make

cd ..
cd ..
cd ..
cd Compile

cp -rfp "../Build/MacOS/$name_project/$name_project" "../../Bin/MacOS"