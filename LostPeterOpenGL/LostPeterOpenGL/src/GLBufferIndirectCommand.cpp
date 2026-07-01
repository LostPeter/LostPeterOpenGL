/****************************************************************************
* LostPeterOpenGL - Copyright (C) 2022 by LostPeter
* 
* Author:   LostPeter
* Time:     2026-06-27
* Github:   https://github.com/LostPeter/LostPeterOpenGL
* Document: https://www.zhihu.com/people/lostpeter/posts
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
****************************************************************************/

#include "../include/GLBufferIndirectCommand.h"
#include "../include/OpenGLWindow.h"

namespace LostPeterOpenGL
{
    GLBufferIndirectCommand::GLBufferIndirectCommand(const String& nameBuffer)
        : GLBuffer(nameBuffer)

		, eUsage(GL_STATIC_DRAW)
		
		, nBufferIndirectCommandID(0)
    {

    }
    GLBufferIndirectCommand::~GLBufferIndirectCommand()
    {
        Destroy();
    }

    void GLBufferIndirectCommand::Destroy()
    {
		Base::GetWindowPtr()->destroyGLBufferIndirectCommand(this->nBufferIndirectCommandID);
        this->indirectDrawInstanceCommandCBs.clear();
        this->indirectDrawIndexedInstanceCommandCBs.clear();
    }

	bool GLBufferIndirectCommand::InitIndirectDrawInstance(GLenum usage,
														   int count)
	{
		this->eUsage = usage;
        this->indirectDrawInstanceCommandCBs.resize(count);
        this->indirectDrawIndexedInstanceCommandCBs.clear();

		if (!Base::GetWindowPtr()->createGLBufferIndirectCommand(GetName(),
																 usage,
																 sizeof(DrawArraysIndirectCommand) * count,
																 (uint8*)(this->indirectDrawInstanceCommandCBs.data()), 
																 this->nBufferIndirectCommandID))
        {
            F_LogError("*********************** GLBufferIndirectCommand::InitIndirectDrawInstance: Failed to create buffer indirect command: [%s] !", GetName().c_str());
            return false;
        }

		return true;
	}
    bool GLBufferIndirectCommand::InitIndirectDrawIndexedInstance(GLenum usage,
																  int count)
	{
		this->eUsage = usage;
        this->indirectDrawInstanceCommandCBs.clear(); 
        this->indirectDrawIndexedInstanceCommandCBs.resize(count);

		if (!Base::GetWindowPtr()->createGLBufferIndirectCommand(GetName(),
																 usage,
																 sizeof(DrawElementsIndirectCommand) * count,
																 (uint8*)(this->indirectDrawIndexedInstanceCommandCBs.data()), 
																 this->nBufferIndirectCommandID))
        {
            F_LogError("*********************** GLBufferIndirectCommand::InitIndirectDrawIndexedInstance: Failed to create buffer indirect command: [%s] !", GetName().c_str());
            return false;
        }

		return true;
	}

	void GLBufferIndirectCommand::UpdateBuffer()
	{
		if (this->indirectDrawInstanceCommandCBs.size() > 0) {
            Base::GetWindowPtr()->updateGLBufferIndirectCommand(0,
																sizeof(DrawArraysIndirectCommand) * this->indirectDrawInstanceCommandCBs.size(),
																(uint8*)(this->indirectDrawInstanceCommandCBs.data()),
																this->nBufferIndirectCommandID);
        } else if (this->indirectDrawIndexedInstanceCommandCBs.size() > 0) {
            Base::GetWindowPtr()->updateGLBufferIndirectCommand(0, 
																sizeof(DrawElementsIndirectCommand) * this->indirectDrawIndexedInstanceCommandCBs.size(),
																(uint8*)(this->indirectDrawIndexedInstanceCommandCBs.data()),
																this->nBufferIndirectCommandID);
        }
	}
	void GLBufferIndirectCommand::UpdateBuffer(int index, const DrawArraysIndirectCommand& args)
	{
		this->indirectDrawInstanceCommandCBs[index] = args;
        UpdateBuffer();
	}
	void GLBufferIndirectCommand::UpdateBuffer(const std::vector<DrawArraysIndirectCommand>& args)
	{
		F_Assert(args.size() <= this->indirectDrawInstanceCommandCBs.size() && "GLBufferIndirectCommand::UpdateBuffer")
        for (size_t i = 0; i < args.size(); i++)
        {
            this->indirectDrawInstanceCommandCBs[i] = args[i];
        }
        UpdateBuffer();
	}
	void GLBufferIndirectCommand::UpdateBuffer(int index, const DrawElementsIndirectCommand& args)
	{	
		this->indirectDrawIndexedInstanceCommandCBs[index] = args;
        UpdateBuffer();
	}
	void GLBufferIndirectCommand::UpdateBuffer(const  std::vector<DrawElementsIndirectCommand>& args)
	{
		F_Assert(args.size() <= this->indirectDrawIndexedInstanceCommandCBs.size() && "GLBufferIndirectCommand::UpdateBuffer")
        for (size_t i = 0; i < args.size(); i++)
        {
            this->indirectDrawIndexedInstanceCommandCBs[i] = args[i];
        }
        UpdateBuffer();
	}


}; //LostPeterOpenGL