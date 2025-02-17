/****************************************************************************
* LostPeterFoundation - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2023-06-17
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#ifndef _F_FILE_MANAGER_H_
#define _F_FILE_MANAGER_H_

#include "FPreDefine.h"
#include "FSingleton.h"

namespace LostPeterFoundation
{
    class foundationExport FFileMemoryPtr
	{
	public:
		FFileMemoryPtr();
		FFileMemoryPtr(FFileMemory* pFM);
		~FFileMemoryPtr();

	private:
		FFileMemory* m_pFileMemory;
		
	public:
		F_FORCEINLINE FFileMemory* GetFileMemory() const { return m_pFileMemory; }
		F_FORCEINLINE void SetFileMemory(FFileMemory* p) { m_pFileMemory = p; }
		
	public:
		uint8* GetBuffer();
		uint32 GetSize();
	};

    class foundationExport FFileManager : public FSingleton<FFileManager>
    {
    public:
        FFileManager();
        ~FFileManager();

    public:
	protected:
		FFileIOPtrMap m_mapFileIO;
		FFileMemoryPtrMap m_mapFileMemory;

    public:
        static FFileManager& GetSingleton();
        static FFileManager* GetSingletonPtr();

    public:
		void Destroy();
		
		FFileIO* CreateFileIO();
		void DeleteFileIO(FFileIO* pFIO);

		FFileMemory* CreateFileMemory(uint32 nSize);
		FFileMemory* CreateFileMemory(uint8* pBuffer,uint32 nSize);
		FFileMemory* CreateFileMemory(const String& strPath);
		void DeleteFileMemory(FFileMemory* pFM);
    };

}; //LostPeterFoundation

#endif