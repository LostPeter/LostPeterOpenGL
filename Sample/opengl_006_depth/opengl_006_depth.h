/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-10
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _OPENGL_006_DEPTH_H_
#define _OPENGL_006_DEPTH_H_

#include "OpenGLWindow.h"
using namespace LostPeterOpenGL; 

class OpenGL_006_Depth : public OpenGLWindow
{
public:
    OpenGL_006_Depth(int width, int height, String name);

public:
	struct ModelObject
	{
		ModelObject(OpenGL_006_Depth* _pWindow)
			//Common
			: pWindow(_pWindow)

			//Name
			, nameModel("")
			, pathModel("")
			, pathTexture("")
			, isShow(true)
			, isRotate(true)
			, isWireFrame(false)
			, isNoDepthEnable(false)
			, isNoDepthTest(false)
			, isNoDepthWrite(false)

			//Vertex/Index
			, poVertexCount(0)
			, poVertexBuffer_Size(0)
			, poVertexBuffer_Data(nullptr)
			, poIndexCount(0)
			, poIndexBuffer_Size(0)
			, poIndexBuffer_Data(nullptr)
			, pBufferVertex(nullptr)
			, pBufferVertexIndex(nullptr)
			
			//Uniform
			, poBufferUniform(nullptr)
			, poMatWorld(1.0f)
			
			//Texture
			, poTexture(nullptr)

			//Pipeline
			, poStatePipelineGraphics(nullptr)

			//State
			, poTypePrimitive(GL_TRIANGLES)
			, poIsCull(true)
			, poTypeFrontFace(GL_CW)
			, poTypeCulling(GL_BACK)
			, poTypePolygonMode(GL_FILL)

			, poDepthEnabled(false)
			, poDepthFuncCompare(GL_LEQUAL)
			, poDepthTestEnabled(false)
			, poDepthWriteEnabled(false)

			, poStencilEnabled(false)
			, poStencil_CompareFunction(GL_LEQUAL)
			, poStencil_StencilFailureOp(GL_KEEP)
			, poStencil_DepthFailureOp(GL_KEEP)
			, poStencil_DepthStencilPassOp(GL_KEEP)
			, poStencil_ReadMask(0)
			, poStencil_WriteMask(0)
			
			, poBlendEnabled(false)
			, poBlendColorFactorSrc(GL_ONE)
			, poBlendColorFactorDst(GL_ZERO)
			, poBlendColorOp(GL_FUNC_ADD)
			, poBlendAlphaFactorSrc(GL_ONE)
			, poBlendAlphaFactorDst(GL_ZERO)
			, poBlendAlphaOp(GL_FUNC_ADD)

			, poColorWriteMask_Red(true)
			, poColorWriteMask_Green(true)
			, poColorWriteMask_Blue(true)
			, poColorWriteMask_Alpha(true)
		{
			
		}
		~ModelObject()
		{
			//Vertex/Index
			F_DELETE(this->pBufferVertex)
			F_DELETE(this->pBufferVertexIndex)
			//Uniform
			this->objectCBs.clear();
			F_DELETE(this->poBufferUniform)

			//Texture
			F_DELETE(this->poTexture)

			//Pipeline
			F_DELETE(this->poStatePipelineGraphics)
		}

		//Common
		OpenGL_006_Depth* pWindow;

		//Name
		String nameModel;
		String pathModel;
		String pathTexture;
		bool isShow;
		bool isRotate;
		bool isWireFrame;
		bool isNoDepthEnable;
		bool isNoDepthTest;
		bool isNoDepthWrite;

		//Vertex/Index
		std::vector<FVertex_Pos3Color4Tex2> vertices;
		uint32_t poVertexCount;
		size_t poVertexBuffer_Size;
		void* poVertexBuffer_Data;
		std::vector<uint32_t> indices;
		uint32_t poIndexCount;
		size_t poIndexBuffer_Size;
		void* poIndexBuffer_Data;
		GLBufferVertex* pBufferVertex;
		GLBufferVertexIndex* pBufferVertexIndex;

		//Uniform
		std::vector<ObjectConstants> objectCBs;
		GLBufferUniform* poBufferUniform;
		FMatrix4 poMatWorld;

		//Texture
		GLTexture* poTexture;

		//Pipeline
		GLStatePipelineGraphics* poStatePipelineGraphics;

		//State
		GLenum poTypePrimitive;
        bool poIsCull;
        GLenum poTypeFrontFace;
        GLenum poTypeCulling;
        GLenum poTypePolygonMode;

		bool poDepthEnabled;
		GLenum poDepthFuncCompare;
		bool poDepthTestEnabled;
		bool poDepthWriteEnabled;

		bool poStencilEnabled;
		GLenum poStencil_CompareFunction;
		GLenum poStencil_StencilFailureOp;
		GLenum poStencil_DepthFailureOp;
		GLenum poStencil_DepthStencilPassOp;
		uint32_t poStencil_ReadMask;
		uint32_t poStencil_WriteMask;

		bool poBlendEnabled;
		GLenum poBlendColorFactorSrc; 
		GLenum poBlendColorFactorDst;
		GLenum poBlendColorOp;
		GLenum poBlendAlphaFactorSrc; 
		GLenum poBlendAlphaFactorDst;
		GLenum poBlendAlphaOp;

		GLboolean poColorWriteMask_Red;
		GLboolean poColorWriteMask_Green;
		GLboolean poColorWriteMask_Blue;
		GLboolean poColorWriteMask_Alpha;
	};
	typedef std::vector<ModelObject*> ModelObjectPtrVector;
	typedef std::map<String, ModelObject*> ModelObjectPtrMap;

public:
	ModelObjectPtrVector m_aModelObjects;
	ModelObjectPtrMap m_mapModelObjects;

	FMeshVertexType typeVertex;
	String shaderVertex_Path;
	String shaderFragment_Path;
	GLShader* pShaderVertex;
	GLShader* pShaderFragment;


protected:
	//Create Pipeline

	//Load Assets
		//Camera
		virtual void createCamera();

		//Geometry/Texture
		virtual void loadModel_Custom();
			bool loadModel_VertexIndex(ModelObject* pModelObject, bool isFlipY, bool isTransformLocal, const FMatrix4& matTransformLocal);
			bool loadModel_Texture(ModelObject* pModelObject);

		//ConstBuffers
		virtual void createCustomCB();

		//Pipeline
		virtual void createGraphicsPipeline_Custom();

		//DescriptorSets
		virtual void createDescriptorSets_Custom();

	//Render/Update
		virtual void updateCBs_Custom();

		virtual bool beginRenderImgui();
			virtual void modelConfig();
			
		virtual void endRenderImgui();

		virtual void drawMeshDefault_Custom();

	//cleanup
		virtual void cleanupCustom();

};


#endif