#pragma once
#include<GLBufferObject.hpp>
#include<memory>
namespace GLRenderer
{
	class GLSharedBuffer
	{
	protected:
		std::shared_ptr<GLBufferObject> BufferObject;
		GLBufferObject* BufferObjectInUse;

	public:
		GLSharedBuffer();
		GLSharedBuffer(GLSharedBuffer& CreateFrom);
		GLSharedBuffer(const GLSharedBuffer& CopyFrom);
		GLSharedBuffer(std::shared_ptr<GLBufferObject> Buffer);

		void BindForDraw();
		void BindForDataAccess() const;
		void Unbind() const;

		inline void SetBufferObject(std::shared_ptr<GLBufferObject> BufferObject) { this->BufferObject = BufferObject; }
		inline bool BufferChanged() const { return BufferObject.get() != BufferObjectInUse; }

		inline GLBufferObject& operator*() const { return *BufferObject.get(); }
		inline GLBufferObject* operator->() const { return BufferObject.get(); }

		inline bool IsEmpty() const { return BufferObject.get() == nullptr; }
		inline void Clear() { BufferObject.reset(); }
		inline operator bool() const { return !IsEmpty(); }

		inline size_t Size() { return IsEmpty() ? 0 : BufferObject->GetLength(); }
	};
}
