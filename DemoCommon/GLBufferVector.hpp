#pragma once
#include<GLSharedBuffer.hpp>
#include<memory>
namespace GLRenderer
{
	class BufferCastingError : public std::runtime_error
	{
	public:
		BufferCastingError(std::string What) noexcept;
	};

	template<typename T>
	class GLBufferIterator;

	template<typename T>
	class GLBufferConstIterator;

	template<typename T>
	class GLBufferVector
	{
	public:
		using Iterator = GLBufferIterator<T>;
		using ConstIterator = GLBufferConstIterator<T>;

	protected:
		size_t Count = 0;
		size_t Capacity = 0;
		std::shared_ptr<GLSharedBuffer> SelfObject = nullptr;

	public:
		BufferType Type;
		BufferUsage Usage;
		GLSharedBuffer& BufferObject;

		GLBufferVector(GLSharedBuffer& BufferObject) :
			Type(BufferType::ArrayBuffer),
			Usage(BufferUsage::StaticDraw),
			BufferObject(BufferObject)
		{
			if (!BufferObject.IsEmpty())
			{
				Capacity = Count = BufferObject->GetLength() / sizeof(T);
			}
		}

		GLBufferVector(BufferType Type, BufferUsage Usage, GLSharedBuffer& BufferObject) :
			Type(Type),
			Usage(Usage),
			BufferObject(BufferObject)
		{
		}

		GLBufferVector(GLBufferVector& CreateFrom) :
			Type(CreateFrom.Type),
			Usage(CreateFrom.Usage),
			BufferObject(CreateFrom.BufferObject),
			Count(CreateFrom.Count),
			Capacity(CreateFrom.Capacity)
		{
		}

		GLBufferVector(const GLBufferVector& CopyFrom) :
			Type(CopyFrom.Type),
			Usage(CopyFrom.Usage),
			BufferObject(CopyFrom.BufferObject),
			Count(CopyFrom.Count),
			Capacity(CopyFrom.Capacity)
		{
		}

		GLBufferVector(BufferType Type, BufferUsage Usage, const std::vector<T>& Data) :
			Type(Type),
			Usage(Usage),
			SelfObject(std::make_shared<GLSharedBuffer>(std::make_shared<GLBufferObject>(Type, Data.size() * sizeof(T), Usage))),
			BufferObject(*SelfObject),
			Count(Data.size()),
			Capacity(Data.capacity())
		{
		}

		~GLBufferVector()
		{
		}

		inline void BindForDataAccess() const
		{
			BufferObject.BindForDataAccess();
		}

		inline void BindForDraw() const
		{
			BufferObject.BindForDraw();
		}

		inline void Unbind() const
		{
			BufferObject.Unbind();
		}

		inline void SetItem(size_t Index, const T& item)
		{
			if (Capacity <= Index)
			{
				Reserve(Index + 1);
				BindForDataAccess();
			}
			if (Count <= Index) Count = Index + 1;
			BufferObject->SetData(Index * sizeof(T), sizeof(T), &item);
		}

		inline void SetItems(size_t Index, size_t ItemCount, const T* Ptr)
		{
			size_t RequiredCapacity = Index + ItemCount;
			if (Capacity < RequiredCapacity)
			{
				Reserve(RequiredCapacity);
			}
			if (Count < RequiredCapacity) Count = RequiredCapacity;
			BufferObject->SetData(Index * sizeof(T), ItemCount * sizeof(T), Ptr);
		}

		inline T GetItem(size_t index) const
		{
			if (index >= Capacity) return T();
			T ret;
			BufferObject->GetData(static_cast<size_t>(index) * sizeof(T), sizeof(T), &ret);
			return ret;
		}

		inline size_t GetCount() const
		{
			return Count;
		}

		inline size_t GetCapacity() const
		{
			return Capacity;
		}

		inline void Resize(size_t NewCount)
		{
			if (NewCount < Count)
			{
				size_t Decre = Count - NewCount;
				T* ptr = static_cast<T*>(BufferObject->MapRO(NewCount * sizeof(T), Decre * sizeof(T)));
				for (size_t i = 0; i < Decre; i++) ptr[i].~T();
				BufferObject->Unmap();
				Count = NewCount;
				return;
			}
			if (NewCount > Count)
			{
				if (NewCount > Capacity)
				{
					Reserve(NewCount);
					BindForDataAccess();
				}
				size_t Incre = NewCount - Count;
				T* ptr = static_cast<T*>(BufferObject->MapWO(Count * sizeof(T), Incre * sizeof(T)));
				for (size_t i = 0; i < Incre; i++) ptr[i] = T();
				BufferObject->Unmap();
				Count = NewCount;
				return;
			}
		}

