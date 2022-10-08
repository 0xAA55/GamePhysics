#include"GLBufferObject.hpp"
#include<GL/glew.h>
#include<cstdlib>
#include<cassert>
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
	Unbind();
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

bool GLBufferObject::IsBind() const
{
	GLenum Check = 0;
	GLint BindObj = 0;
	switch (Type)
	{
	case BufferType::ArrayBuffer: Check = GL_ARRAY_BUFFER_BINDING; break;
	case BufferType::AtomicCounterBuffer: Check = GL_ATOMIC_COUNTER_BUFFER_BINDING; break;
	case BufferType::CopyReadBuffer: Check = GL_COPY_READ_BUFFER_BINDING; break;
	case BufferType::CopyWriteBuffer: Check = GL_COPY_WRITE_BUFFER_BINDING; break;
	case BufferType::DispatchIndirectBuffer: Check = GL_DISPATCH_INDIRECT_BUFFER_BINDING; break;
	case BufferType::DrawIndirectBuffer: Check = GL_DRAW_INDIRECT_BUFFER_BINDING; break;
	case BufferType::ElementArrayBuffer: Check = GL_ELEMENT_ARRAY_BUFFER_BINDING; break;
	case BufferType::PixelPackBuffer: Check = GL_PIXEL_PACK_BUFFER_BINDING; break;
	case BufferType::PixelUnpackBuffer: Check = GL_PIXEL_UNPACK_BUFFER_BINDING; break;
	case BufferType::QueryBuffer: Check = GL_QUERY_BUFFER_BINDING; break;
	case BufferType::ShaderStorageBuffer: Check = GL_SHADER_STORAGE_BUFFER_BINDING; break;
	case BufferType::TextureBuffer: Check = GL_TEXTURE_BUFFER_BINDING; break;
	case BufferType::TransformFeedbackBuffer: Check = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING; break;
	case BufferType::UniformBuffer: Check = GL_UNIFORM_BUFFER_BINDING; break;
	default: throw std::invalid_argument("Unknown buffer type.");
	}
	glGetIntegerv(Check, &BindObj);
	return BindObj == Object;
}

#if _DEBUG
#define CHECKBINDING 1
#else
#define CHECKBINDING 0
#endif

#if CHECKBINDING
#define CheckBind() assert(IsBind())
#else
#define CheckBind()
#endif

void *GLBufferObject::MapRO() const
{
	CheckBind();
	return glMapBuffer(static_cast<GLenum>(Type), GL_READ_ONLY);
}

void *GLBufferObject::MapWO() const
{
	CheckBind();
	return glMapBuffer(static_cast<GLenum>(Type), GL_WRITE_ONLY);
}

void *GLBufferObject::MapRW() const
{
	CheckBind();
	return glMapBuffer(static_cast<GLenum>(Type), GL_READ_WRITE);
}

void *GLBufferObject::MapRO(size_t Offset, size_t Length) const
{
	CheckBind();
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT);
}

void *GLBufferObject::MapWO(size_t Offset, size_t Length) const
{
	CheckBind();
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
}

void *GLBufferObject::MapRW(size_t Offset, size_t Length) const
{
	CheckBind();
	return glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void GLBufferObject::Unmap() const
{
	CheckBind();
	glUnmapBuffer(static_cast<GLenum>(Type));
}

void GLBufferObject::SetData(const void *Data) const
{
	CheckBind();
	void *MapPtr = glMapBuffer(static_cast<GLenum>(Type), GL_WRITE_ONLY);
	std::memcpy(MapPtr, Data, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));
}

void GLBufferObject::GetData(void *DataOut) const
{
	CheckBind();
	void *MapPtr = glMapBuffer(static_cast<GLenum>(Type), GL_READ_ONLY);
	std::memcpy(DataOut, MapPtr, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));

}

void GLBufferObject::SetData(size_t Offset, size_t Length, const void *Data) const
{
	CheckBind();
	void *MapPtr = glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	std::memcpy(MapPtr, Data, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));
}

void GLBufferObject::GetData(size_t Offset, size_t Length, void *DataOut) const
{
	CheckBind();
	void *MapPtr = glMapBufferRange(static_cast<GLenum>(Type), Offset, Length, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	std::memcpy(DataOut, MapPtr, Length);
	glUnmapBuffer(static_cast<GLenum>(Type));
}
