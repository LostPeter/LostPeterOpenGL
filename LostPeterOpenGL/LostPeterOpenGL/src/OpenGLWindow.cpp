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


        , poVertexCount(0)
        , poVertexBuffer_Size(0)
        , poVertexBuffer_Data(nullptr)
        , poIndexCount(0)
        , poIndexBuffer_Size(0)
        , poIndexBuffer_Data(nullptr)
        , pBufferVertex(nullptr)
        , pBufferVertexIndex(nullptr)

        , typeVertex(F_MeshVertex_Pos3Color4Normal3Tangent3Tex2)


        , isFrameBufferResized(false)


        , cfg_colorBackground(0.0f, 0.2f, 0.4f, 1.0f)


        , cfg_isMSAA(false)
        , cfg_isImgui(false)
        , cfg_isWireFrame(false)

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
            glfwSetFramebufferSizeCallback(this->pWindow, framebuffer_size_callback);

            //2> glad load all OpenGL function pointers 
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "OpenGLWindow::createDevice: gladLoadGLLoader failed !" << std::endl;
                glfwTerminate();
                return;
            }
        }
        F_LogInfo("*****<1-2> OpenGLWindow::createDevice finish *****");
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

        }
            void OpenGLWindow::createViewport()
            {

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
                                                                           this->typeVertex,
                                                                           this->poVertexBuffer_Size,
                                                                           this->poVertexBuffer_Data,
                                                                           false,
                                                                           this->poIndexBuffer_Size,
                                                                           this->poIndexBuffer_Data,
                                                                           false);
                    }

                    //3> createBufferVertex
                    if (this->poVertexBuffer_Size > 0 &&
                        this->poVertexBuffer_Data != nullptr)
                    {
                        this->pBufferVertex = createBufferVertex("Vertex-" + this->nameTitle,
                                                                 this->typeVertex,
                                                                 this->poVertexBuffer_Size, 
                                                                 this->poVertexBuffer_Data, 
                                                                 false);
                    }
                }
                F_LogInfo("**<2-1-1> OpenGLWindow::loadVertexIndexBuffer finish **");
            }
                void OpenGLWindow::loadModel()
                {

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

                bool OpenGLWindow::createGLBufferVertex(FMeshVertexType type,
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

                bool OpenGLWindow::createGLBufferVertexIndex(FMeshVertexType type,
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

            }
                void OpenGLWindow::loadTexture_Default()
                {

                }
                void OpenGLWindow::loadTexture_Custom()
                {

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

            GLShader* OpenGLWindow::createShader()
            {
                
                return nullptr;
            }

            bool OpenGLWindow::createGLShader(const String& nameShader, FShaderType typeShader, const String& pathFile, uint32& nShaderID)
            {
                const String& strTypeShader = F_GetShaderTypeName(typeShader);
                return createGLShader(nameShader, typeShader, strTypeShader, pathFile, nShaderID);
            }
            bool OpenGLWindow::createGLShader(const String& nameShader, FShaderType typeShader, const String& strTypeShader, const String& pathFile, uint32& nShaderID)
            {
                GLenum shaderType = Util_Transform2GLShaderType(typeShader);
                nShaderID = glCreateShader(shaderType);

                
                return true;
            }
            void OpenGLWindow::destroyGLShader(uint32 nShaderID)
            {
                if (nShaderID > 0)
                {
                    glDeleteShader(nShaderID);
                }
            }

            bool OpenGLWindow::createGLShaderProgram(uint32 nShaderVertexID,
                                                     uint32 nShaderTessellationControlID,
                                                     uint32 nShaderTessellationEvaluationID,
                                                     uint32 nShaderGeometryID,
                                                     uint32 nShaderFragmentID)
            {
                
                return true;
            }
            bool OpenGLWindow::createGLShaderProgram(uint32 nShaderComputeID)
            {
                

                return true;
            }
            void OpenGLWindow::destroyGLShaderProgram(uint32 nShaderProgramID)
            {
                if (nShaderProgramID > 0)
                {
                    glDeleteProgram(nShaderProgramID);
                }
            }
            

    void OpenGLWindow::resizeWindow(int w, int h, bool force)
    {

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

                }
                    bool OpenGLWindow::beginRenderImgui()
                    {   
                        return true;
                    }
                        void OpenGLWindow::commonConfig()
                        {

                        }
                            void OpenGLWindow::commonShowConfig()
                            {

                            }
                            void OpenGLWindow::commonEditorConfig()
                            {

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
                    
                    glClearColor(clBg.x, clBg.y, clBg.z, clBg.w);
                    glClear(GL_COLOR_BUFFER_BIT);
                }



                void OpenGLWindow::endRenderPass()
                {

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

        }
        void OpenGLWindow::cleanupEditor()
        {

        }
        void OpenGLWindow::cleanupCustom()
        {

        }

        void OpenGLWindow::cleanupSwapChain()
        {
            F_LogInfo("----- OpenGLWindow::cleanupSwapChain start -----");
            {

            }
            F_LogInfo("----- OpenGLWindow::cleanupSwapChain finish -----");
        }
            void OpenGLWindow::cleanupSwapChain_Default()
            {

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