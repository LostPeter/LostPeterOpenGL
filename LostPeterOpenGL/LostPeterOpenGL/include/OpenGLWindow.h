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


        FSizeI poOffset;
        FSizeI poExtent;
        FRectI poScissor;


        FVector2 poFramebufferSize;
        FVector2 poWindowContentScale;



        uint32_t poVertexCount;
        size_t poVertexBuffer_Size;
        void* poVertexBuffer_Data;
        uint32_t poIndexCount;
        size_t poIndexBuffer_Size;
        void* poIndexBuffer_Data;
        FMatrix4 poMatWorld;


        bool isFrameBufferResized;

        //Config
        FVector4 cfg_colorBackground;
        FVector4Vector cfg_colorValues;




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


    public:


    public:
        //Create Pipeline
        virtual void createPipeline();
            virtual void createWindowCallback();
            virtual void createDevice();


            virtual void createFeatureSupport();


        //Load Assets
        virtual void loadAssets();


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