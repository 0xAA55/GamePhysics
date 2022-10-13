#include "GLSharedBuffer.hpp"
using namespace GLRenderer;

GLSharedBuffer::GLSharedBuffer() :
	BufferObject(nullptr),
	BufferObjectInUse(nullptr)
{};

GLSharedBuffer::GLSharedBuffer(GLSharedBuffer& CreateFrom) :
	BufferObject(CreateFrom.BufferObject),
	BufferObjectInUse(nullptr)
{};

GLSharedBuffer::GLSharedBuffer(const GLSharedBuffer& CopyFrom) :
	BufferObject(std::make_shared<GLBufferObject>(*CopyFrom.BufferObject)),
	BufferObjectInUse(nullptr)
{};

GLSharedBuffer::GLSharedBuffer(std::shared_ptr<GLBufferObject> Buffer) :
	BufferObject(Buffer),
	BufferObjectInUse(nullptr)
{
}

void GLSharedBuffer::BindForDraw()
{
	BufferObject->Bind();
	BufferObjectInUse = BufferObject.get();
}

void GLSharedBuffer::BindForDataAccess() const
{
	BufferObject->Bind();
}

void GLSharedBuffer::Unbind() const
{
	BufferObject->Unbind();
}
