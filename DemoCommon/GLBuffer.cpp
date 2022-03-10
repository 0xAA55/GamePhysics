#include"GLBuffer.hpp"
#include<GL/glew.h>
#include<cstdlib>
using namespace GLRenderer;

GLBufferObject::GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage) :
	Type(Type),
	Usage(Usage),
	Length(Length),
	Object(0)
{
	if (!Length) throw std::invalid_argument("Couldn't create a GLBufferObject when `Length` == 0");
	glGenBuffers(1, &Object); Bind();
	glBufferData(static_cast<GLenum>(Type), Length, nullptr, static_cast<GLenum>(Usage));
}

GLBufferObject::GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage, GLBufferObject &CopyFrom, ptrdiff_t CopyLength) :
	GLBufferObject(Type, Length, Usage)
{
	if (CopyLength == -1) CopyLength = CopyFrom.Length;
	else CopyLength = min(CopyLength, static_cast<ptrdiff_t>(CopyFrom.Length));
	if (CopyLength)
	{
		if (CopyFrom.Type != Type)
		{
			Bind(); CopyFrom.Bind();
			glCopyBufferSubData(static_cast<GLenum>(CopyFrom.Type), static_cast<GLenum>(Type), 0, 0, CopyLength);
			Unbind(); CopyFrom.Unbind();
		}
		else
		{
			GLenum CopyFromBuffer = static_cast<GLenum>(BufferType::CopyReadBuffer);
			GLenum CopyToBuffer = static_cast<GLenum>(BufferType::CopyWriteBuffer);
			glBindBuffer(CopyFromBuffer, CopyFrom.Object);
			glBindBuffer(CopyToBuffer, Object);
			glCopyBufferSubData(CopyFromBuffer, CopyToBuffer, 0, 0, min(Length, static_cast<size_t>(CopyLength)));
			glBindBuffer(CopyFromBuffer, 0);
			glBindBuffer(CopyToBuffer, 0);
		}
	}
}

GLBufferObject::GLBufferObject(GLBufferObject &From, ptrdiff_t CopyLength) :
	GLBufferObject(From.Type, From.Length, From.Usage, From, CopyLength)
{
}

GLBufferObject::GLBufferObject(GLBufferObject &From, size_t Length, ptrdiff_t CopyLength) :
	GLBufferObject(From.Type, Length, From.Usage, From, CopyLength)
{
}

GLBufferObject::~GLBufferObject()
{
	glDeleteBuffers(1, &Object);
}

void GLBufferObject::Bind() const
{
	glBindBuffer(static_cast<GLenum>(Type), Object);
}

void GLBufferObject::Unbind() const
{
	glBindBuffer(static_cast<GLenum>(Type), 0);
}

void *GLBufferObject::MapRO() const
{
	return glMapBuffer(static_cast<GLenum>(Type), GL_READ_ONLY);
}

void *GLBufferObject::MapWO() const
{
	return glMapBuffer(static_cast<GLenum>(Type), GL_WRITE_ONLY);
}

void *GLBufferObject::MapRW() const
{
	return glMapBuffer(static_cast<GLenum>(Type), GL_READ_WRITE);
}

void *GLBufferObject::MapRO(size_t Offset, size_t Length) const
{
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT);
}

void *GLBufferObject::MapWO(size_t Offset, size_t Length) const
{
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
}

void *GLBufferObject::MapRW(size_t Offset, size_t Length) const
{
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void GLBufferObject::Unmap() const
{
	glUnmapBuffer(static_cast<GLenum>(Type));
}

void GLBufferObject::SetData(const void *Data) const
{
	void *MapPtr = glMapBuffer(static_cast<GLenum>(Type), GL_WRITE_ONLY);
	std::memcpy(MapPtr, Data, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));
}

void GLBufferObject::GetData(void *DataOut) const
{
	void *MapPtr = glMapBuffer(static_cast<GLenum>(Type), GL_READ_ONLY);
	std::memcpy(DataOut, MapPtr, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));

}

void GLBufferObject::SetData(size_t Offset, size_t Length, const void *Data) const
{
	void *MapPtr = glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	std::memcpy(MapPtr, Data, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));
}

void GLBufferObject::GetData(size_t Offset, size_t Length, void *DataOut) const
{
	void *MapPtr = glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	std::memcpy(DataOut, MapPtr, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));
}

BufferCastingError::BufferCastingError(std::string What) noexcept :
	std::runtime_error(What)
{
}
