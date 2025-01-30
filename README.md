# README #

Author: 

    LostPeter

Target: 

    Learning opengl render api, compile in different platform with CMake and code the samples !

Github Address:

    LostPeter GitHub: https://github.com/LostPeter/LostPeterOpenGL

Document Web: 

    LostPeter 知乎: https://www.zhihu.com/people/lostpeter

Usage:

    OpenGL SDK: 
        

    MacOS:   
        Only support to gl4.1

    Windows: 
        using gl4.6

    VSCode:
        Config above complete, I'm only using VSCode to edit, compile and debug code in platform Windows/MacOS.
        You can look at .vscode/launch.json file, config your vscode, there are all samples debug config, it is nice and effective to debug direct in vscode.
    

    Build Auto: 
        MacOS:      ./Build_MacOS.sh debug rebuild depends
        Windows:    ./Build_Windows.bat debug rebuild depends

        param1: debug or other is release
        param2: rebuild or other is not rebuild
        param3: depends or other is not build depends


    Build Custom:
    1> Compile Dependencies
        cd Dependencies
        cd Compile
        MacOS:      ./Build_MacOS_lib_all.sh debug rebuild
        Windows:    ./Build_Windows_lib_all.bat debug rebuild

        used dependencies libraries：
            assimp-5.2.4
            glad-4.1(MacOS)
            glad-4.6(Windows)
            glfw-3.3.6
            glm-0.9.9.8
            imgui-1.85
            libcpuid-0.5.1
            libnoise-1.0.0
            libsquish-1.15
            rapidxml-1.13
            spdlog-1.10.0
            stb-0.02
            tinyxml-2.6.2
            zlib-1.2.11
            zziplib-0.13.72

    2> Compile Shader
        cd Bin
        cd Shader
        MacOS:      ./Build_MacOS_Shader_GLSL_All.sh
        Windows:    ./Build_Windows_Shader_GLSL_All.bat

        Always using glsl shader, maybe realize spir-v(must gl4.6, MacOS not support(Only support to gl4.1)) for windows later.

    3> Compile LostPeterOpenGL
        cd LostPeterOpenGL
        cd Compile
        MacOS:      ./Build_MacOS_LostPeterOpenGL.sh debug rebuild
        Windows:    ./Build_Windows_LostPeterOpenGL.bat debug rebuild

    4> Compile Samples
        cd Sample
        cd Compile
        MacOS:      ./Build_MacOS_Sample_All.sh debug rebuild
        Windows:    ./Build_Windows_Sample_All.bat debug rebuild

License:

    MIT License 


### <000> opengl_000_window
[OpenGL学习例子000: opengl_000_window 基础跨平台窗口显示](https://zhuanlan.zhihu.com/p/19289601385)
* sample000：Setup a framework, compile all sort of dependencies libraries, show a Window 

![image](https://github.com/LostPeter/LostPeterOpenGL/blob/main/Images/opengl_000_window.png)