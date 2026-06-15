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

#ifndef _GL_TEXTURE_H_
#define _GL_TEXTURE_H_

#include "Base.h"

namespace LostPeterOpenGL
{
    class openglExport GLTexture : public Base
    {
    public:
        GLTexture(const String& _nameTexture,
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
                  bool _isGraphicsComputeShared,
			  	  bool _isRenderTarget,
                  bool _isUnOrderedAccess,
                  const FColor& _rtColor);
        virtual ~GLTexture();

    public:
        StringVector aPathTexture;
        FTextureType typeTexture;
        FTexturePixelFormatType typePixelFormat;
        FTextureAddressingType typeAddressing;
        FTextureFilterType typeFilterSizeMin;
        FTextureFilterType typeFilterSizeMag;
        FMSAASampleCountType numSamples;
        FColor borderColor;
        bool isUseBorderColor;
        bool isGraphicsComputeShared;
		bool isRenderTarget;
		bool isUnOrderedAccess;
        FColor rtColor;
        int width;
        int height;
        int depth;
        int channel;

        int mipMapCount;
        bool isAutoMipmap;

        //Texture 3D
        uint8* pDataRGBA;
		bool isDeleteRGBA;

        //Texture Animation
        int texChunkMaxX;
        int texChunkMaxY;
        int texChunkIndex;
        int frameCurrent;

        //Texture RenderTarget
        FVector4 rtColorDefault;
        bool rtIsSetColor; 
        

        uint32 nTextureID;

    public:
        void Destroy();
        virtual bool Init();

		virtual int RandomTextureIndex();
        virtual bool LoadTexture(int width,
                                 int height,
                                 int depth,
                                 int channel,
                                 uint8* pData);
        virtual void UpdateTexture();

    public:
        void BindTexture(uint slot, bool enable);
        void BindTextureImage(uint slot, uint32 access, bool enable);

	protected:
        virtual void updateNoiseTextureData();
        virtual void updateNoiseTexture();
    };

}; //LostPeterOpenGL

#endif