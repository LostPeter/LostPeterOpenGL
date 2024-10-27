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

#ifndef _OPENGL_WINDOW_H_
#define _OPENGL_WINDOW_H_

#include "OpenGLBase.h"
#include "OpenGLDefine.h"

namespace LostPeterOpenGL
{
    class openglExport OpenGLWindow : public OpenGLBase
    {
    public:
        OpenGLWindow(int width, int height, String name);
        virtual ~OpenGLWindow();

    public:
        

    ///////////////////////// Internal /////////////////////////


    public:

        FVector2 poFramebufferSize;
        FVector2 poWindowContentScale;


        bool isFrameBufferResized;

        //Mouse
        FVector2 mousePosLast;
        bool mouseButtonDownLeft;
        bool mouseButtonDownRight;
        bool mouseButtonDownMiddle;

    public: 
        static bool s_isEnableValidationLayers;
        static int s_maxFramesInFight;

    public:
        // Common
        virtual void OnInit();
        virtual void OnLoad();
        virtual bool OnIsInit();
        virtual void OnResize(int w, int h, bool force);
        virtual bool OnBeginCompute();
            virtual void OnUpdateCompute();
            virtual void OnCompute();
        virtual void OnEndCompute();
        virtual bool OnBeginRender();
            virtual void OnUpdateRender();
            virtual void OnRender();
        virtual void OnEndRender();
        virtual void OnDestroy();

        // Mouse Input
        virtual void OnMouseInput();
        virtual void OnMouseLeftDown(double x, double y);
        virtual void OnMouseLeftUp(double x, double y);
        virtual void OnMouseRightDown(double x, double y);
        virtual void OnMouseRightUp(double x, double y);
        virtual void OnMouseMiddleDown(double x, double y);
        virtual void OnMouseMiddleUp(double x, double y);
        virtual void OnMouseMove(int button, double x, double y);
        virtual void OnMouseHover(double x, double y);
        virtual void OnMouseWheel(double x, double y);

        // Keyboard Input
        virtual void OnKeyboardInput();
        virtual void OnKeyDown(int key);
        virtual void OnKeyUp(int key);

        // Camera Process
        virtual void OnCameraMouseMoveProcess(double newX, double newY, double oldX, double oldY);
        virtual void OnCameraMouseZoomProcess(double zoom);
        virtual void OnCameraMouseKeyboardProcess();

        // Editor Coordinate Process
        virtual void OnEditorCoordinateMouseLeftDown(double x, double y);
        virtual void OnEditorCoordinateMouseMove(double x, double y);
        virtual void OnEditorCoordinateMouseLeftUp(double x, double y);
        virtual void OnEditorCoordinateMouseHover(double x, double y);

    public:


    public:


    public:
        //Create Pipeline
        virtual void createPipeline();
            virtual void createWindowCallback();
            virtual void createDevice();


            virtual void createFeatureSupport();

    };

}; //LostPeterOpenGL

#endif