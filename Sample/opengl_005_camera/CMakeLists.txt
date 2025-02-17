#****************************************************************************
# LostPeterOpenGL - Copyright (C) 2022 by LostPeter
# 
# Author:   LostPeter
# Time:     2024-11-10
# Github:   https://github.com/LostPeter/LostPeterOpenGL
# Document: https://www.zhihu.com/people/lostpeter/posts
#
# This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
#****************************************************************************/

CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
SET(NAME_PROJECT "opengl_005_camera")
if (DEBUG)
    PROJECT(${NAME_PROJECT}_d)
    SET(CMAKE_BUILD_TYPE "Debug")
    if (!WIN32)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif()

    MESSAGE(STATUS "Set Debug Build !")
else ()
    PROJECT(${NAME_PROJECT})
endif ()

SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 11)

#MESSAGE(STATUS "HOME dir: $ENV{HOME}")
MESSAGE(STATUS "Binary dir: ${PROJECT_BINARY_DIR}")
MESSAGE(STATUS "SOURCE dir: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "SYSTEM name: ${CMAKE_SYSTEM_NAME}")
MESSAGE(STATUS "SYSTEM version: ${CMAKE_SYSTEM_VERSION}")
MESSAGE(STATUS "SYSTEM processor: ${CMAKE_SYSTEM_PROCESSOR}")

#HEADER_FILES
FILE(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
MESSAGE(STATUS "HEADER files: ${HEADER_FILES}")

#SOURCE_FILES_CPP
FILE(GLOB_RECURSE SOURCE_FILES_CPP "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
MESSAGE(STATUS "SOURCE .cpp files: ${SOURCE_FILES_CPP}")


#LIB_INCLUDE
if (WIN32)
    SET(LIB_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/assimp-5.2.4"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/glad-4.6"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/glfw-3.3.6"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/glm-0.9.9.8"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/imgui-1.85_glfw_gl3"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/libnoise-1.0.0"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/include/Windows/rapidxml-1.13"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/spdlog-1.10.0"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/stb-0.02"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/tinyxml-2.6.2"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/Windows/zlib-1.2.11"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../LostPeterOpenGL/LostPeterFoundation/include"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../LostPeterOpenGL/LostPeterOpenGL/include")   

elseif (APPLE)
    SET(LIB_INCLUDE "/System/Library/Frameworks/OpenGL.framework"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/assimp-5.2.4"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/glad-4.1"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/glfw-3.3.6"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/glm-0.9.9.8"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/imgui-1.85_glfw_gl3"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/libnoise-1.0.0"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/include/MacOS/rapidxml-1.13"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/spdlog-1.10.0"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/stb-0.02"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/tinyxml-2.6.2"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Include/MacOS/zlib-1.2.11"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../LostPeterOpenGL/LostPeterFoundation/include"
                    "${CMAKE_CURRENT_SOURCE_DIR}/../../LostPeterOpenGL/LostPeterOpenGL/include")

    SET(SYS_FRAMEWORKS_DIR /System/Library/Frameworks)
    SET(OPENGL_LIBS ${SYS_FRAMEWORKS_DIR}/OpenGL.framework)
    SET(COCOA_LIBS ${SYS_FRAMEWORKS_DIR}/Cocoa.framework)
    SET(COREVIDEO_LIBS ${SYS_FRAMEWORKS_DIR}/CoreVideo.framework)
    SET(IOKIT_LIBS ${SYS_FRAMEWORKS_DIR}/IOKit.framework)

endif ()
MESSAGE(STATUS "LIB_INCLUDE: ${LIB_INCLUDE}")
INCLUDE_DIRECTORIES(${LIB_INCLUDE})

#LIB_DEPENDENCIES_DIR, LIB_PLUGINS_DIR
if (WIN32)
    SET(LIB_DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Lib/Windows")
    SET(LIB_PLUGINS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Plugins/Windows")

elseif (APPLE)
    SET(LIB_DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Dependencies/Lib/MacOS")
    SET(LIB_PLUGINS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Plugins/MacOS")

endif ()
MESSAGE(STATUS "LIB_DEPENDENCIES_DIR dir: ${LIB_DEPENDENCIES_DIR}")
MESSAGE(STATUS "LIB_PLUGINS_DIR dir: ${LIB_PLUGINS_DIR}")

if (WIN32)
    MESSAGE(STATUS "Build ${PROJECT_NAME} platfrom Win32 !")
    
    ADD_DEFINITIONS(-DNOISE_STATIC)
    if(MSVC)
        ADD_DEFINITIONS(/wd4251 /wd4275)
    endif()
    if (DEBUG)
        LINK_LIBRARIES(shlwapi.lib 
                       ${LIB_DEPENDENCIES_DIR}/assimp-5.2.4_d.lib
                       ${LIB_DEPENDENCIES_DIR}/glad-4.6_d.lib
                       ${LIB_DEPENDENCIES_DIR}/glfw-3.3.6_d.lib
                       ${LIB_DEPENDENCIES_DIR}/imgui-1.85_glfw_gl3_d.lib
                       ${LIB_DEPENDENCIES_DIR}/libnoise-1.0.0_d.lib
                       ${LIB_DEPENDENCIES_DIR}/libnoiseutils-1.0.0_d.lib
                       ${LIB_DEPENDENCIES_DIR}/tinyxml-2.6.2_d.lib
                       ${LIB_DEPENDENCIES_DIR}/zlib-1.2.11_d.lib
                       ${LIB_PLUGINS_DIR}/LostPeterFoundation_d.lib
                       ${LIB_PLUGINS_DIR}/LostPeterOpenGL_d.lib)
    else ()
        LINK_LIBRARIES(shlwapi.lib 
                       ${LIB_DEPENDENCIES_DIR}/assimp-5.2.4.lib
                       ${LIB_DEPENDENCIES_DIR}/glad-4.6.lib
                       ${LIB_DEPENDENCIES_DIR}/glfw-3.3.6.lib
                       ${LIB_DEPENDENCIES_DIR}/imgui-1.85_glfw_gl3.lib
                       ${LIB_DEPENDENCIES_DIR}/libnoise-1.0.0.lib
                       ${LIB_DEPENDENCIES_DIR}/libnoiseutils-1.0.0.lib
                       ${LIB_DEPENDENCIES_DIR}/tinyxml-2.6.2.lib
                       ${LIB_DEPENDENCIES_DIR}/zlib-1.2.11.lib
                       ${LIB_PLUGINS_DIR}/LostPeterFoundation.lib
                       ${LIB_PLUGINS_DIR}/LostPeterOpenGL.lib)
    endif()
    ADD_EXECUTABLE(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES_CPP})

elseif (APPLE)
    MESSAGE(STATUS "Build ${PROJECT_NAME} platfrom MacOS !")
    
    ADD_EXECUTABLE(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES_CPP} ${SOURCE_FILES_MM})
    if (DEBUG)
        TARGET_LINK_LIBRARIES(${PROJECT_NAME}
                              ${LIB_PLUGINS_DIR}/libLostPeterFoundation_d.dylib
                              ${LIB_PLUGINS_DIR}/libLostPeterOpenGL_d.dylib)
    else ()
        TARGET_LINK_LIBRARIES(${PROJECT_NAME}
                              ${LIB_PLUGINS_DIR}/libLostPeterFoundation.dylib
                              ${LIB_PLUGINS_DIR}/libLostPeterOpenGL.dylib)
    endif()
    SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup -flat_namespace \
        -Wl,-search_paths_first"
    )
    
endif ()