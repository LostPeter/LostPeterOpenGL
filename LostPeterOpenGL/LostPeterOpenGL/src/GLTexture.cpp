/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2024-11-07
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "../include/GLTexture.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLTexture::GLTexture(const String& _nameTexture,
                         const StringVector& _aPathTexture,
                         FTextureType _typeTexture,
                         FTexturePixelFormatType _typePixelFormat,
                         FTextureAddressingType _typeAddressing,
                         FTextureFilterType _typeFilterSizeMin,
                         FTextureFilterType _typeFilterSizeMag,
                         FMSAASampleCountType _numSamples,
                         const FColor& _borderColor,
                         bool _isUseBorderColor,
                         bool _isAutoMipmap,
                         bool _isCubeMap,
                         bool _isRenderTarget,
                         bool _isGraphicsComputeShared)
        : Base(_nameTexture)
        , aPathTexture(_aPathTexture)
        , typeTexture(_typeTexture)
        , typePixelFormat(_typePixelFormat)
        , typeAddressing(_typeAddressing)
        , typeFilterSizeMin(_typeFilterSizeMin)
        , typeFilterSizeMag(_typeFilterSizeMag)
        , numSamples(_numSamples)
        , borderColor(_borderColor)
        , isUseBorderColor(_isUseBorderColor)
        , isCubeMap(_isCubeMap)
        , isRenderTarget(_isRenderTarget)
        , isGraphicsComputeShared(_isGraphicsComputeShared)
        
        , width(0)
        , height(0)
        , depth(0)
        , channel(4)

        , mipMapCount(1)
        , isAutoMipmap(_isAutoMipmap)

        //Texture 3D
        , pDataRGBA(nullptr)

        //Texture Animation
        , texChunkMaxX(0)
        , texChunkMaxY(0)
        , texChunkIndex(0)
        , frameCurrent(0)

        //Texture RenderTarget
        , rtColorDefault(0, 0, 0, 1)
        , rtIsSetColor(false)

        , nTextureID(0)
    {

    }
    GLTexture::~GLTexture()
    {
        Destroy();
    }

    void GLTexture::Destroy()
    {
        if (this->nTextureID > 0)
        {
            Base::GetWindowPtr()->destroyGLTexture(this->nTextureID);
        }
        this->nTextureID = 0;
    }

    bool GLTexture::Init()
    {
        return LoadTexture(0, 
                           0, 
                           0, 
                           4, 
                           nullptr);
    }

	int GLTexture::RandomTextureIndex()
    {
        if (this->typeTexture == F_Texture_2DArray)
        {
            int count = (int)this->aPathTexture.size();
            return FMath::Rand(0, count - 1);
        }
        return 0;
    }

    bool GLTexture::LoadTexture(int width,
                                int height,
                                int depth,
                                int channel,
                                uint8* pData)
    {   
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->channel = channel;

        if (!this->isRenderTarget)
        {
            if (this->typeTexture == F_Texture_1D)
            {

            }
            else if (this->typeTexture == F_Texture_2D)
            {
                if (!Base::GetWindowPtr()->createTexture2D(this->name,
                                                           this->aPathTexture[0], 
                                                           this->mipMapCount,
                                                           this->isAutoMipmap,
                                                           this->typeTexture,
                                                           this->isCubeMap,
                                                           this->typePixelFormat,
                                                           this->typeAddressing,
                                                           this->typeFilterSizeMin,
                                                           this->typeFilterSizeMag,
                                                           this->numSamples,
                                                           this->borderColor,
                                                           this->isUseBorderColor,
                                                           this->isGraphicsComputeShared,
                                                           this->nTextureID))
                {
                    F_LogError("*********************** GLTexture::LoadTexture: Failed to create texture, name: [%s], path: [%s] !", this->name.c_str(), this->aPathTexture[0].c_str());
                    return false;
                }
            }
            else if (this->typeTexture == F_Texture_2DArray)
            {

            }
            else if (this->typeTexture == F_Texture_3D)
            {

            }
            else if (this->typeTexture == F_Texture_CubeMap)
            {

            }
            else
            {
                String msg = "*********************** GLTexture::LoadTexture: Wrong texture type, Create from file, name: [" + this->name + "] !";
                F_LogError(msg.c_str());
                throw std::runtime_error(msg);
            }
        }
        else
        {
            if (this->typeTexture == F_Texture_1D)
            {

            }
            else if (this->typeTexture == F_Texture_2D)
            {
                if (!Base::GetWindowPtr()->createTextureRenderTarget2D(this->name,
                                                                       pData, 
                                                                       channel,
                                                                       width,
                                                                       height,
                                                                       this->mipMapCount,
                                                                       this->isAutoMipmap,
                                                                       this->typeTexture,
                                                                       this->isCubeMap,
                                                                       this->typePixelFormat,
                                                                       this->typeAddressing,
                                                                       this->typeFilterSizeMin,
                                                                       this->typeFilterSizeMag,
                                                                       this->numSamples,
                                                                       this->borderColor,
                                                                       this->isUseBorderColor,
                                                                       this->isGraphicsComputeShared,
                                                                       this->nTextureID))
                {
                    F_LogError("*********************** GLTexture::LoadTexture: Failed to create texture RenderTarget2D, name: [%s] !", this->name.c_str());
                    return false;
                }
            }
            else if (this->typeTexture == F_Texture_2DArray)
            {

            }
            else if (this->typeTexture == F_Texture_3D)
            {

            }
            else if (this->typeTexture == F_Texture_CubeMap)
            {

            }
            else
            {
                String msg = "*********************** GLTexture::LoadTexture: Wrong texture type, Create render target, name: [" + this->name + "] !";
                F_LogError(msg.c_str());
                throw std::runtime_error(msg);
            }
        }

        return true;
    }

    void GLTexture::UpdateTexture()
    {
		if (this->typeTexture == F_Texture_3D)
        {
            updateNoiseTexture();
        }
    }
	void GLTexture::updateNoiseTextureData()
    {
        // Perlin noise
        noise::module::Perlin modulePerlin;
        for (int z = 0; z < this->depth; z++)
        {
            for (int y = 0; y < this->height; y++)
            {
                for (int x = 0; x < this->width; x++)
                {
                    float nx = (float)x / (float)this->width;
                    float ny = (float)y / (float)this->height;
                    float nz = (float)z / (float)this->depth;

                    float n = 20.0f * (float)(modulePerlin.GetValue(nx, ny, nz));
                    n = n - floor(n);
                    uint8 v = static_cast<uint8>(floor(n * 255));
                    int address = x + y * this->width + z * this->width * this->height;
                    this->pDataRGBA[address + 0] = v;
                    if (channel > 1)
                         this->pDataRGBA[address + 1] = v;
                    if (channel > 2)
                         this->pDataRGBA[address + 2] = v;
                    if (channel > 3)
                         this->pDataRGBA[address + 3] = v;
                }
            }
        }
    }
    void GLTexture::updateNoiseTexture()
    {
        //1> updateNoiseTextureData
        updateNoiseTextureData();

        
    }

    void GLTexture::BindTexture()
    {
        if (this->nTextureID > 0)
        {
            Base::GetWindowPtr()->bindGLTexture(this->typeTexture, this->nTextureID);
        }
    }

}; //LostPeterOpenGL