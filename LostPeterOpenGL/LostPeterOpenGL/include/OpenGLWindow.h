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
        static const String c_strShaderProgram;

    public:

        GLDebug* poDebug;

        FSizeI poOffset;
        FSizeI poExtent;
        FRectI poScissor;


        FVector2 poFramebufferSize;
        FVector2 poWindowContentScale;


        uint32_t poVertexCount;
        size_t poVertexBuffer_Size;
        uint8* poVertexBuffer_Data;
        uint32_t poIndexCount;
        size_t poIndexBuffer_Size;
        uint8* poIndexBuffer_Data;
        GLBufferVertex* pBufferVertex;
        GLBufferVertexIndex* pBufferVertexIndex;
        FMatrix4 poMatWorld;

        FMeshVertexType poTypeVertex;
        GLShader* poShaderVertex;
        GLShader* poShaderFragment;
        GLShaderProgram* poShaderProgram;

        GLTexture* poTexture;

        bool isFrameBufferResized;

        //Config
        FVector4 cfg_colorBackground;
        FVector4Vector cfg_colorValues;


        bool cfg_isMSAA;
        bool cfg_isImgui;
        bool cfg_isWireFrame;
        
        GLenum cfg_glPrimitiveTopology;
        


        FVector3 cfg_cameraPos;
        FVector3 cfg_cameraLookTarget;
        FVector3 cfg_cameraUp;

        float cfg_cameraFov;
        float cfg_cameraNear;
        float cfg_cameraFar;

        float cfg_cameraSpeedMove;
        float cfg_cameraSpeedZoom;
        float cfg_cameraSpeedRotate;

        //Custom
        String cfg_model_Path;
        String cfg_shaderVertex_Path;
        String cfg_shaderFragment_Path;
        String cfg_texture_Path;
        String cfg_terrain_Path;
        String cfg_terrainTextureDiffuse_Path;
        String cfg_terrainTextureNormal_Path;
        String cfg_terrainTextureControl_Path;
        float cfg_terrainHeightStart;
        float cfg_terrainHeightMax;
        
        //Imgui
        bool imgui_IsEnable;
        int	imgui_MinimalSwapchainImages;
        String imgui_PathIni;
        String imgui_PathLog;

        //Camera
        FCamera* pCamera; //Eye Left
        FCamera* pCameraRight; //Eye Right

        //Light

        //Shadow
        FCamera* pCameraMainLight; //mainLight's shadow camera

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

        virtual bool OnBeginCompute_BeforeRender();
            virtual void OnUpdateCompute_BeforeRender();
            virtual void OnCompute_BeforeRender();
        virtual void OnEndCompute_BeforeRender();

        virtual bool OnBeginRender();
            virtual void OnUpdateRender();
            virtual void OnRender();
        virtual void OnEndRender();

        virtual bool OnBeginCompute_AfterRender();
            virtual void OnUpdateCompute_AfterRender();
            virtual void OnCompute_AfterRender();
        virtual void OnEndCompute_AfterRender();

        virtual void OnPresent();
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
        virtual bool HasConfig_MASS();
        virtual bool HasConfig_Imgui();

        virtual bool IsEnable_MASS();
        virtual bool IsEnable_Imgui();

    public:


    public:
        //Create Pipeline
        virtual void createPipeline();
            virtual void createWindowCallback();
            virtual void createDevice();
                virtual void setUpDebugMessenger();


            virtual void createFeatureSupport();

            //Camera/Light
            virtual void createCamera();
            virtual void createLightMain();
            virtual void createShadowLightMain();
            virtual void createTerrain();

            virtual void createCommandObjects();

            virtual void createSwapChainObjects();
                virtual void createSwapChain();
                    virtual void createViewport();
                virtual void createSwapChainImageViews();
                    virtual void createColorResources();
                    virtual void createDepthResources();
                virtual void createColorResourceLists();

            virtual void createPipelineObjects();
                virtual void createRenderPasses();
                    virtual void createRenderPass_ShadowMap();
                    virtual void createRenderPass_Default();
                    virtual void createRenderPass_Cull();
                    virtual void createRenderPass_Terrain();
                    virtual void createRenderPass_Custom();
                        virtual GLRenderPass* createRenderPass_DefaultCustom();
                        virtual GLRenderPass* createRenderPass_KhrDepth(int formatSwapChain, int formatDepth);
                        virtual GLRenderPass* createRenderPass_KhrDepthImgui(int formatColor, int formatDepth, int formatSwapChain);
                        virtual GLRenderPass* createRenderPass_ColorDepthMSAA(int formatColor, int formatDepth, int formatSwapChain, int samples);
                        virtual GLRenderPass* createRenderPass_ColorDepthImguiMSAA(int formatColor, int formatDepth, int formatSwapChain, int samples);



                virtual void createFramebuffers();
                    virtual void createFramebuffer_Default();
                    virtual void createFramebuffer_Custom();
                        virtual void createFramebuffer_DefaultCustom();


                    virtual GLFrameBuffer* createGLFrameBuffer(const String& nameFrameBuffer,
                                                               uint32_t width,
                                                               uint32_t height,
                                                               uint32_t layers);
                    virtual uint32 createGLFrameBuffer();
                    virtual void bindGLFrameBuffer(GLFrameBuffer* pGLFrameBuffer);
                    virtual void bindGLFrameBuffer(uint32 nGLFrameBuffer);
                    virtual void destroyGLFrameBuffer(GLFrameBuffer* pGLFrameBuffer);
                    virtual void destroyGLFrameBuffer(uint32 nGLFrameBuffer);


        //Load Assets
        virtual void loadAssets();

            //Geometry
            virtual void loadGeometry();
                virtual void loadVertexIndexBuffer();
                    virtual void loadModel();
                        virtual void loadModel_Default();
                        virtual void loadModel_Custom();
                    virtual GLBufferVertex* createBufferVertex(const String& nameBuffer,
                                                               FMeshVertexType type,
                                                               size_t bufSize, 
                                                               uint8* pBuf,
                                                               bool isDelete);
                    virtual void updateBufferVertex(GLBufferVertex* pBufferVertex,
                                                    FMeshVertexType type,
                                                    size_t bufSize, 
                                                    uint8* pBuf,
                                                    bool isDelete);

                    virtual GLBufferVertexIndex* createBufferVertexIndex(const String& nameBuffer,
                                                                         FMeshVertexType type,
                                                                         size_t bufSize_Vertex, 
                                                                         uint8* pBuf_Vertex,
                                                                         bool isDelete_Vertex,
                                                                         size_t bufSize_Index, 
                                                                         uint8* pBuf_Index,
                                                                         bool isDelete_Index);
                    virtual void updateBufferVertexIndex(GLBufferVertexIndex* pBufferVertexIndex,
                                                         FMeshVertexType type,
                                                         size_t bufSize_Vertex, 
                                                         uint8* pBuf_Vertex,
                                                         bool isDelete_Vertex,
                                                         size_t bufSize_Index, 
                                                         uint8* pBuf_Index,
                                                         bool isDelete_Index);

                    virtual bool createGLBufferVertex(const String& nameBuffer,
                                                      FMeshVertexType type,
                                                      size_t bufSize,
                                                      uint8* pBuf,
                                                      uint32& nVAO,
                                                      uint32& nVBO);
                    virtual void updateGLBufferVertex(FMeshVertexType type,
                                                      size_t bufSize,
                                                      uint8* pBuf,
                                                      uint32 nVAO,
                                                      uint32 nVBO);
                    virtual void destroyGLBufferVertex(uint32 nVAO, uint32 nVBO);

                    virtual bool createGLBufferVertexIndex(const String& nameBuffer,
                                                           FMeshVertexType type,
                                                           size_t bufSize_Vertex,
                                                           uint8* pBuf_Vertex,
                                                           size_t bufSize_Index,
                                                           uint8* pBuf_Index,
                                                           uint32& nVAO,
                                                           uint32& nVBO,
                                                           uint32& nVEO);
                    virtual void updateGLBufferVertexIndex(FMeshVertexType type,
                                                           size_t bufSize_Vertex,
                                                           uint8* pBuf_Vertex,
                                                           size_t bufSize_Index,
                                                           uint8* pBuf_Index,
                                                           uint32 nVAO,
                                                           uint32 nVBO,
                                                           uint32 nVEO);
                    virtual void bindGLVertexArray(uint32 nVAO);
                    virtual void destroyGLBufferVertexIndex(uint32 nVAO, uint32 nVBO, uint32 nVEO);


                virtual void loadTexture();
                    virtual void loadTexture_Default();
                    virtual void loadTexture_Custom();


                    virtual bool createTexture2D(const String& nameTexture,
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
                                                 uint32& nTextureID);

                    virtual bool createGLTexture(const String& nameTexture,
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
                                                 uint32& nTextureID);
                    virtual void bindGLTexture(FTextureType typeTexture, uint32 nTextureID);
                    virtual void destroyGLTexture(uint32 nTextureID);


                virtual void createConstBuffers();
                    virtual void createObjectCB();
                        virtual void buildObjectCB();
                    virtual void createMaterialCB();
                        virtual void buildMaterialCB();
                    virtual void createInstanceCB();
                        virtual void buildInstanceCB();
                    virtual void createCustomCB();

                virtual GLShader* createShader(const String& nameShader, const String& pathFile, FShaderType typeShader);
                virtual String getShaderPathRelative(const String& nameShader, ShaderSortType type);
                virtual String getShaderPath(const String& nameShader, ShaderSortType type);

                virtual bool createGLShader(const String& nameShader, const String& pathFile, FShaderType typeShader, uint32& nShaderID);
                virtual bool createGLShader(const String& nameShader, const String& strTypeShader, const String& pathFile, FShaderType typeShader, uint32& nShaderID);
                virtual void destroyGLShader(uint32 nShaderID);
                

                virtual GLShaderProgram* createShaderProgram(const String& nameShaderProgram,
                                                             GLShader* pShaderVertex,
                                                             GLShader* pShaderTessellationControl,
                                                             GLShader* pShaderTessellationEvaluation,
                                                             GLShader* pShaderGeometry,
                                                             GLShader* pShaderFragment);
                virtual GLShaderProgram* createShaderProgram(const String& nameShaderProgram,
                                                             GLShader* pShaderCompute);

                virtual uint32 createGLShaderProgram();
                virtual bool createGLShaderProgram(const String& nameShaderProgram,
                                                   uint32 nShaderVertexID,
                                                   uint32 nShaderTessellationControlID,
                                                   uint32 nShaderTessellationEvaluationID,
                                                   uint32 nShaderGeometryID,
                                                   uint32 nShaderFragmentID,
                                                   uint32& nShaderProgramID);
                virtual bool createGLShaderProgram(const String& nameShaderProgram,
                                                   uint32 nShaderComputeID,
                                                   uint32& nShaderProgramID);
                virtual void bindGLShaderProgram(uint32 nShaderProgramID);
                virtual void destroyGLShaderProgram(uint32 nShaderProgramID);
                virtual bool checkGLShaderCompileErrors(uint32 nShader, const String& type);    


                virtual void createCustomBeforePipeline();
                virtual void createGraphicsPipeline();
                    virtual void createGraphicsPipeline_Default();
                    virtual void createGraphicsPipeline_Custom();    


                virtual void createComputePipeline();
                    virtual void createComputePipeline_Default();
                    virtual void createComputePipeline_Custom();


        //Resize
        virtual void resizeWindow(int w, int h, bool force);


        //Compute Before Render


        //Compute After Render



        //Render/Update
        virtual bool beginRender();
            virtual void updateRender();
                virtual void updateCBs_Default();
                    virtual void updateCBs_Pass();
                        virtual void updateCBs_PassTransformAndCamera(PassConstants& pass, FCamera* pCam, int nIndex);
                    virtual void updateCBs_Objects();
                        virtual void updateCBs_ObjectsContent();
                    virtual void updateCBs_Materials();
                        virtual void updateCBs_MaterialsContent();
                    virtual void updateCBs_Instances();
                        virtual void updateCBs_InstancesContent();
                virtual void updateCBs_Terrain();
                virtual void updateCBs_ImGUI();
                    virtual bool beginRenderImgui();
                        //Common
                        virtual void commonConfig();
                            virtual void commonShowConfig();
                            virtual void commonEditorConfig();
                        //Camera
                        virtual void cameraConfig();
                            virtual void cameraReset();
                        //Light
                        virtual void lightConfig();
                            virtual void lightConfigItem(LightConstants& lc, const String& name, int index, bool canChangeType, bool bIsMainLight);
                            virtual void lightMainReset();
                        //Shadow
                        virtual void shadowConfig();
                            virtual void shadowConfigItem(ShadowConstants& sc, const String& name, bool bIsMainLight);
                            virtual void shadowReset();
                         //Cull
                        virtual void cullConfig();
                        //Terrain
                        virtual void terrainConfig();
                            virtual void terrainConfigItem(TerrainConstants& tc, const String& name);
                                virtual bool terrainConfigSplatItem(TerrainSplatConstants& tsc, const String& name);
                            virtual void terrainReset();
                        //PassConstants
                        virtual void passConstantsConfig();
                        //Model
                        virtual void modelConfig();
                        
                    virtual void endRenderImgui();
                virtual void updateCBs_Editor();
                virtual void updateCBs_Custom();

                virtual void updateRenderCommandBuffers_CustomBeforeDefault();
                virtual void updateRenderCommandBuffers_Default();

                    virtual void updateRenderPass_CustomBeforeDefault();
                    virtual void updateRenderPass_Default();
                        virtual void updateMeshDefault_Before();
                            virtual void drawMeshDefault();
                            virtual void drawMeshTerrain();
                            virtual void drawMeshDefault_Custom();
                            virtual void drawMeshDefault_Editor();
                            virtual void drawMeshDefault_CustomBeforeImgui();
                            virtual void drawMeshDefault_Imgui();
                        virtual void updateMeshDefault_After();
                    virtual void updateRenderPass_CustomAfterDefault();


                    virtual void beginRenderPass(const String& nameRenderPass,
                                                 const FSizeI& offset,
                                                 const FSizeI& extent,
                                                 const FVector4& clBg,
                                                 float depth,
                                                 uint32_t stencil);
                    
                        virtual void draw(GLenum mode, GLint first, GLsizei count);
                        virtual void drawIndexed(GLenum mode, GLsizei count, GLenum type, const void* indices);

                    virtual void endRenderPass();


                virtual void updateRenderCommandBuffers_CustomAfterDefault();

            virtual void render();
        virtual void endRender();

        //cleanup
        virtual void cleanup();
            virtual void cleanupDefault();
                virtual void cleanupTexture();
                virtual void cleanupVertexIndexBuffer();
            virtual void cleanupImGUI();
            virtual void cleanupEditor();
            virtual void cleanupCustom();

            virtual void cleanupSwapChain();
                virtual void cleanupSwapChain_Default();
                virtual void cleanupSwapChain_Editor();
                virtual void cleanupSwapChain_Custom();
            virtual void recreateSwapChain();
                virtual void recreateSwapChain_Editor();
                virtual void recreateSwapChain_Custom();

    private:


    };

}; //LostPeterOpenGL

#endif