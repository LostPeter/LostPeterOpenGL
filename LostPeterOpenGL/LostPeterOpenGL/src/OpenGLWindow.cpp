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
    const String OpenGLWindow::c_strShaderProgram = "ShaderProgram";
    OpenGLWindow::OpenGLWindow(int width, int height, String name)
        : OpenGLBase(width, height, name)


        , poVertexCount(0)
        , poVertexBuffer_Size(0)
        , poVertexBuffer_Data(nullptr)
        , poIndexCount(0)
        , poIndexBuffer_Size(0)
        , poIndexBuffer_Data(nullptr)
        , pBufferVertex(nullptr)
        , pBufferVertexIndex(nullptr)

        , poTypeVertex(F_MeshVertex_Pos3Color4Normal3Tangent3Tex2)
        , poShaderVertex(nullptr)
        , poShaderFragment(nullptr)
        , poShaderProgram(nullptr)

        , poTexture(nullptr)
        
        , isFrameBufferResized(false)


        , cfg_colorBackground(0.0f, 0.2f, 0.4f, 1.0f)


        , cfg_isMSAA(false)
        , cfg_isImgui(false)
        , cfg_isWireFrame(false)
        , cfg_isRotate(false)

        , cfg_glPrimitiveTopology(GL_TRIANGLES)


        , cfg_cameraPos(0.0f, 0.0f, -5.0f)
        , cfg_cameraLookTarget(0.0f, 0.0f, 0.0f)
        , cfg_cameraUp(0.0f, 1.0f, 0.0f)
        , cfg_cameraFov(45.0f)
        , cfg_cameraNear(0.05f)
        , cfg_cameraFar(1000.0f)
        , cfg_cameraSpeedMove(1000.0f)
        , cfg_cameraSpeedZoom(0.1f)
        , cfg_cameraSpeedRotate(0.1f)


        , cfg_model_Path("")
        , cfg_shaderVertex_Path("")
        , cfg_shaderFragment_Path("")
        , cfg_texture_Path("")
        , cfg_terrain_Path("")
        , cfg_terrainTextureDiffuse_Path("Assets/Texture/Terrain/shore_sand_albedo.png;Assets/Texture/Terrain/moss_albedo.png;Assets/Texture/Terrain/rock_cliff_albedo.png;Assets/Texture/Terrain/cliff_albedo.png")
        , cfg_terrainTextureNormal_Path("Assets/Texture/Terrain/shore_sand_norm.png;Assets/Texture/Terrain/moss_norm.tga;Assets/Texture/Terrain/rock_cliff_norm.tga;Assets/Texture/Terrain/cliff_norm.png")
        , cfg_terrainTextureControl_Path("Assets/Texture/Terrain/terrain_control.png")
        , cfg_terrainHeightStart(0.0f)
        , cfg_terrainHeightMax(200.0f)


        , imgui_IsEnable(false)
        , imgui_MinimalSwapchainImages(0)
        , imgui_PathIni("")
        , imgui_PathLog("")

        , pCamera(nullptr)
        , pCameraRight(nullptr)
        , pCameraMainLight(new FCamera)

        , mouseButtonDownLeft(false)
        , mouseButtonDownRight(false)
        , mouseButtonDownMiddle(false)

        , cfg_isEditorCreate(false)
        , cfg_isEditorGridShow(false)
        , cfg_isEditorCameraAxisShow(false)
        , cfg_isEditorCoordinateAxisShow(false)
        , cfg_editorGrid_Color(0.5f, 0.5f, 0.5f, 0.5f)
        , cfg_editorCoordinateAxis_MoveSpeed(0.01f)
        , cfg_editorCoordinateAxis_RotateSpeed(0.01f)
        , cfg_editorCoordinateAxis_ScaleSpeed(0.01f)
        , pEditorGrid(nullptr)
        , pEditorCameraAxis(nullptr)
        , pEditorCoordinateAxis(nullptr)
        , pEditorLineFlat2DCollector(nullptr)
        , pEditorLineFlat3DCollector(nullptr)
    {

        Base::ms_pWindow = this;
    }

    OpenGLWindow::~OpenGLWindow()
    {
        F_DELETE(pCamera)
        F_DELETE(pCameraRight)
        F_DELETE(pCameraMainLight)
    }

    void OpenGLWindow::OnInit()
    {
        createPipeline();
    }

    void OpenGLWindow::OnLoad()
    {
        loadAssets();
    }

    bool OpenGLWindow::OnIsInit()
    {
        return this->isCreateDevice &&
            this->isLoadAsset;
    }

    void OpenGLWindow::OnResize(int w, int h, bool force)
    {
        resizeWindow(w, h, force);

        if (this->pCamera != nullptr)
        {
            this->pCamera->PerspectiveLH(glm::radians(this->cfg_cameraFov), this->aspectRatio, this->cfg_cameraNear, this->cfg_cameraFar);
        }
    }

    bool OpenGLWindow::OnBeginCompute_BeforeRender()
    {
        return false;
    }
        void OpenGLWindow::OnUpdateCompute_BeforeRender()
        {

        }
        void OpenGLWindow::OnCompute_BeforeRender()
        {

        }
    void OpenGLWindow::OnEndCompute_BeforeRender()
    {

    }


    bool OpenGLWindow::OnBeginCompute_AfterRender()
    {
        return false;
    }
        void OpenGLWindow::OnUpdateCompute_AfterRender()
        {

        }
        void OpenGLWindow::OnCompute_AfterRender()
        {

        }
    void OpenGLWindow::OnEndCompute_AfterRender()
    {

    }


    bool OpenGLWindow::OnBeginRender()
    {
        return beginRender();
    }
        void OpenGLWindow::OnUpdateRender()
        {
            updateRender();
        }
        void OpenGLWindow::OnRender()
        {
            render();
        }
    void OpenGLWindow::OnEndRender()
    {
        endRender();
    }


    void OpenGLWindow::OnPresent()
    {

    }
    void OpenGLWindow::OnDestroy()
    {
        //1> Wait
        if (this->isCreateDevice)
        {

            //2> Cleanup
            cleanup();
        }
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
            cameraReset();
        }
        if (key == GLFW_KEY_T)
        {
            this->cfg_isRotate = !this->cfg_isRotate;
        }
        if (key == GLFW_KEY_F)
        {
            this->cfg_isWireFrame = !this->cfg_isWireFrame;
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

    bool OpenGLWindow::HasConfig_MASS()
    {
        return this->cfg_isMSAA;
    }
    bool OpenGLWindow::HasConfig_Imgui()
    {
        return this->cfg_isImgui;
    }

    bool OpenGLWindow::IsEnable_MASS()
    {
        return this->cfg_isMSAA;
    }
    bool OpenGLWindow::IsEnable_Imgui()
    {
        return this->cfg_isImgui &&
               this->imgui_IsEnable;
    }


    void OpenGLWindow::createPipeline()
    {
        F_LogInfo("**********<1> OpenGLWindow::createPipeline start **********");
        {
            //1> Create Resize callback
            createWindowCallback();
        
            //2> Create Device
            createDevice();

            //3> Create Feature Support
            createFeatureSupport();

            //4> Create Command Objects
            createCommandObjects();

            //5> Create Swap Chain Objects
            createSwapChainObjects();


            //8> Camera/Light/Shadow/Terrain
            createCamera();
            createLightMain();
            createShadowLightMain();
            createTerrain();

            //9> Create Pipeline Objects
            createPipelineObjects();



            //13> isCreateDevice
            this->isCreateDevice = true;
        }
        F_LogInfo("**********<1> OpenGLWindow::createPipeline finish **********");
    }
    //glfw: whenever the window size changed (by OS or user resize) this callback function executes
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        OpenGLWindow* pWnd = (OpenGLWindow*)glfwGetWindowUserPointer(window);
        pWnd->isFrameBufferResized = true;
        pWnd->OnResize(width, height, false);
    }
    void OpenGLWindow::createWindowCallback()
    {   
        glfwSetWindowUserPointer(this->pWindow, this);
        glfwSetFramebufferSizeCallback(this->pWindow, framebuffer_size_callback);

        F_LogInfo("*****<1-1> OpenGLWindow::createWindowCallback finish *****");
    }
    void OpenGLWindow::createDevice()
    {
        F_LogInfo("*****<1-2> OpenGLWindow::createDevice start *****");
        {
            //1> make window
            glfwMakeContextCurrent(this->pWindow);
            glfwSwapInterval(1); // Enable vsync
            glfwSetFramebufferSizeCallback(this->pWindow, framebuffer_size_callback);

            //2> glad load all OpenGL function pointers 
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                F_LogError("*********************** OpenGLWindow::createDevice: gladLoadGLLoader failed !");
                glfwTerminate();
                return;
            }

            //3> setUpDebugMessenger
            setUpDebugMessenger();

            //4> GLDebug
            this->poDebug = new GLDebug();
            this->poDebug->Init();


        }
        F_LogInfo("*****<1-2> OpenGLWindow::createDevice finish *****");
    }
        void APIENTRY glDebugOutput(GLenum source, 
                                    GLenum type, 
                                    unsigned int id, 
                                    GLenum severity, 
                                    GLsizei length, 
                                    const char *message, 
                                    const void *userParam)
        {
            if (id <= 0)
                return;
            if(id == 131169 || id == 131185 || id == 131218 || id == 131204) 
                return; // ignore these non-significant error codes

            String prefix("");
            String msg = "Debug message (" + FUtilString::SaveUInt(id) + "): " + message;

            switch (source)
            {
                case GL_DEBUG_SOURCE_API:             prefix = "Source: API"; break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   prefix = "Source: Window System"; break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER: prefix = "Source: Shader Compiler"; break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:     prefix = "Source: Third Party"; break;
                case GL_DEBUG_SOURCE_APPLICATION:     prefix = "Source: Application"; break;
                case GL_DEBUG_SOURCE_OTHER:           prefix = "Source: Other"; break;
            }

            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR:               prefix = "Type: Error"; break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: prefix = "Type: Deprecated Behaviour"; break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  prefix = "Type: Undefined Behaviour"; break; 
                case GL_DEBUG_TYPE_PORTABILITY:         prefix = "Type: Portability"; break;
                case GL_DEBUG_TYPE_PERFORMANCE:         prefix = "Type: Performance"; break;
                case GL_DEBUG_TYPE_MARKER:              prefix = "Type: Marker"; break;
                case GL_DEBUG_TYPE_PUSH_GROUP:          prefix = "Type: Push Group"; break;
                case GL_DEBUG_TYPE_POP_GROUP:           prefix = "Type: Pop Group"; break;
                case GL_DEBUG_TYPE_OTHER:               prefix = "Type: Other"; break;
            }
            
            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:         prefix = "Severity: high"; break;
                case GL_DEBUG_SEVERITY_MEDIUM:       prefix = "Severity: medium"; break;
                case GL_DEBUG_SEVERITY_LOW:          prefix = "Severity: low"; break;
                case GL_DEBUG_SEVERITY_NOTIFICATION: prefix = "Severity: notification"; break;
            } 

            F_LogInfo("[%s]: [%s]", prefix.c_str(), msg.c_str());
        }
        void OpenGLWindow::setUpDebugMessenger()
        {
            if (s_isEnableValidationLayers)
            {
                int flags; 
                glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
                if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
                {
                    glEnable(GL_DEBUG_OUTPUT);
                    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
                    glDebugMessageCallback(glDebugOutput, nullptr);
                    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
                }
            }
            
            F_LogInfo("<1-1-2> OpenGLWindow::setUpDebugMessenger finish !");
        }


    void OpenGLWindow::createFeatureSupport()
    {

    }

    void OpenGLWindow::createCamera()
    {
        if (this->pCamera == nullptr)
        {
            this->pCamera = new FCamera();
        }
    }
    void OpenGLWindow::createLightMain()
    {

    }
    void OpenGLWindow::createShadowLightMain()
    {

    }
    void OpenGLWindow::createTerrain()
    {

    }


    void OpenGLWindow::createCommandObjects()
    {
        F_LogInfo("*****<1-4> OpenGLWindow::createCommandObjects start *****");
        {
            


        }
        F_LogInfo("*****<1-4> OpenGLWindow::createCommandObjects finish *****");
    }


    void OpenGLWindow::createSwapChainObjects()
    {
        F_LogInfo("*****<1-5> OpenGLWindow::createSwapChainObjects start *****");
        {
            //1> createSwapChain
            createSwapChain();

            //2> createSwapChainImageViews
            createSwapChainImageViews();

            //3> createColorResources
            if (HasConfig_MASS())
            {
                createColorResources();
            }

            //4> createDepthResources
            createDepthResources();

            //5> createColorResourceLists
            createColorResourceLists();
        }
        F_LogInfo("*****<1-5> OpenGLWindow::createSwapChainObjects finish *****");
    }
        void OpenGLWindow::createSwapChain()
        {
            //1> Default Framebuffer Color/Depth format
            glGetIntegerv(GL_COLOR_ATTACHMENT0, &this->poSwapChainImageFormat);
            glGetIntegerv(GL_DEPTH_STENCIL_ATTACHMENT, &this->poDepthImageFormat);

            //2> Framebuffer
            int w, h;
            glfwGetFramebufferSize(this->pWindow, &w, &h);
            this->poFramebufferSize.x = (float)w;
            this->poFramebufferSize.y = (float)h;
            float scaleX, scaleY;
            glfwGetWindowContentScale(this->pWindow, &scaleX, &scaleY);
            this->poWindowContentScale.x = scaleX;
            this->poWindowContentScale.y = scaleY;
            F_LogInfo("<1-5-1> OpenGLWindow::createSwapChain finish, Swapchain size: [%d,%d], window size: [%d,%d], scale: [%f, %f], format color: [%d], format depth: [%d] !", 
                      w, h, this->width, this->height, scaleX, scaleY, this->poSwapChainImageFormat, this->poDepthImageFormat);
            
            createViewport();
        }
            void OpenGLWindow::createViewport()
            {
                int w = (int)this->poFramebufferSize.x;
                int h = (int)this->poFramebufferSize.y;

                this->poOffset.x = 0;
                this->poOffset.y = 0;
                this->poExtent.x = w;
                this->poExtent.y = h;

                this->poViewport.left = 0;
                this->poViewport.top = 0;
                this->poViewport.right = w;
                this->poViewport.bottom = h;

                this->poScissor.left = 0;
                this->poScissor.top = 0;
                this->poScissor.right = w;
                this->poScissor.bottom = h;
            }
        void OpenGLWindow::createSwapChainImageViews()
        {

        }
            void OpenGLWindow::createColorResources()
            {

            }
            void OpenGLWindow::createDepthResources()
            {

            }
        void OpenGLWindow::createColorResourceLists()
        {

        }


    void OpenGLWindow::createPipelineObjects()
    {
        F_LogInfo("*****<1-9> OpenGLWindow::createPipelineObjects start *****");
        {
            //1> createRenderPasses
            createRenderPasses();
            F_LogInfo("<1-9-1> OpenGLWindow::createPipelineObjects: Success to create RenderPasses !");

            //2> createFramebuffers
            createFramebuffers();
            F_LogInfo("<1-9-2> OpenGLWindow::createPipelineObjects: Success to create Framebuffers !");
        }
        F_LogInfo("*****<1-9> OpenGLWindow::createPipelineObjects finish *****");
    }
        void OpenGLWindow::createRenderPasses()
        {
            createRenderPass_ShadowMap();
            createRenderPass_Default();
            createRenderPass_Cull();
            createRenderPass_Terrain();
            createRenderPass_Custom();
        }
            void OpenGLWindow::createRenderPass_ShadowMap()
            {

            }
            void OpenGLWindow::createRenderPass_Default()
            {

            }
            void OpenGLWindow::createRenderPass_Cull()
            {

            }
            void OpenGLWindow::createRenderPass_Terrain()
            {

            }
            void OpenGLWindow::createRenderPass_Custom()
            {

            }

                GLRenderPass* OpenGLWindow::createRenderPass_DefaultCustom()
                {
                    return nullptr;
                }
                GLRenderPass* OpenGLWindow::createRenderPass_KhrDepth(int formatSwapChain, int formatDepth)
                {
                    return nullptr;
                }
                GLRenderPass* OpenGLWindow::createRenderPass_KhrDepthImgui(int formatColor, int formatDepth, int formatSwapChain)
                {
                    return nullptr;
                }
                GLRenderPass* OpenGLWindow::createRenderPass_ColorDepthMSAA(int formatColor, int formatDepth, int formatSwapChain, int samples)
                {
                    return nullptr;
                }
                GLRenderPass* OpenGLWindow::createRenderPass_ColorDepthImguiMSAA(int formatColor, int formatDepth, int formatSwapChain, int samples)
                {
                    return nullptr;
                }

            


        void OpenGLWindow::createFramebuffers()
        {
            //1> createFramebuffer_Default
            createFramebuffer_Default();

            //2> createFramebuffer_Custom
            createFramebuffer_Custom();
        }
            void OpenGLWindow::createFramebuffer_Default()
            {

            }
            void OpenGLWindow::createFramebuffer_Custom()
            {

            }
                void OpenGLWindow::createFramebuffer_DefaultCustom()
                {

                }

            GLFrameBuffer* OpenGLWindow::createGLFrameBuffer(const String& nameFrameBuffer,
                                                             uint32_t width,
                                                             uint32_t height,
                                                             uint32_t layers)
            {
                GLFrameBuffer* pGLFrameBuffer = new GLFrameBuffer(nameFrameBuffer);
                if (!pGLFrameBuffer->Init(width, 
                                          height,
                                          layers))
                {
                    F_LogError("*********************** OpenGLWindow::createGLFrameBuffer: Create FrameBuffer failed, Name: [%s] !", nameFrameBuffer.c_str());
                    F_DELETE(pGLFrameBuffer)
                    return nullptr;
                }   

                return pGLFrameBuffer;
            }
            uint32 OpenGLWindow::createGLFrameBuffer()
            {
                uint32 nGLFrameBuffer = 0;
                glGenFramebuffers(1, &nGLFrameBuffer);
                if (nGLFrameBuffer <= 0)
                {
                    F_LogError("*********************** OpenGLWindow::createGLFrameBuffer: Create FrameBuffer failed, id: [%d] !", nGLFrameBuffer);
                    return 0;
                }
                return nGLFrameBuffer;
            }
            void OpenGLWindow::bindGLFrameBuffer(GLFrameBuffer* pGLFrameBuffer)
            {
                if (!pGLFrameBuffer)
                    return;
                bindGLFrameBuffer(pGLFrameBuffer->nFrameBufferID);
            }
            void OpenGLWindow::bindGLFrameBuffer(uint32 nGLFrameBuffer)
            {
                if (nGLFrameBuffer <= 0)
                {
                    F_LogError("*********************** OpenGLWindow::bindGLFrameBuffer: FrameBuffer id [%d] is not valid !", nGLFrameBuffer);
                    return;
                }
                glBindFramebuffer(GL_FRAMEBUFFER, nGLFrameBuffer);
            }
            void OpenGLWindow::destroyGLFrameBuffer(GLFrameBuffer* pGLFrameBuffer)
            {
                if (!pGLFrameBuffer)
                    return;
                destroyGLFrameBuffer(pGLFrameBuffer->nFrameBufferID);
            }
            void OpenGLWindow::destroyGLFrameBuffer(uint32 nGLFrameBuffer)
            {
                if (nGLFrameBuffer <= 0)
                    return;
                glDeleteFramebuffers(1, &nGLFrameBuffer);
            }


    void OpenGLWindow::loadAssets()
    {
        F_LogInfo("**********<2> OpenGLWindow::loadAssets start **********");
        {
            //0> Camera/Light/Shadow
            cameraReset();
            lightMainReset();
            shadowReset();
            terrainReset();

            //1> loadGeometry
            loadGeometry();

            //2> Imgui
            if (HasConfig_Imgui())
            {
                createImgui();
            }

            //3> Editor
            if (this->cfg_isEditorCreate)
            {
                createEditor();
            }

            this->isLoadAsset = true;
        }
        F_LogInfo("**********<2> OpenGLWindow::loadAssets finish **********");
    }
        void OpenGLWindow::loadGeometry()
        {
            F_LogInfo("*****<2-1> OpenGLWindow::loadGeometry start *****");
            {
                //1> loadVertexIndexBuffer
                loadVertexIndexBuffer();

                //2> loadTexture
                loadTexture();

                //3> createConstBuffers
                createConstBuffers();

                //4> createCustomBeforePipeline
                createCustomBeforePipeline();

                //5> createGraphicsPipeline
                createGraphicsPipeline();

                //6> createComputePipeline
                createComputePipeline();


            }
            F_LogInfo("*****<2-1> OpenGLWindow::loadGeometry finish *****");
        }
            void OpenGLWindow::loadVertexIndexBuffer()
            {
                F_LogInfo("**<2-1-1> OpenGLWindow::loadVertexIndexBuffer start **");
                {
                    //1> loadModel
                    loadModel();

                    //2> createBufferVertexIndex
                    if (this->poVertexBuffer_Size > 0 &&
                        this->poVertexBuffer_Data != nullptr &&
                        this->poIndexBuffer_Size > 0 &&
                        this->poIndexBuffer_Data != nullptr)
                    {
                        this->pBufferVertexIndex = createBufferVertexIndex("VertexIndex-" + this->nameTitle,
                                                                           this->poTypeVertex,
                                                                           this->poVertexBuffer_Size,
                                                                           this->poVertexBuffer_Data,
                                                                           false,
                                                                           this->poIndexBuffer_Size,
                                                                           this->poIndexBuffer_Data,
                                                                           false);
                    }
                    //3> createBufferVertex
                    else if (this->poVertexBuffer_Size > 0 &&
                             this->poVertexBuffer_Data != nullptr)
                    {
                        this->pBufferVertex = createBufferVertex("Vertex-" + this->nameTitle,
                                                                 this->poTypeVertex,
                                                                 this->poVertexBuffer_Size, 
                                                                 this->poVertexBuffer_Data, 
                                                                 false);
                    }
                }
                F_LogInfo("**<2-1-1> OpenGLWindow::loadVertexIndexBuffer finish **");
            }
                void OpenGLWindow::loadModel()
                {
                    F_LogInfo("**<2-1-1-1> OpenGLWindow::loadModel start **");
                    {
                        //1> model 
                        if (!this->cfg_model_Path.empty())
                        {
                            loadModel_Default();
                        }
                        //2> model user
                        else
                        {
                            loadModel_Custom();
                        }
                    }
                    F_LogInfo("**<2-1-1-1> OpenGLWindow::loadModel finish **");
                }
                    void OpenGLWindow::loadModel_Default()
                    {

                    }
                    void OpenGLWindow::loadModel_Custom()
                    {

                    }
                GLBufferVertex* OpenGLWindow::createBufferVertex(const String& nameBuffer,
                                                                 FMeshVertexType type,
                                                                 size_t bufSize, 
                                                                 uint8* pBuf,
                                                                 bool isDelete)
                {
                    GLBufferVertex* pBufferVertex = new GLBufferVertex(nameBuffer);
                    if (!pBufferVertex->Init(type, 
                                             bufSize, 
                                             pBuf, 
                                             isDelete))
                    {
                        F_LogError("*********************** OpenGLWindow::createBufferVertex: Failed to create buffer vertex: [%s] !", nameBuffer.c_str());
                        F_DELETE(pBufferVertex)
                        return nullptr;
                    }
                    return pBufferVertex;
                }
                void OpenGLWindow::updateBufferVertex(GLBufferVertex* pBufferVertex,
                                                      FMeshVertexType type,
                                                      size_t bufSize, 
                                                      uint8* pBuf,
                                                      bool isDelete)
                {
                    if (pBufferVertex == nullptr)
                        return;

                    pBufferVertex->Update(type,
                                          bufSize,
                                          pBuf,
                                          isDelete);
                }

                GLBufferVertexIndex* OpenGLWindow::createBufferVertexIndex(const String& nameBuffer,
                                                                           FMeshVertexType type,
                                                                           size_t bufSize_Vertex, 
                                                                           uint8* pBuf_Vertex,
                                                                           bool isDelete_Vertex,
                                                                           size_t bufSize_Index, 
                                                                           uint8* pBuf_Index,
                                                                           bool isDelete_Index)
                {
                    GLBufferVertexIndex* pBufferVertexIndex = new GLBufferVertexIndex(nameBuffer);
                    if (!pBufferVertexIndex->Init(type,
                                                  bufSize_Vertex, 
                                                  pBuf_Vertex, 
                                                  isDelete_Vertex,
                                                  bufSize_Index,
                                                  pBuf_Index,
                                                  isDelete_Index))
                    {
                        F_LogError("*********************** OpenGLWindow::createBufferVertexIndex: Failed to create buffer vertex index: [%s] !", nameBuffer.c_str());
                        F_DELETE(pBufferVertexIndex)
                        return nullptr;
                    }
                    return pBufferVertexIndex;
                }
                void OpenGLWindow::updateBufferVertexIndex(GLBufferVertexIndex* pBufferVertexIndex,
                                                           FMeshVertexType type,
                                                           size_t bufSize_Vertex, 
                                                           uint8* pBuf_Vertex,
                                                           bool isDelete_Vertex,
                                                           size_t bufSize_Index, 
                                                           uint8* pBuf_Index,
                                                           bool isDelete_Index)
                {
                    if (pBufferVertexIndex == nullptr)
                        return;

                    pBufferVertexIndex->Update(type,  
                                               bufSize_Vertex,
                                               pBuf_Vertex,
                                               isDelete_Vertex,
                                               bufSize_Index,
                                               pBuf_Index,
                                               isDelete_Index);
                }   

                bool OpenGLWindow::createGLBufferVertex(const String& nameBuffer,
                                                        FMeshVertexType type,
                                                        size_t bufSize,
                                                        uint8* pBuf,
                                                        uint32& nVAO,
                                                        uint32& nVBO)
                {
                    glGenVertexArrays(1, &nVAO);
                    glGenBuffers(1, &nVBO);

                    updateGLBufferVertex(type, 
                                         bufSize,
                                         pBuf,
                                         nVAO,
                                         nVBO);

                    this->poDebug->SetGLBufferName(nVBO, "BufferVertex-" + nameBuffer);
                    this->poDebug->SetGLVertexArrayName(nVAO, "VertexArray-" + nameBuffer);
                    return true;
                }
                void OpenGLWindow::updateGLBufferVertex(FMeshVertexType type,
                                                        size_t bufSize,
                                                        uint8* pBuf,
                                                        uint32 nVAO,
                                                        uint32 nVBO)
                {
                    glBindVertexArray(nVAO);

                    glBindBuffer(GL_ARRAY_BUFFER, nVBO);
                    glBufferData(GL_ARRAY_BUFFER, bufSize, pBuf, GL_STATIC_DRAW);

                    Util_CreateAttributeDescriptions(type);

                    glBindBuffer(GL_ARRAY_BUFFER, 0); 
                    glBindVertexArray(0); 
                }
                void OpenGLWindow::destroyGLBufferVertex(uint32 nVAO, uint32 nVBO)
                {
                    if (nVAO > 0)
                    {
                        glDeleteVertexArrays(1, &nVAO);
                    }
                    if (nVBO > 0)
                    {
                        glDeleteBuffers(1, &nVBO);
                    }
                }

                bool OpenGLWindow::createGLBufferVertexIndex(const String& nameBuffer,
                                                             FMeshVertexType type,
                                                             size_t bufSize_Vertex,
                                                             uint8* pBuf_Vertex,
                                                             size_t bufSize_Index,
                                                             uint8* pBuf_Index,
                                                             uint32& nVAO,
                                                             uint32& nVBO,
                                                             uint32& nVEO)
                {
                    glGenVertexArrays(1, &nVAO);
                    glGenBuffers(1, &nVBO);
                    glGenBuffers(1, &nVEO);

                    updateGLBufferVertexIndex(type, 
                                              bufSize_Vertex,
                                              pBuf_Vertex,
                                              bufSize_Index,
                                              pBuf_Index,
                                              nVAO,
                                              nVBO,
                                              nVEO);

                    this->poDebug->SetGLBufferName(nVBO, "BufferVertex-" + nameBuffer);
                    this->poDebug->SetGLBufferName(nVEO, "BufferIndex-" + nameBuffer);
                    this->poDebug->SetGLVertexArrayName(nVAO, "VertexArray-" + nameBuffer);
                    return true;
                }
                void OpenGLWindow::updateGLBufferVertexIndex(FMeshVertexType type,
                                                             size_t bufSize_Vertex,
                                                             uint8* pBuf_Vertex,
                                                             size_t bufSize_Index,
                                                             uint8* pBuf_Index,
                                                             uint32 nVAO,
                                                             uint32 nVBO,
                                                             uint32 nVEO)
                {
                    glBindVertexArray(nVAO);

                    glBindBuffer(GL_ARRAY_BUFFER, nVBO);
                    glBufferData(GL_ARRAY_BUFFER, bufSize_Vertex, pBuf_Vertex, GL_STATIC_DRAW);

                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nVEO);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufSize_Index, pBuf_Index, GL_STATIC_DRAW);

                    Util_CreateAttributeDescriptions(type);

                    glBindBuffer(GL_ARRAY_BUFFER, 0); 
                    glBindVertexArray(0); 
                }       
                void OpenGLWindow::bindGLVertexArray(uint32 nVAO)
                {
                    if (nVAO > 0)
                    {
                        glBindVertexArray(nVAO);
                    }
                }
                void OpenGLWindow::destroyGLBufferVertexIndex(uint32 nVAO, uint32 nVBO, uint32 nVEO)
                {
                    if (nVAO > 0)
                    {
                        glDeleteVertexArrays(1, &nVAO);
                    }
                    if (nVBO > 0)
                    {
                        glDeleteBuffers(1, &nVBO);
                    }
                    if (nVEO > 0)
                    {
                        glDeleteBuffers(1, &nVEO);
                    }
                }

            void OpenGLWindow::loadTexture()
            {
                F_LogInfo("**<2-1-2> OpenGLWindow::loadTexture start **");
                {
                    //1> Texture Default 
                    loadTexture_Default();

                    //2> Texture Custom
                    loadTexture_Custom();
                }
                F_LogInfo("**<2-1-2> OpenGLWindow::loadTexture finish **");
            }
                void OpenGLWindow::loadTexture_Default()
                {
                    if (!this->cfg_texture_Path.empty())
                    {
                        String nameTexture;
                        String pathBase;
                        FUtilString::SplitFileName(this->cfg_texture_Path, nameTexture, pathBase);
                        StringVector aPathTexture;
                        aPathTexture.push_back(this->cfg_texture_Path);
                        this->poTexture = new GLTexture(nameTexture,
                                                        aPathTexture,
                                                        F_Texture_2D,
                                                        F_TexturePixelFormat_R8G8B8A8_SRGB,
                                                        F_TextureAddressing_Wrap,
                                                        F_TextureFilter_Bilinear,
                                                        F_TextureFilter_Bilinear,
                                                        F_MSAASampleCount_1_Bit,
                                                        FColor(0, 0, 0, 1),
                                                        true,
                                                        true,
                                                        false,
                                                        false,
                                                        false);
                        if (!this->poTexture->Init())
                        {
                            F_LogError("*********************** OpenGLWindow::loadTexture_Default: Failed to create texture, name: [%s], path: [%s] !", nameTexture.c_str(), this->cfg_texture_Path.c_str());
                            F_DELETE(this->poTexture)
                            return;
                        }
                        F_LogInfo("<2-1-2-1> OpenGLWindow::loadTexture_Default finish !");
                    }
                }
                void OpenGLWindow::loadTexture_Custom()
                {

                }

                bool OpenGLWindow::createTexture2D(const String& nameTexture,
                                                   const String& pathAsset_Tex,
                                                   uint32_t& mipMapCount, 
                                                   bool isAutoMipmap,
                                                   FTextureType typeTexture, 
                                                   bool isCubeMap,
                                                   FTexturePixelFormatType typePixelFormat,
                                                   FTextureAddressingType typeAddressing,
                                                   FTextureFilterType typeFilterSizeMin,
                                                   FTextureFilterType typeFilterSizeMag,
                                                   FMSAASampleCountType numSamples, 
                                                   const FColor& borderColor,
                                                   bool isUseBorderColor,
                                                   bool isGraphicsComputeShared,
                                                   uint32& nTextureID)
                {
                    //1> Load Texture From File
                    String pathTexture = GetAssetFullPath(pathAsset_Tex);
                    int width, height, texChannels;
                    stbi_uc* pixels = stbi_load(pathTexture.c_str(), &width, &height, &texChannels, 0);
                    int imageSize = width * height * texChannels;
                    mipMapCount = static_cast<uint32_t>(std::floor(std::log2(std::max(width, height)))) + 1;
                    if (!pixels) 
                    {
                        String msg = "*********************** OpenGLWindow::createTexture2D: Failed to load texture image: " + pathAsset_Tex;
                        F_LogError(msg.c_str());
                        throw std::runtime_error(msg);
                    }

                    if (!createGLTexture(nameTexture,
                                         pixels,
                                         texChannels,
                                         width,
                                         height,
                                         0,
                                         1,
                                         mipMapCount,
                                         isAutoMipmap,
                                         typeTexture,
                                         isCubeMap,
                                         typePixelFormat,
                                         typeAddressing,
                                         typeFilterSizeMin,
                                         typeFilterSizeMag,
                                         numSamples,
                                         borderColor,
                                         isUseBorderColor,
                                         isGraphicsComputeShared,
                                         nTextureID))
                    {
                        F_LogError("*********************** OpenGLWindow::createTexture2D: Failed to create texture, name: [%s], path: [%s] !", nameTexture.c_str(), pathAsset_Tex.c_str());
                        stbi_image_free(pixels);
                        return false;
                    }
                    stbi_image_free(pixels);

                    F_LogInfo("OpenGLWindow::createTexture2D: Success to create texture, name: [%s], path: [%s] !", nameTexture.c_str(), pathAsset_Tex.c_str());
                    return true;
                }
                bool OpenGLWindow::createGLTexture(const String& nameTexture,
                                                   uint8* pData,
                                                   int channel,
                                                   uint32_t width, 
                                                   uint32_t height, 
                                                   uint32_t depth, 
                                                   uint32_t numArray,
                                                   uint32_t mipMapCount, 
                                                   bool isAutoMipmap,
                                                   FTextureType typeTexture, 
                                                   bool isCubeMap,
                                                   FTexturePixelFormatType typePixelFormat,
                                                   FTextureAddressingType typeAddressing,
                                                   FTextureFilterType typeFilterSizeMin,
                                                   FTextureFilterType typeFilterSizeMag,
                                                   FMSAASampleCountType numSamples, 
                                                   const FColor& borderColor,
                                                   bool isUseBorderColor,
                                                   bool isGraphicsComputeShared,
                                                   uint32& nTextureID)
                {
                    glGenTextures(1, &nTextureID);
                    
                    //1> Texture Type
                    GLenum type = Util_Transform2GLTextureType(typeTexture);
                    glBindTexture(type, nTextureID);

                    //2> Texture Data
                    GLenum typeFormat = Util_Transform2GLFormat(typePixelFormat);
                    if (typeTexture == F_Texture_1D)
                    {

                    }
                    else if (typeTexture == F_Texture_2D)
                    {
                        GLenum format;
                        if (channel == 1)
                            format = GL_RED;
                        else if (channel == 3)
                            format = GL_RGB;
                        else if (channel == 4)
                            format = GL_RGBA;
                        glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pData);
                    }
                    else if (typeTexture == F_Texture_2DArray)
                    {

                    }
                    else if (typeTexture == F_Texture_3D)
                    {

                    }
                    else if (typeTexture == F_Texture_CubeMap)
                    {

                    }
                    else
                    {
                        String msg = "*********************** OpenGLWindow::createGLTexture: Wrong texture type, Create texture failed, name: [" + nameTexture + "] !";
                        F_LogError(msg.c_str());
                        throw std::runtime_error(msg);
                    }
                    
                    //3> AutoMipMap
                    if (isAutoMipmap)
                    {
                        glGenerateMipmap(type);
                    }

                    //4> Wrapping parameters
                    GLenum typeAddress = Util_Transform2GLSamplerAddressMode(typeAddressing);
                    glTexParameteri(type, GL_TEXTURE_WRAP_S, typeAddress);
                    glTexParameteri(type, GL_TEXTURE_WRAP_T, typeAddress);
                    
                    //5> Filtering parameters
                    GLenum typeFilterMin = Util_Transform2GLFilter(typeFilterSizeMin, F_TextureFilterSize_Min);
                    GLenum typeFilterMag = Util_Transform2GLFilter(typeFilterSizeMin, F_TextureFilterSize_Mag);
                    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, typeFilterMin);
                    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, typeFilterMag);


                    return true;
                }
                void OpenGLWindow::bindGLTexture(FTextureType typeTexture, uint32 nTextureID)
                {
                    GLenum type = Util_Transform2GLTextureType(typeTexture);
                    glBindTexture(type, nTextureID);
                }
                void OpenGLWindow::destroyGLTexture(uint32 nTextureID)
                {
                    if (nTextureID > 0)
                    {
                        glDeleteTextures(1, &nTextureID);
                    }
                }



            void OpenGLWindow::createConstBuffers()
            {

            }
                void OpenGLWindow::createObjectCB()
                {

                }
                    void OpenGLWindow::buildObjectCB()
                    {

                    }
                void OpenGLWindow::createMaterialCB()
                {

                }
                    void OpenGLWindow::buildMaterialCB()
                    {

                    }
                void OpenGLWindow::createInstanceCB()
                {

                }
                    void OpenGLWindow::buildInstanceCB()
                    {

                    }
                void OpenGLWindow::createCustomCB()
                {

                }

            GLShader* OpenGLWindow::createShader(const String& nameShader, const String& pathFile, FShaderType typeShader)
            {
                GLShader* pShader = new GLShader(nameShader);
                if (!pShader->Init(pathFile, 
                                   typeShader))
                {
                    F_LogError("*********************** OpenGLWindow::createShader failed, name: [%s], path: [%s] !", nameShader.c_str(), pathFile.c_str());
                    return nullptr;
                }
                return pShader;
            }
            String OpenGLWindow::getShaderPathRelative(const String& nameShader, ShaderSortType type)
            {
                String pathRelative = "Assets/Shader/";
                if (type == ShaderSort_Common)
                {
                    pathRelative += "Common/";
                } 
                else
                {
                #if F_PLATFORM == F_PLATFORM_MAC
                    pathRelative += "MacOS/";
                #else
                    pathRelative += "Windows/";
                #endif
                }
                pathRelative += nameShader;
                return pathRelative;
            }
            String OpenGLWindow::getShaderPath(const String& nameShader, ShaderSortType type)
            {
                String pathRelative = getShaderPathRelative(nameShader, type);
                return GetAssetFullPath(pathRelative);
            }

            bool OpenGLWindow::createGLShader(const String& nameShader, const String& pathFile, FShaderType typeShader, uint32& nShaderID)
            {
                const String& strTypeShader = F_GetShaderTypeName(typeShader);
                return createGLShader(nameShader, strTypeShader, pathFile, typeShader, nShaderID);
            }
            bool OpenGLWindow::createGLShader(const String& nameShader, const String& strTypeShader, const String& pathFile, FShaderType typeShader, uint32& nShaderID)
            {
                if (pathFile.empty())
                    return false;

                CharVector code;
                if (!FUtil::LoadAssetFileContent(pathFile.c_str(), code, true))
                {
                    F_LogError("*********************** OpenGLWindow::createGLShader failed, path: [%s] !", pathFile.c_str());
                    return false;
                }
                if (code.size() <= 0)
                {
                    return false;
                }
                const char* pCode = code.data();

                GLenum shaderType = Util_Transform2GLShaderType(typeShader);
                nShaderID = glCreateShader(shaderType);

                glShaderSource(nShaderID, 1, &pCode, nullptr);
                glCompileShader(nShaderID);
                if (checkGLShaderCompileErrors(nShaderID, strTypeShader))
                {
                    F_LogError("*********************** OpenGLWindow::createGLShader: Failed to create shader, name: [%s], type: [%s], path: [%s] !", nameShader.c_str(), strTypeShader.c_str(), pathFile.c_str());
                    return false;
                }
                F_LogInfo("OpenGLWindow::createGLShader success, id: [%u], type: [%s], name: [%s], path: [%s] !", nShaderID, strTypeShader.c_str(), nameShader.c_str(), pathFile.c_str());

                this->poDebug->SetGLShaderName(nShaderID, "Shader-" + nameShader);
                return true;
            }
            void OpenGLWindow::destroyGLShader(uint32 nShaderID)
            {
                if (nShaderID > 0)
                {
                    glDeleteShader(nShaderID);
                }
            }

            GLShaderProgram* OpenGLWindow::createShaderProgram(const String& nameShaderProgram,
                                                               GLShader* pShaderVertex,
                                                               GLShader* pShaderTessellationControl,
                                                               GLShader* pShaderTessellationEvaluation,
                                                               GLShader* pShaderGeometry,
                                                               GLShader* pShaderFragment)
            {
                GLShaderProgram* pShaderProgram = new GLShaderProgram(nameShaderProgram);
                if (!pShaderProgram->Init(pShaderVertex, 
                                          pShaderTessellationControl,
                                          pShaderTessellationEvaluation,
                                          pShaderGeometry,
                                          pShaderFragment))
                {
                    F_LogError("*********************** OpenGLWindow::createShaderProgram failed, name: [%s] !", nameShaderProgram.c_str());
                    return nullptr;
                }
                F_LogInfo("OpenGLWindow::createShaderProgram graphic success, id: [%u], name: [%s] !", pShaderProgram->nShaderProgramID, nameShaderProgram.c_str());

                return pShaderProgram;
            }
            GLShaderProgram* OpenGLWindow::createShaderProgram(const String& nameShaderProgram,
                                                               GLShader* pShaderCompute)
            {
                GLShaderProgram* pShaderProgram = new GLShaderProgram(nameShaderProgram);
                if (!pShaderProgram->Init(pShaderCompute))
                {
                    F_LogError("*********************** OpenGLWindow::createShaderProgram failed, name: [%s] !", nameShaderProgram.c_str());
                    return nullptr;
                }
                F_LogInfo("OpenGLWindow::createShaderProgram compute success, id: [%u], name: [%s] !", pShaderProgram->nShaderProgramID, nameShaderProgram.c_str());

                return pShaderProgram;
            }

            uint32 OpenGLWindow::createGLShaderProgram()
            {
                uint32 nShaderComputeID = glCreateProgram();
                if (nShaderComputeID <= 0)
                {
                    F_LogError("*********************** OpenGLWindow::createGLShaderProgram: Failed to create shader program !");
                    return 0;
                }
                return nShaderComputeID;
            }
            bool OpenGLWindow::createGLShaderProgram(const String& nameShaderProgram,
                                                     uint32 nShaderVertexID,
                                                     uint32 nShaderTessellationControlID,
                                                     uint32 nShaderTessellationEvaluationID,
                                                     uint32 nShaderGeometryID,
                                                     uint32 nShaderFragmentID,
                                                     uint32& nShaderProgramID)
            {
                if (nShaderVertexID <= 0 && nShaderFragmentID <= 0)
                    return false;
                nShaderProgramID = createGLShaderProgram();
                if (nShaderProgramID <= 0)
                    return false;

                //Shader Vertex
                if (nShaderVertexID > 0)
                {
                    glAttachShader(nShaderProgramID, nShaderVertexID);
                }
                //Shader Tessellation Control
                if (nShaderTessellationControlID > 0)
                {
                    glAttachShader(nShaderProgramID, nShaderTessellationControlID);
                }
                //Shader Tessellation Evaluation
                if (nShaderTessellationEvaluationID > 0)
                {
                    glAttachShader(nShaderProgramID, nShaderTessellationEvaluationID);
                }
                //Shader Geometry
                if (nShaderGeometryID > 0)
                {
                    glAttachShader(nShaderProgramID, nShaderGeometryID);
                }
                //Shader Fragment
                if (nShaderFragmentID > 0)
                {
                    glAttachShader(nShaderProgramID, nShaderFragmentID);
                }

                glLinkProgram(nShaderProgramID);
                if (checkGLShaderCompileErrors(nShaderProgramID, c_strShaderProgram))
                {
                    return false;
                }

                this->poDebug->SetGLShaderProgramName(nShaderProgramID, "ShaderProgram-" + nameShaderProgram);
                return true;
            }
            bool OpenGLWindow::createGLShaderProgram(const String& nameShaderProgram,
                                                     uint32 nShaderComputeID,
                                                     uint32& nShaderProgramID)
            {
                if (nShaderComputeID <= 0)
                    return false;
                nShaderProgramID = createGLShaderProgram();
                if (nShaderProgramID <= 0)
                    return false;

                //Shader Compute
                if (nShaderComputeID > 0)
                {
                    glAttachShader(nShaderProgramID, nShaderComputeID);
                }

                glLinkProgram(nShaderProgramID);
                if (checkGLShaderCompileErrors(nShaderProgramID, c_strShaderProgram))
                {
                    return false;
                }

                this->poDebug->SetGLShaderProgramName(nShaderProgramID, "ShaderProgram-" + nameShaderProgram);
                return true;
            }
            void OpenGLWindow::bindGLShaderProgram(uint32 nShaderProgramID)
            {
                if (nShaderProgramID > 0)
                {
                    glUseProgram(nShaderProgramID); 
                }
            }   
            void OpenGLWindow::destroyGLShaderProgram(uint32 nShaderProgramID)
            {
                if (nShaderProgramID > 0)
                {
                    glDeleteProgram(nShaderProgramID);
                }
            }
            bool OpenGLWindow::checkGLShaderCompileErrors(uint32 nShader, const String& type)
            {
                int32 nSuccess;
                char infoLog[1024];
                if (type != c_strShaderProgram)
                {
                    glGetShaderiv(nShader, GL_COMPILE_STATUS, &nSuccess);
                    if (!nSuccess)
                    {
                        glGetShaderInfoLog(nShader, 1024, NULL, infoLog);
                        F_LogError("*********************** OpenGLWindow::checkGLShaderCompileErrors: Failed to compile shader type: [%s], error: [%s] !", type.c_str(), infoLog);
                        return true;
                    }
                }
                else
                {
                    glGetProgramiv(nShader, GL_LINK_STATUS, &nSuccess);
                    if (!nSuccess)
                    {
                        glGetProgramInfoLog(nShader, 1024, NULL, infoLog);
                        F_LogError("*********************** OpenGLWindow::checkGLShaderCompileErrors: Failed to compile shader type: [%s], error: [%s] !", type.c_str(), infoLog);
                        return true;
                    }
                }
                return false;
            }   
            

            void OpenGLWindow::createCustomBeforePipeline()
            {
                F_LogInfo("**<2-1-4> OpenGLWindow::createCustomBeforePipeline finish **");
            }
            void OpenGLWindow::createGraphicsPipeline()
            {
                F_LogInfo("**<2-1-5> OpenGLWindow::createGraphicsPipeline start **");
                {
                    //1> createGraphicsPipeline_Default
                    createGraphicsPipeline_Default();
                    F_LogInfo("<2-1-5-1> OpenGLWindow::createGraphicsPipeline: createGraphicsPipeline_Default finish !");

                    //2> createGraphicsPipeline_Custom
                    createGraphicsPipeline_Custom();
                    F_LogInfo("<2-1-5-2> OpenGLWindow::createGraphicsPipeline: createGraphicsPipeline_Custom finish !");
                }
                F_LogInfo("**<2-1-5> OpenGLWindow::createGraphicsPipeline finish **");
            }
                void OpenGLWindow::createGraphicsPipeline_Default()
                {
                    if (this->cfg_shaderVertex_Path.empty() ||
                        this->cfg_shaderFragment_Path.empty())
                    {
                        return;
                    }

                    //1> Shader
                    String nameVertexShader;
                    String namePathBase;
                    FUtilString::SplitFileName(this->cfg_shaderVertex_Path, nameVertexShader, namePathBase);
                    this->poShaderVertex = createShader(nameVertexShader, this->cfg_shaderVertex_Path, F_Shader_Vertex);
                    if (this->poShaderVertex == nullptr)
                    {
                        String msg = "*********************** OpenGLWindow::createGraphicsPipeline_Default: Failed to create shader vertex: " + this->cfg_shaderVertex_Path;
                        F_LogError(msg.c_str());
                        throw std::runtime_error(msg);
                    }
                    
                    String nameFragmentShader;
                    FUtilString::SplitFileName(this->cfg_shaderFragment_Path, nameFragmentShader, namePathBase);
                    this->poShaderFragment = createShader(nameFragmentShader, this->cfg_shaderFragment_Path, F_Shader_Fragment);
                    if (this->poShaderFragment == nullptr)
                    {
                        String msg = "*********************** OpenGLWindow::createGraphicsPipeline_Default: Failed to create shader fragment: " + this->cfg_shaderFragment_Path;
                        F_LogError(msg.c_str());
                        throw std::runtime_error(msg);
                    }

                    //2> Shader Program
                    String nameShaderProgram = "ShaderProgram-Default";
                    this->poShaderProgram = createShaderProgram(nameShaderProgram,
                                                                this->poShaderVertex,
                                                                nullptr,
                                                                nullptr,
                                                                nullptr,
                                                                this->poShaderFragment);
                    if (this->poShaderProgram == nullptr)
                    {
                        String msg = "*********************** OpenGLWindow::createGraphicsPipeline_Default: Failed to create shader program: " + nameShaderProgram;
                        F_LogError(msg.c_str());
                        throw std::runtime_error(msg);
                    }

                }
                void OpenGLWindow::createGraphicsPipeline_Custom()
                {

                }

            void OpenGLWindow::createComputePipeline()
            {
                F_LogInfo("**<2-1-6> OpenGLWindow::createComputePipeline start **");
                {
                    //1> createComputePipeline_Default
                    createComputePipeline_Default();

                    //2> createComputePipeline_Custom
                    createComputePipeline_Custom();
                }
                F_LogInfo("**<2-1-6> OpenGLWindow::createComputePipeline finish **");
            }
                void OpenGLWindow::createComputePipeline_Default()
                {

                }
                void OpenGLWindow::createComputePipeline_Custom()
                {

                }


        void OpenGLWindow::createImgui()
        {
            F_LogInfo("**********<2-2> OpenGLWindow::createImgui start **********");
            {
                //1> createImgui_DescriptorPool
                //createImgui_DescriptorPool();
                
                //2> createImgui_Init
                createImgui_Init();
            }
            F_LogInfo("**********<2-2> OpenGLWindow::createImgui finish **********");
        }
            void OpenGLWindow::createImgui_Init()
            {
                //1> Config
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                this->imgui_PathIni = this->pathBin + "Log/" + this->nameTitle + ".ini";
                this->imgui_PathLog = this->pathBin + "Log/" + this->nameTitle + ".log";
                io.IniFilename = this->imgui_PathIni.c_str();
                io.LogFilename = this->imgui_PathLog.c_str();

                //2> Setup Dear ImGui style
                ImGui::StyleColorsDark();
                //ImGui::StyleColorsClassic();

                //3> Init OpenGL
                ImGui_ImplGlfw_InitForOpenGL(this->pWindow, true);
                ImGui_ImplOpenGL3_Init(this->versionGLSL);


                F_LogInfo("<2-2-1> OpenGLWindow::createImgui_Init finish !");
            }


        void OpenGLWindow::createEditor()
        {

        }
            void OpenGLWindow::createEditor_Grid()
            {

            }
            void OpenGLWindow::createEditor_CameraAxis()
            {

            }
            void OpenGLWindow::createEditor_CoordinateAxis()    
            {

            }
            void OpenGLWindow::createEditor_LineFlat2DCollector()
            {

            }
            void OpenGLWindow::createEditor_LineFlat3DCollector()
            {

            }
        void OpenGLWindow::destroyEditor()
        {

        }


    void OpenGLWindow::resizeWindow(int w, int h, bool force)
    {
        if (this->width == w &&
            this->height == h &&
            !force)
        {
            return;
        }
        this->width = w;
        this->height = h;
        RefreshAspectRatio();
    }

    bool OpenGLWindow::beginRender()
    {
        return true;
    }
        void OpenGLWindow::updateRender()
        {
            //1> updateCBs_Default
            updateCBs_Default();

            //2> updateCBs_Terrain
            updateCBs_Terrain();

            //3> updateCBs_ImGUI
            updateCBs_ImGUI();

            //4> updateCBs_Editor
            updateCBs_Editor();

            //5> CB Custom
            updateCBs_Custom();

            //6> CommandBuffers
            updateRenderCommandBuffers_CustomBeforeDefault();
            {
                updateRenderCommandBuffers_Default();
            }
            updateRenderCommandBuffers_CustomAfterDefault();
        }
            void OpenGLWindow::updateCBs_Default()
            {

            }
                void OpenGLWindow::updateCBs_Pass()
                {

                }
                    void OpenGLWindow::updateCBs_PassTransformAndCamera(PassConstants& pass, FCamera* pCam, int nIndex)
                    {

                    }
                void OpenGLWindow::updateCBs_Objects()
                {

                }
                    void OpenGLWindow::updateCBs_ObjectsContent()
                    {

                    }
                void OpenGLWindow::updateCBs_Materials()    
                {

                }
                    void OpenGLWindow::updateCBs_MaterialsContent()
                    {

                    }
                void OpenGLWindow::updateCBs_Instances()
                {

                }
                    void OpenGLWindow::updateCBs_InstancesContent()
                    {

                    }
                void OpenGLWindow::updateCBs_Terrain()
                {

                }
                void OpenGLWindow::updateCBs_ImGUI()
                {
                    if (IsEnable_Imgui())
                    {
                        if (beginRenderImgui())
                        {
                            endRenderImgui();
                        }
                    }
                }
                    bool OpenGLWindow::beginRenderImgui()
                    {   

                        return false;
                    }
                        void OpenGLWindow::commonConfig()
                        {
                            ImGui::Text("Frametime: %f", this->fFPS);

                            ImGui::Separator();
                            commonShowConfig();

                            ImGui::Separator();
                            commonEditorConfig();
                        }
                            void OpenGLWindow::commonShowConfig()
                            {
                                if (ImGui::CollapsingHeader("Common Show"))
                                {
                                    ImGui::Text("Op ResetCamera -- Key R");
                                    ImGui::Text("Op WireFrame -- Key F");
                                    ImGui::Text("Op Rotate -- Key T");

                                    ImGui::Separator();
                                    ImGui::Text("Viewport Offset: [%d, %d]",
                                                this->poViewport.left,
                                                this->poViewport.top);
                                    ImGui::Text("Viewport Size: [%d, %d]",
                                                this->poViewport.right,
                                                this->poViewport.bottom);
                                    ImGui::Text("Framebuffer Size: [%f, %f]",
                                                this->poFramebufferSize.x,
                                                this->poFramebufferSize.y);
                                    ImGui::Text("Glfw WindowContent Scale: [%f, %f]",
                                                this->poWindowContentScale.x,
                                                this->poWindowContentScale.y);

                                    ImGui::Separator();
                                    ImGui::Text("Mouse Screen XY: [%f, %f]", 
                                                this->mousePosLast.x,
                                                this->mousePosLast.y);
                                    if (this->poViewport.right > 0 && this->poViewport.bottom > 0)
                                    ImGui::Text("Mouse Viewport XY: [%f, %f]", 
                                                this->mousePosLast.x / this->poViewport.right,
                                                this->mousePosLast.y / this->poViewport.bottom);
                                    ImGui::Text("Mouse NDC XY: [%f, %f]", 
                                                (float)((this->mousePosLast.x - this->poViewport.left) * 2.0f / this->poViewport.right - 1.0f),
                                                (float)(1.0f - (this->mousePosLast.y - this->poViewport.top) * 2.0f / this->poViewport.bottom));
                                    ImGui::Text("Mouse LeftDown: [%s]", 
                                                this->mouseButtonDownLeft ? "true" : "false");
                                    ImGui::Text("Mouse RightDown: [%s]", 
                                                this->mouseButtonDownRight ? "true" : "false");
                                    ImGui::Text("Mouse MiddleDown: [%s]", 
                                                this->mouseButtonDownMiddle ? "true" : "false");

                                    ImGui::Separator();

                                }
                            }
                            void OpenGLWindow::commonEditorConfig()
                            {
                                ImGui::Checkbox("Is WireFrame", &cfg_isWireFrame);
                                ImGui::Checkbox("Is Rotate", &cfg_isRotate);
                                ImGui::Separator();
                                if (ImGui::CollapsingHeader("EditorGrid Settings"))
                                {
                                    ImGui::Checkbox("Is EditorGridShow", &cfg_isEditorGridShow);
                                    if (this->pEditorGrid != nullptr)
                                    {
                                        if (ImGui::ColorEdit4("EditorGrid Color", (float*)&this->cfg_editorGrid_Color))
                                        {
                                            //this->pEditorGrid->SetColor(this->cfg_editorGrid_Color);
                                        }
                                    }
                                }
                                if (ImGui::CollapsingHeader("EditorCameraAxis Settings"))
                                {
                                    ImGui::Checkbox("Is EditorCameraAxisShow", &cfg_isEditorCameraAxisShow);

                                }
                            }
                        void OpenGLWindow::cameraConfig()
                        {

                        }
                            void OpenGLWindow::cameraReset()
                            {

                            }
                        void OpenGLWindow::lightConfig()
                        {

                        }
                            void OpenGLWindow::lightConfigItem(LightConstants& lc, const String& name, int index, bool canChangeType, bool bIsMainLight)
                            {

                            }
                            void OpenGLWindow::lightMainReset()
                            {

                            }
                        void OpenGLWindow::shadowConfig()
                        {

                        }
                            void OpenGLWindow::shadowConfigItem(ShadowConstants& sc, const String& name, bool bIsMainLight)
                            {

                            }
                            void OpenGLWindow::shadowReset()
                            {

                            }
                        void OpenGLWindow::cullConfig()
                        {

                        }
                        void OpenGLWindow::terrainConfig()
                        {

                        }
                            void OpenGLWindow::terrainConfigItem(TerrainConstants& tc, const String& name)
                            {

                            }
                                bool OpenGLWindow::terrainConfigSplatItem(TerrainSplatConstants& tsc, const String& name)
                                {
                                    return true;
                                }
                            void OpenGLWindow::terrainReset()
                            {

                            }
                        void OpenGLWindow::passConstantsConfig()
                        {

                        }
                        void OpenGLWindow::modelConfig()
                        {

                        }
                void OpenGLWindow::endRenderImgui()
                {
                    ImGui::Render();
                }
            void OpenGLWindow::updateCBs_Editor()
            {

            }
            void OpenGLWindow::updateCBs_Custom()
            {

            }

            void OpenGLWindow::updateRenderCommandBuffers_CustomBeforeDefault()
            {

            }
            void OpenGLWindow::updateRenderCommandBuffers_Default()
            {

                {
                    updateRenderPass_CustomBeforeDefault();
                    {
                        updateRenderPass_Default();
                    }
                    updateRenderPass_CustomAfterDefault();
                }

            }
                void OpenGLWindow::updateRenderPass_CustomBeforeDefault()
                {

                }
                void OpenGLWindow::updateRenderPass_Default()
                {
                    updateMeshDefault_Before();
                    {
                        beginRenderPass("[RenderPass-Default]",
                                        this->poOffset,
                                        this->poExtent,
                                        this->cfg_colorBackground,
                                        1.0f,
                                        0);
                        {
                            //1> Viewport
                            

                            //2> Default
                            drawMeshDefault();
                            drawMeshTerrain();
                            drawMeshDefault_Custom();
                            drawMeshDefault_Editor();
                            drawMeshDefault_CustomBeforeImgui();

                            //3> ImGui 
                            drawMeshDefault_Imgui();
                        }
                        endRenderPass();
                    }
                    updateMeshDefault_After();
                }
                    void OpenGLWindow::updateMeshDefault_Before()
                    {

                    }
                        void OpenGLWindow::drawMeshDefault()
                        {
                            if (this->poShaderProgram == nullptr)
                                return;

                            if (this->poTexture != nullptr)
                                this->poTexture->BindTexture();
                            this->poShaderProgram->BindProgram();
                            Util_EnableAttributeDescriptions(this->poTypeVertex, true);
                            if (this->pBufferVertex != nullptr)
                            {
                                this->pBufferVertex->BindVertexArray();
                                draw(this->cfg_glPrimitiveTopology, 0, this->poVertexCount);
                            }
                            else if (this->pBufferVertexIndex != nullptr)
                            {   
                                this->pBufferVertexIndex->BindVertexArray();
                                drawIndexed(this->cfg_glPrimitiveTopology, this->poVertexCount, GL_UNSIGNED_INT, 0);
                            }
                        }
                        void OpenGLWindow::drawMeshTerrain()
                        {

                        }
                        void OpenGLWindow::drawMeshDefault_Custom()
                        {

                        }
                        void OpenGLWindow::drawMeshDefault_Editor()
                        {

                        }
                        void OpenGLWindow::drawMeshDefault_CustomBeforeImgui()
                        {

                        }
                        void OpenGLWindow::drawMeshDefault_Imgui()
                        {
                            if (HasConfig_Imgui())
                            {
                                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                            }
                        }
                    void OpenGLWindow::updateMeshDefault_After()
                    {

                    }
                void OpenGLWindow::updateRenderPass_CustomAfterDefault()
                {

                }



                void OpenGLWindow::beginRenderPass(const String& nameRenderPass,
                                                   const FSizeI& offset,
                                                   const FSizeI& extent,
                                                   const FVector4& clBg,
                                                   float depth,
                                                   uint32_t stencil)
                {
                    this->poDebug->BeginRegion(nameRenderPass.c_str(), GL_DEBUG_SOURCE_APPLICATION);

                    glClearColor(clBg.x, clBg.y, clBg.z, clBg.w);
                    glClear(GL_COLOR_BUFFER_BIT);
                    glEnable(GL_FRAMEBUFFER_SRGB);
                }

                    void OpenGLWindow::draw(GLenum mode, GLint first, GLsizei count)
                    {
                        glDrawArrays(mode, first, count);
                    }
                    void OpenGLWindow::drawIndexed(GLenum mode, GLsizei count, GLenum type, const void* indices)
                    {
                        glDrawElements(mode, count, type, indices);
                    }

                void OpenGLWindow::endRenderPass()
                {

                    this->poDebug->EndRegion();
                }


            void OpenGLWindow::updateRenderCommandBuffers_CustomAfterDefault()
            {

            }


        void OpenGLWindow::render()
        {

        }
    void OpenGLWindow::endRender()
    {

    }

    void OpenGLWindow::cleanup()
    {
        F_LogInfo("---------- OpenGLWindow::cleanup start ----------");
        {
            //0> cleanupSwapChain
            cleanupSwapChain();

            //1> cleanupCustom/cleanupEditor/cleanupImGUI/cleanupDefault/cleanupInternal
            cleanupCustom();
            cleanupEditor();
            cleanupImGUI();
            cleanupDefault();
            //cleanupInternal();


        }
        F_LogInfo("---------- OpenGLWindow::cleanup finish ----------");
    }
        void OpenGLWindow::cleanupDefault()
        {
            
            cleanupTexture();
            cleanupVertexIndexBuffer();
        }
            void OpenGLWindow::cleanupTexture()
            {
                F_DELETE(this->poTexture)
            }
            void OpenGLWindow::cleanupVertexIndexBuffer()
            {
                //1> VertexBuffer/pBufferVertexIndex
                F_DELETE(this->pBufferVertex)
                F_DELETE(this->pBufferVertexIndex)

                //2> Data
                this->poVertexCount = 0;
                this->poVertexBuffer_Size = 0;
                this->poVertexBuffer_Data = nullptr;
                this->poIndexCount = 0;
                this->poIndexBuffer_Size = 0;
                this->poIndexBuffer_Data = nullptr;
            }
        void OpenGLWindow::cleanupImGUI()
        {
            if (HasConfig_Imgui())
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();
            }
        }
        void OpenGLWindow::cleanupEditor()
        {
            destroyEditor();
        }
        void OpenGLWindow::cleanupCustom()
        {

        }

        void OpenGLWindow::cleanupSwapChain()
        {
            F_LogInfo("----- OpenGLWindow::cleanupSwapChain start -----");
            {
                //0> Custom/Editor/Terrain/Default
                cleanupSwapChain_Custom();
                cleanupSwapChain_Editor();
                cleanupSwapChain_Default();

                //1> DepthImage/ColorImage    

                //2> SwapChainFrameBuffers

                //3> CommandBuffers



            }
            F_LogInfo("----- OpenGLWindow::cleanupSwapChain finish -----");
        }
            void OpenGLWindow::cleanupSwapChain_Default()
            {
                size_t count = 0;

                //1> ConstBuffers

                //2> Pipelines
                F_DELETE(this->poShaderProgram)
                F_DELETE(this->poShaderVertex)
                F_DELETE(this->poShaderFragment)

            }
            void OpenGLWindow::cleanupSwapChain_Editor()
            {

            }
            void OpenGLWindow::cleanupSwapChain_Custom()
            {

            }
        void OpenGLWindow::recreateSwapChain()
        {
            F_LogInfo("++++++++++ OpenGLWindow::recreateSwapChain start ++++++++++");
            {

            }
            F_LogInfo("++++++++++ OpenGLWindow::recreateSwapChain finish ++++++++++");
        }
            void OpenGLWindow::recreateSwapChain_Editor()
            {

            }
            void OpenGLWindow::recreateSwapChain_Custom()
            {

            }

}; //LostPeterOpenGL