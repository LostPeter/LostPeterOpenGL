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

#include "../include/PreInclude.h"
#include "../include/OpenGLWindow.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include <stb_image.h>

namespace LostPeterOpenGL
{
#if F_DEBUG == 1
    bool OpenGLWindow::s_isEnableValidationLayers = true;
#else
    bool OpenGLWindow::s_isEnableValidationLayers = false;
#endif
    int OpenGLWindow::s_maxFramesInFight = 2;
    

    /////////////////////////// OpenGLWindow //////////////////////
    OpenGLWindow::OpenGLWindow(int width, int height, String name)
        : OpenGLBase(width, height, name)
    {
        Base::ms_pOpenGLWindow = this;
    }

    OpenGLWindow::~OpenGLWindow()
    {

    }

    void OpenGLWindow::OnInit()
    {

    }

    void OpenGLWindow::OnLoad()
    {

    }

    bool OpenGLWindow::OnIsInit()
    {
        return this->isCreateDevice &&
            this->isLoadAsset;
    }

    void OpenGLWindow::OnResize(int w, int h, bool force)
    {

    }

    bool OpenGLWindow::OnBeginCompute()
    {
        return false;
    }
        void OpenGLWindow::OnUpdateCompute()
        {

        }
        void OpenGLWindow::OnCompute()
        {

        }
    void OpenGLWindow::OnEndCompute()
    {

    }

    bool OpenGLWindow::OnBeginRender()
    {
        return false;
    }
        void OpenGLWindow::OnUpdateRender()
        {

        }
        void OpenGLWindow::OnRender()
        {

        }
    void OpenGLWindow::OnEndRender()
    {

    }

    void OpenGLWindow::OnDestroy()
    {
        
    }

    void OpenGLWindow::OnMouseInput()
    {   
        double cursorX; double cursorY;
        glfwGetCursorPos(this->pWindow, &cursorX, &cursorY);
        cursorX *= this->poWindowContentScale.x;
        cursorY *= this->poWindowContentScale.y;

        //Mouse Left
        int actionLeft = glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_LEFT);
        if (actionLeft == GLFW_PRESS)
        {
            if (!this->mouseButtonDownLeft)
            {
                OnMouseLeftDown(cursorX, cursorY);
            }
            else
            {
                OnMouseMove(GLFW_MOUSE_BUTTON_LEFT, cursorX, cursorY);
            }
        }
        else
        {
            if (this->mouseButtonDownLeft)
            {
                OnMouseLeftUp(cursorX, cursorY);
            }
        }
        
        //Mouse Right
        int actionRight = glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_RIGHT);
        if (actionRight == GLFW_PRESS)
        {
            if (!this->mouseButtonDownRight)
            {
                OnMouseRightDown(cursorX, cursorY);
            }
            else
            {
                OnMouseMove(GLFW_MOUSE_BUTTON_RIGHT, cursorX, cursorY);
            }
        }
        else
        {
            if (this->mouseButtonDownRight)
            {
                OnMouseRightUp(cursorX, cursorY);
            }
        }

        //Mouse Middle
        int actionMiddle = glfwGetMouseButton(this->pWindow, GLFW_MOUSE_BUTTON_MIDDLE);
        if (actionMiddle == GLFW_PRESS)
        {
            if (!this->mouseButtonDownMiddle)
            {
                OnMouseMiddleDown(cursorX, cursorY);
            }
            else
            {
                OnMouseMove(GLFW_MOUSE_BUTTON_MIDDLE, cursorX, cursorY);
            }
        }
        else
        {
            if (this->mouseButtonDownMiddle)
            {
                OnMouseMiddleUp(cursorX, cursorY);
            }
        }

        //Mouse Hover
        if (!this->mouseButtonDownLeft &&
            !this->mouseButtonDownRight &&
            !this->mouseButtonDownMiddle)
        {
            OnMouseHover(cursorX, cursorY);
        }

        this->mousePosLast.x = (float)cursorX;
        this->mousePosLast.y = (float)cursorY;
    }
    void OpenGLWindow::OnMouseLeftDown(double x, double y)
    {
        this->mouseButtonDownLeft = true;
        {
            OnEditorCoordinateMouseLeftDown(x, y);
        }
    }
    void OpenGLWindow::OnMouseLeftUp(double x, double y)
    {   
        this->mouseButtonDownLeft = false;

        OnEditorCoordinateMouseLeftUp(x, y);
    }
    void OpenGLWindow::OnMouseRightDown(double x, double y)
    {
        this->mouseButtonDownRight = true;
        {

        }
    }
    void OpenGLWindow::OnMouseRightUp(double x, double y)
    {
        this->mouseButtonDownRight = false;

    }
    void OpenGLWindow::OnMouseMiddleDown(double x, double y)
    {
        this->mouseButtonDownMiddle = true;
        {

        }
    }
    void OpenGLWindow::OnMouseMiddleUp(double x, double y)
    {
        this->mouseButtonDownMiddle = false;

    }   
    void OpenGLWindow::OnMouseMove(int button, double x, double y)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            OnEditorCoordinateMouseMove(x, y);

        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            OnCameraMouseMoveProcess(x, y, this->mousePosLast.x, this->mousePosLast.y);
            
        }
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        {
            
        }
    }
    void OpenGLWindow::OnMouseHover(double x, double y)
    {
        OnEditorCoordinateMouseHover(x, y);

    }
    void OpenGLWindow::OnMouseWheel(double x, double y)
    {
        OnCameraMouseZoomProcess(y);

    }

    void OpenGLWindow::OnKeyboardInput()
    {
        OnCameraMouseKeyboardProcess();

    }
    void OpenGLWindow::OnKeyDown(int key)
    {
        if (key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(this->pWindow, true);
        }
        if (key == GLFW_KEY_R)
        {

        }
        if (key == GLFW_KEY_T)
        {

        }
        if (key == GLFW_KEY_F)
        {

        }
    }
    void OpenGLWindow::OnKeyUp(int key)
    {

    }

    void OpenGLWindow::OnCameraMouseMoveProcess(double newX, double newY, double oldX, double oldY)
    {

    }
    void OpenGLWindow::OnCameraMouseZoomProcess(double zoom) 
    {

    }
    void OpenGLWindow::OnCameraMouseKeyboardProcess()
    {
       
    }

    void OpenGLWindow::OnEditorCoordinateMouseLeftDown(double x, double y)
    {

    }
    void OpenGLWindow::OnEditorCoordinateMouseMove(double x, double y)
    {

    }
    void OpenGLWindow::OnEditorCoordinateMouseLeftUp(double x, double y)
    {

    }
    void OpenGLWindow::OnEditorCoordinateMouseHover(double x, double y)
    {

    }   

}; //LostPeterOpenGL