/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2022-10-30
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _OPENGL_BASE_H_
#define _OPENGL_BASE_H_

#include "PreDefine.h"

namespace LostPeterOpenGL
{
    class openglExport OpenGLBase
    {
    public:
        OpenGLBase(int width, int height, String name);
        virtual ~OpenGLBase();

    public:
        static FLogManager* ms_pLogManager;

    public:
        int versionGL_Major;
        int versionGL_Minor;
        const char* versionGLSL;    

    public:
        int width;
        int height;
        float aspectRatio;
        GLFWwindow* pWindow;

        bool isAppPaused;           //is the application paused?
        bool isMinimized;           //is the application minimized?
        bool isMaximized;           //is the application maximized?
        bool isResizing;            //is the resize bars being dragged?
        bool isFullscreenState;     //is fullscreen enabled
        bool isMinimizedWindowNeedClose; //is Minimalized Window Need Close

        bool isCreateDevice;        //is create device
        bool isLoadAsset;           //is load asset

        FTimer* pTimer;
        float fTimeLastFPS;
        float fFPS;
        int nFrameFPS;
        uint64 nFrameTotal;

    protected:
        String nameTitle;
        String pathBin; 

    public:
        int GetWidth() const { return this->width; }
        int GetHeight() const { return this->height; }
        float RefreshAspectRatio();

        const String& GetTitle() const { return this->nameTitle; }


    public:
        // Common
        virtual void OnInit() = 0;
        virtual void OnLoad() = 0;
        virtual bool OnIsInit() = 0;
        virtual void OnResize(int w, int h, bool force) = 0;

        virtual bool OnBeginCompute_BeforeRender() = 0;
            virtual void OnUpdateCompute_BeforeRender() = 0;
            virtual void OnCompute_BeforeRender() = 0;
        virtual void OnEndCompute_BeforeRender() = 0;

        virtual bool OnBeginRender() = 0;
            virtual void OnUpdateRender() = 0;
            virtual void OnRender() = 0;
        virtual void OnEndRender() = 0;

        virtual bool OnBeginCompute_AfterRender() = 0;
            virtual void OnUpdateCompute_AfterRender() = 0;
            virtual void OnCompute_AfterRender() = 0;
        virtual void OnEndCompute_AfterRender() = 0;

        virtual void OnPresent() = 0;
        virtual void OnDestroy() = 0;

        // Mouse Input
        virtual void OnMouseInput() { }
        virtual void OnMouseLeftDown(double x, double y) { }
        virtual void OnMouseLeftUp(double x, double y) { }
        virtual void OnMouseRightDown(double x, double y) { }
        virtual void OnMouseRightUp(double x, double y) { }
        virtual void OnMouseMiddleDown(double x, double y) { }
        virtual void OnMouseMiddleUp(double x, double y) { }
        virtual void OnMouseMove(int button, double x, double y) { }
        virtual void OnMouseHover(double x, double y) { }
        virtual void OnMouseWheel(double x, double y) { }

        // Keyboard Input
        virtual void OnKeyboardInput() { }
        virtual void OnKeyDown(int key) { }
        virtual void OnKeyUp(int key) { }

        // Camera Process
        virtual void OnCameraMouseMoveProcess(double newX, double newY, double oldX, double oldY) { }
        virtual void OnCameraMouseZoomProcess(double zoom) { }
        virtual void OnCameraMouseKeyboardProcess() { }

        // Editor Coordinate Process
        virtual void OnEditorCoordinateMouseLeftDown(double x, double y) { }
        virtual void OnEditorCoordinateMouseMove(double x, double y) { }
        virtual void OnEditorCoordinateMouseLeftUp(double x, double y) { }
        virtual void OnEditorCoordinateMouseHover(double x, double y) { }

    public:
        virtual void CalculateFrameStats(GLFWwindow* s_pWindow);

        virtual void UpdateTimer();

    public:
        String GetAssetFullPath(const String& assetName);

    };

}; //LostPeterOpenGL

#endif