		inline void Reserve(size_t NewCapacity)
		{
			if (Capacity >= NewCapacity) return;
			if (BufferObject.IsEmpty())
				BufferObject.SetBufferObject(std::make_shared<GLBufferObject>(Type, NewCapacity * sizeof(T), Usage));
			else
				BufferObject.SetBufferObject(std::make_shared<GLBufferObject>(*BufferObject, NewCapacity * sizeof(T), GetCount() * sizeof(T)));
			Capacity = NewCapacity;
		}

		inline void Clear()
		{
			Count = 0;
		}

		inline void ShrinkToFit()
		{
			if (!BufferObject) return;
			size_t NewSize = Count * sizeof(T);
			if (BufferObject->GetLength() != NewSize)
			{
				BufferObject.SetBufferObject(std::make_shared<GLBufferObject>(*BufferObject, NewSize));
			}
		}

		inline void PushBack(const T& item)
		{
			if (Count >= Capacity) Reserve(Capacity * 3 / 2 + 1);
			BindForDataAccess();
			SetItem(Count++, item);
			Unbind();
		}

		inline void PushBack(const T* Items, size_t ItemCount)
		{
			size_t NewCapacity = Capacity;
			size_t RequiredCapacity = Capacity + ItemCount;
			while (NewCapacity < RequiredCapacity) NewCapacity = NewCapacity * 3 / 2 + 1;
			Reserve(NewCapacity);
			BindForDataAccess();
			SetItems(Count, ItemCount, Items);
			Unbind();
		}

		inline void PushBack(const std::vector<T>& items)
		{
			PushBack(&items[0], items.size());
		}

		inline T PopBack()
		{
			if (!Count) return T();
			size_t LastIndex = Count - 1;
			BindForDataAccess();
			T ret = GetItem(LastIndex);
			Resize(LastIndex);
			Unbind();
			return ret;
		}

		inline T operator [] (ptrdiff_t index) const
		{
			BindForDataAccess();
			return GetItem(index);
			Unbind();
		}

		inline GLBufferIterator<T> operator [] (ptrdiff_t index);
	};

	template<typename T>
	class GLBufferIterator
	{
		using Container = GLBufferVector<T>;
		using Iterator = GLBufferIterator<T>;

	protected:
		Container& Buffer;
		ptrdiff_t Index;

	public:
		GLBufferIterator(Container& Buffer, ptrdiff_t Index) : Buffer(Buffer), Index(Index) {}
		Iterator& operator++() { ++Index; return *this; }
		Iterator operator++(int) { return Iterator(Buffer, Index++); }
		T& operator*() const { return Buffer[Index]; }
		T* operator->() const { return &Buffer[Index]; }
		Iterator operator +(ptrdiff_t v) const { return Iterator(Buffer, Index + v); }
		bool operator==(const Iterator& r) const { return r.Buffer == Buffer && r.Index == Index; }
		bool operator!=(const Iterator& r) const { return r.Buffer != Buffer || r.Index != Index; }

		GLBufferIterator (const Iterator& i) = default;
		Iterator& operator =(const Iterator& i) = default;
		Iterator& operator =(T& i) { Buffer.BindForDataAccess(); Buffer.SetItem(Index, i); Buffer.Unbind(); return *this; }
	};

	template<typename T>
	class GLBufferConstIterator
	{
		using Container = GLBufferVector<T>;
		using Iterator = GLBufferConstIterator<T>;

	protected:
		const Container& Buffer;
		ptrdiff_t Index;

	public:
		GLBufferConstIterator(const Container& Buffer, ptrdiff_t Index) : Buffer(Buffer), Index(Index) {}
		Iterator& operator++() { ++Index; return *this; }
		Iterator operator++(int) { return Iterator(Buffer, Index++); }
		const T& operator*() const { return Buffer[Index]; }
		const T* operator->() const { return &Buffer[Index]; }
		Iterator operator +(ptrdiff_t v) const { return Iterator(Buffer, Index + v); }
		bool operator==(const Iterator& r) const { return r.Buffer == Buffer && r.Index == Index; }
		bool operator!=(const Iterator& r) const { return r.Buffer != Buffer || r.Index != Index; }
	};

	template<typename T>
	inline GLBufferIterator<T> GLBufferVector<T>::operator [] (ptrdiff_t index)
	{
		return GLBufferIterator(*this, index);
	}

	extern template GLBufferVector<GLubyte>;
	extern template GLBufferVector<GLushort>;
	extern template GLBufferVector<GLuint>;
}
