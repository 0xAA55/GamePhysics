#include "GLBuffer.hpp"
#include<GL/glew.h>
using namespace GLRenderer;

std::unordered_map<BufferType, GLuint> GLBufferObject::BufferBindings;

GLBufferObject::GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage) :
	Type(Type),
	Usage(Usage),
	Length(Length)
{
	glGenBuffers(1, &Object);
	Bind();
	glBufferData(static_cast<GLenum>(Type), Length, nullptr, static_cast<GLenum>(Usage));
}

GLBufferObject::GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage, GLBufferObject &CopyFrom, ptrdiff_t CopyLength) :
	GLBufferObject(Type, Length, Usage)
{
	if (CopyLength == -1) CopyLength = CopyFrom.Length;
	if (CopyFrom.Type != Type)
	{
		CopyFrom.Bind();
		Bind();
		glCopyBufferSubData(static_cast<GLenum>(CopyFrom.Type), static_cast<GLenum>(Type), 0, 0, CopyLength);
	}
	else
	{
		GLenum CopyFromBuffer = static_cast<GLenum>(BufferType::CopyReadBuffer);
		BufferType CopyToType = Type == BufferType::CopyReadBuffer ? BufferType::CopyWriteBuffer : Type;
		GLenum CopyToBuffer = static_cast<GLenum>(CopyToType);
		GLuint OldCopyRead = BufferBindings[BufferType::CopyReadBuffer];
		Bind(BufferType::CopyReadBuffer, CopyFrom.Object);
		Bind(CopyToType, Object);
		glCopyBufferSubData(CopyFromBuffer, CopyToBuffer, 0, 0, min(Length, static_cast<size_t>(CopyLength)));
		Bind(BufferType::CopyReadBuffer, OldCopyRead);
	}
}

GLBufferObject::~GLBufferObject()
{
	if (BufferBindings[Type] == Object)
	{
		Unbind();
	}
	glDeleteBuffers(1, &Object);
}

void GLBufferObject::Bind(BufferType Type, GLuint BufferObject)
{
	if (BufferBindings[Type] != BufferObject)
	{
		glBindBuffer(static_cast<GLenum>(Type), BufferObject);
		BufferBindings[Type] = BufferObject;
	}
}
void GLBufferObject::Unbind(BufferType Type)
{
	glBindBuffer(static_cast<GLenum>(Type), 0);
	BufferBindings[Type] = 0;
}

size_t GLBufferObject::GetLength()
{
	return Length;
}

GLBufferObject::operator GLuint() const
{
	return Object;
}

void *GLBufferObject::MapRO()
{
	Bind();
	return glMapBuffer(static_cast<GLenum>(Type), GL_READ_ONLY);
}

void *GLBufferObject::MapWO()
{
	Bind();
	return glMapBuffer(static_cast<GLenum>(Type), GL_WRITE_ONLY);
}

void *GLBufferObject::MapRW()
{
	Bind();
	return glMapBuffer(static_cast<GLenum>(Type), GL_READ_WRITE);
}

void *GLBufferObject::MapRO(size_t Offset, size_t Length)
{
	Bind();
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT);
}

void *GLBufferObject::MapWO(size_t Offset, size_t Length)
{
	Bind();
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
}

void *GLBufferObject::MapRW(size_t Offset, size_t Length)
{
	Bind();
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void GLBufferObject::Unmap()
{
	Bind();
	glUnmapBuffer(static_cast<GLenum>(Type));
}
