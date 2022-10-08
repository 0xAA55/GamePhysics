#pragma once
#include<GLRendererBase.hpp>
#include<vector>
#include<memory>
#include<cstring>
#include<stdexcept>
#include<unordered_map>
namespace GLRenderer
{
	enum class BufferType
	{
		ArrayBuffer = 0x8892,
		AtomicCounterBuffer = 0x92C0,
		CopyReadBuffer = 0x8F36,
		CopyWriteBuffer = 0x8F37,
		DispatchIndirectBuffer = 0x90EE,
		DrawIndirectBuffer = 0x8F3F,
		ElementArrayBuffer = 0x8893,
		PixelPackBuffer = 0x88EB,
		PixelUnpackBuffer = 0x88EC,
		QueryBuffer = 0x9192,
		ShaderStorageBuffer = 0x90D2,
		TextureBuffer = 0x8C2A,
		TransformFeedbackBuffer = 0x8C8E,
		UniformBuffer = 0x8A11
	};

	enum class BufferUsage
	{
		StreamDraw = 0x88E0,
		StreamRead = 0x88E1,
		StreamCopy = 0x88E2,
		StaticDraw = 0x88E4,
		StaticRead = 0x88E5,
		StaticCopy = 0x88E6,
		DynamicDraw = 0x88E8,
		DynamicRead = 0x88E9,
		DynamicCopy = 0x88EA
	};

	class GLBufferObject
	{
	protected:
		BufferType Type;
		BufferUsage Usage;
		GLuint Object;
		size_t Length;

	public:
		GLBufferObject() = delete;
		GLBufferObject(const GLBufferObject &From) = delete;
		GLBufferObject(GLBufferObject &From, ptrdiff_t CopyLength = -1);
		GLBufferObject(GLBufferObject &From, size_t Length, ptrdiff_t CopyLength = -1);
		GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage);
		GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage, GLBufferObject &CopyFrom, ptrdiff_t CopyLength = -1);
		~GLBufferObject();

		inline operator GLuint() const { return Object; }
		inline GLuint GetObject() const { return Object; }
		inline size_t GetLength() const { return Length; }

		void *MapRO() const;
		void *MapWO() const;
		void *MapRW() const;
		void *MapRO(size_t Offset, size_t Length) const;
		void *MapWO(size_t Offset, size_t Length) const;
		void *MapRW(size_t Offset, size_t Length) const;
		void Unmap() const;
		void SetData(const void *Data) const;
		void GetData(void *DataOut) const;
		void SetData(size_t Offset, size_t Length, const void *Data) const;
		void GetData(size_t Offset, size_t Length, void *DataOut) const;

		void Bind() const;
		void Unbind() const;
		bool IsBind() const;
	};

}
