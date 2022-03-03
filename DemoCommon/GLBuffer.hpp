#pragma once
#include<GLRendererBase.hpp>
#include<vector>
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

		static std::unordered_map<BufferType, GLuint> BufferBindings;

	public:
		GLBufferObject() = delete;
		GLBufferObject(const GLBufferObject& From) = delete;
		GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage);
		GLBufferObject(BufferType Type, size_t Length, BufferUsage Usage, GLBufferObject &CopyFrom, ptrdiff_t CopyLength = -1);
		~GLBufferObject();

		operator GLuint() const;

		size_t GetLength();

		void *MapRO();
		void *MapWO();
		void *MapRW();
		void *MapRO(size_t Offset, size_t Length);
		void *MapWO(size_t Offset, size_t Length);
		void *MapRW(size_t Offset, size_t Length);
		void Unmap();

		static void Bind(BufferType Type, GLuint BufferObject);
		static void Unbind(BufferType Type);
		inline void Bind() { Bind(Type, Object); }
		inline void Unbind() { Unbind(Type); }
	};

	template<typename T>
	class GLBufferIterator;

	template<typename T>
	class GLBufferConstIterator;

	template<typename T>
	class GLBuffer
	{
	public:
		using VectorType = std::vector<T>;
		using BoolVecType = std::vector<bool>;
		using SizeType = typename VectorType::size_type;
		using DifferenceType = typename VectorType::difference_type;
		using Iterator = GLBufferIterator<T>;
		using ConstIterator = GLBufferConstIterator<T>;

	protected:
		BufferType Type;
		BufferUsage Usage;
		GLBufferObject *BufferObject;
		VectorType Contents;
		BoolVecType Updated;
		DifferenceType Updated_MinIndex;
		DifferenceType Updated_MaxIndex;
		bool Flushed = false;
		void SetFlushed();
		bool ObjectChanged;

	public:
		GLBuffer() = delete;
		GLBuffer(BufferType Type, BufferUsage Usage);
		GLBuffer(const GLBuffer &CopyFrom);
		GLBuffer& operator =(const GLBuffer &CopyFrom);
		~GLBuffer();
		void SetUpdated(DifferenceType index);
		void SetItem(DifferenceType index, const T &item);
		T GetItem(DifferenceType index) const;
		T &GetItem(DifferenceType index);
		bool Empty() const;
		SizeType Size() const;
		SizeType Capacity() const;
		void Resize(SizeType Count);
		void Reserve(SizeType NewCapacity);
		void ShrinkToFit();
		void Clear();
		void PushBack(const T &item);
		void PushBack(const T items[], SizeType Count);
		void PushBack(const std::vector<T>& items);
		void WatchForObjectChanged();
		bool CheckObjectChanged() const;

		const SizeType FlushingGap = 16;

		void Bind();
		void Unbind();
		void Flush();

		T operator [] (SizeType index) const;
		T &operator [] (SizeType index);

		template<typename T2>
		GLBuffer<T2> ReinterpretCast(BufferType Type, BufferUsage Usage) const;

		template<typename T2>
		GLBuffer<T2> StaticCast(BufferType Type, BufferUsage Usage) const;

		template<typename T2>
		GLBuffer<T2> DynamicCast(BufferType Type, BufferUsage Usage) const;
	};

	template<typename T>
	class GLBufferIterator
	{
		using Container = GLBuffer<T>;
		using Iterator = GLBufferIterator<T>;
		using SizeType = typename Container::SizeType;
		using DifferenceType = typename Container::DifferenceType;

	protected:
		Container &Buffer;
		DifferenceType Index;

	public:
		GLBufferIterator(Container &Buffer, DifferenceType Index) : Buffer(Buffer), Index(Index) {}
		Iterator &operator++() { ++Index; return *this; }
		Iterator operator++(int) { return Iterator(Buffer, Index++); }
		T &operator*() const { return Buffer[Index]; }
		T *operator->() const { return &Buffer[Index]; }
		Iterator operator +(DifferenceType v) const { return Iterator(Buffer, Index + v); }
		bool operator==(const Iterator &r) const { return r.Buffer == Buffer && r.Index == Index; }
		bool operator!=(const Iterator &r) const { return r.Buffer != Buffer || r.Index != Index; }
	};

	template<typename T>
	class GLBufferConstIterator
	{
		using Container = GLBuffer<T>;
		using Iterator = GLBufferConstIterator<T>;
		using SizeType = typename Container::SizeType;
		using DifferenceType = typename Container::DifferenceType;

	protected:
		const Container &Buffer;
		DifferenceType Index;

	public:
		GLBufferConstIterator(const Container &Buffer, DifferenceType Index) : Buffer(Buffer), Index(Index) {}
		Iterator &operator++() { ++Index; return *this; }
		Iterator operator++(int) { return Iterator(Buffer, Index++); }
		const T &operator*() const { return Buffer[Index]; }
		const T *operator->() const { return &Buffer[Index]; }
		Iterator operator +(DifferenceType v) const { return Iterator(Buffer, Index + v); }
		bool operator==(const Iterator &r) const { return r.Buffer == Buffer && r.Index == Index; }
		bool operator!=(const Iterator &r) const { return r.Buffer != Buffer || r.Index != Index; }
	};

	template<typename T>
	void GLBuffer<T>::SetFlushed()
	{
		Updated.clear();
		Updated.resize(Size(), false);
		Updated_MinIndex = -1;
		Updated_MaxIndex = -1;
		Flushed = true;
	}

	template<typename T>
	GLBuffer<T>::GLBuffer(BufferType Type, BufferUsage Usage) :
		Type(Type),
		Usage(Usage),
		BufferObject(nullptr),
		Contents(),
		Updated(),
		Updated_MinIndex(-1),
		Updated_MaxIndex(-1),
		Flushed(false),
		ObjectChanged(false)
	{
	}

	template<typename T>
	GLBuffer<T>::GLBuffer(const GLBuffer<T> &CopyFrom) :
		Type(CopyFrom.Type),
		Usage(CopyFrom.Usage),
		BufferObject(nullptr),
		Contents(CopyFrom.Contents),
		Updated(),
		Updated_MinIndex(0),
		Updated_MaxIndex(Size()),
		ObjectChanged(false)
	{
		SizeType Count = Size();
		Updated.reserve(Capacity());
		for (SizeType i = 0; i < Count; i++) Updated.push_back(true);
	}

	template<typename T>
	GLBuffer<T> & GLBuffer<T>::operator =(const GLBuffer &CopyFrom)
	{
		Type = CopyFrom.Type;
		Usage = CopyFrom.Usage;
		if (BufferObject)
		{
			delete BufferObject;
			BufferObject = nullptr;
		}
		Contents = CopyFrom.Contents;
		SizeType Count = Size();
		Updated.reserve(Capacity());
		for (SizeType i = 0; i < Count; i++) Updated.push_back(true);
		Updated_MinIndex = 0;
		Updated_MaxIndex = Count;
	}

	template<typename T>
	GLBuffer<T>::~GLBuffer()
	{
		if (BufferObject) delete BufferObject;
	}

	template<typename T>
	void GLBuffer<T>::SetUpdated(DifferenceType index)
	{
		if (Updated_MinIndex == -1 || Updated_MinIndex > index) Updated_MinIndex = index;
		if (Updated_MaxIndex == -1 || Updated_MaxIndex < index) Updated_MaxIndex = index;
		Updated[index] = true;
		Flushed = false;
	}

	template<typename T>
	void GLBuffer<T>::SetItem(DifferenceType index, const T &item)
	{
		SetUpdated(index);
		Contents[index] = item;
	}

	template<typename T>
	T GLBuffer<T>::GetItem(DifferenceType index) const
	{
		return Contents[index];
	}

	template<typename T>
	T &GLBuffer<T>::GetItem(DifferenceType index)
	{
		SetUpdated(index);
		return Contents[index];
	}

	template<typename T>
	bool GLBuffer<T>::Empty() const
	{
		return Contents.empty();
	}

	template<typename T>
	typename GLBuffer<T>::SizeType GLBuffer<T>::Size() const
	{
		return Contents.size();
	}

	template<typename T>
	typename GLBuffer<T>::SizeType GLBuffer<T>::Capacity() const
	{
		return Contents.capacity();
	}

	template<typename T>
	void GLBuffer<T>::Resize(SizeType Count)
	{
		SizeType PrevCount = Size();
		Contents.resize(Count);
		Updated.resize(Count);
		Flushed = false;
	}

	template<typename T>
	void GLBuffer<T>::Reserve(SizeType NewCapacity)
	{
		Contents.reserve(NewCapacity);
		Updated.reserve(NewCapacity);
		Flushed = false;
	}

	template<typename T>
	void GLBuffer<T>::Clear()
	{
		Contents.clear();
		Updated.clear();
		delete BufferObject;
		BufferObject = nullptr;
		Flushed = false;
	}

	template<typename T>
	void GLBuffer<T>::PushBack(const T &item)
	{
		Contents.push_back(item);
		Updated.push_back(true);
	}

	template<typename T>
	void GLBuffer<T>::PushBack(const T items[], SizeType Count)
	{
		for (SizeType i = 0; i < Count; i++)
		{
			Contents.push_back(items[i]);
			Updated.push_back(true);
		}
	}

	template<typename T>
	void GLBuffer<T>::PushBack(const std::vector<T> &items)
	{
		SizeType Count = items.size();
		for (SizeType i = 0; i < Count; i++)
		{
			Contents.push_back(items[i]);
			Updated.push_back(true);
		}
	}

	template<typename T>
	void GLBuffer<T>::WatchForObjectChanged()
	{
		ObjectChanged = false;
	}

	template<typename T>
	bool GLBuffer<T>::CheckObjectChanged() const
	{
		return ObjectChanged;
	}

	template<typename T>
	void GLBuffer<T>::ShrinkToFit()
	{
		Contents.shrink_to_fit();
		Updated.shrink_to_fit();
		Flushed = false;
		SizeType SizeBytes = Size() * sizeof(T);
		SizeType CapacityBytes = Capacity() * sizeof(T);
		if (BufferObject)
		{
			if (BufferObject->GetLength() != CapacityBytes)
			{
				GLBufferObject *NewObject = new GLBufferObject(Type, CapacityBytes, Usage, *BufferObject, SizeBytes);
				delete BufferObject;
				BufferObject = NewObject;
				ObjectChanged = true;
			}
		}
	}

	template<typename T>
	void GLBuffer<T>::Bind()
	{
		Flush();
		if (BufferObject) BufferObject->Bind();
	}

	template<typename T>
	void GLBuffer<T>::Unbind()
	{
		if (BufferObject) BufferObject->Unbind();
	}

	template<typename T>
	void GLBuffer<T>::Flush()
	{
		if (Flushed) return;
		if (!Size())
		{
			if (BufferObject)
			{
				delete BufferObject;
				BufferObject = nullptr;
				ObjectChanged = true;
			}
			return;
		}
		SizeType SizeBytes = Size() * sizeof(T);
		SizeType CapacityBytes = Capacity() * sizeof(T);
		if (BufferObject)
		{
			if (BufferObject->GetLength() != CapacityBytes)
			{
				GLBufferObject *NewObject = new GLBufferObject(Type, CapacityBytes, Usage, *BufferObject, SizeBytes);
				delete BufferObject;
				BufferObject = NewObject;
				ObjectChanged = true;
			}
			Updated_MinIndex = max(Updated_MinIndex, static_cast<DifferenceType>(0));
			Updated_MaxIndex = min(Updated_MaxIndex, static_cast<DifferenceType>(Size()));
			if (Updated_MaxIndex < 0) Updated_MaxIndex = static_cast<DifferenceType>(Size());
			DifferenceType BlockBegin = 0;
			DifferenceType BlockEnd = 0;
			DifferenceType i;
			bool IsInBlock = false;
			SizeType BlockGap = 0;
			SizeType Offset = 0, BlockLengthBytes = 0;
			for (i = Updated_MinIndex; i <= Updated_MaxIndex; i++)
			{
				if (Updated[i])
				{
					if (!IsInBlock)
					{
						BlockBegin = i;
						IsInBlock = true;
					}
					BlockEnd = i;
					BlockGap = 0;
				}
				else
				{
					if (IsInBlock)
					{
						BlockGap++;
						if (BlockGap > FlushingGap)
						{
							IsInBlock = false;
							Offset = BlockBegin * sizeof(T);
							BlockLengthBytes = (BlockEnd + 1 - BlockBegin) * sizeof(T);
							std::memcpy(BufferObject->MapWO(Offset, BlockLengthBytes), Contents.data(), BlockLengthBytes);
							BufferObject->Unmap();
						}
					}
				}
			}
			if (IsInBlock)
			{
				Offset = BlockBegin * sizeof(T);
				BlockLengthBytes = (BlockEnd + 1 - BlockBegin) * sizeof(T);
				std::memcpy(BufferObject->MapWO(Offset, BlockLengthBytes), Contents.data(), BlockLengthBytes);
				BufferObject->Unmap();
			}
			SetFlushed();
		}
		else
		{
			BufferObject = new GLBufferObject(Type, CapacityBytes, Usage);
			ObjectChanged = true;
			std::memcpy(BufferObject->MapWO(), Contents.data(), SizeBytes);
			BufferObject->Unmap();
			SetFlushed();
			return;
		}
	}

	template<typename T>
	T GLBuffer<T>::operator [] (SizeType index) const
	{
		return Contents[index];
	}

	template<typename T>
	T &GLBuffer<T>::operator [] (SizeType index)
	{
		SetUpdated(index);
		return Contents[index];
	}

	class BufferCastingError : public std::runtime_error
	{
	public:
		BufferCastingError(std::string What) noexcept;
	};

	template<typename T>
	template<typename T2>
	GLBuffer<T2> GLBuffer<T>::ReinterpretCast(BufferType Type, BufferUsage Usage) const
	{
		GLBuffer<T2> Ret(Type, Usage);
		SizeType SizeBytes = Size() * sizeof(T);
		if (SizeBytes % sizeof(T2))
		{
			throw BufferCastingError("Element count not divisible.");
		}
		SizeType UnitCount = SizeBytes / sizeof(T2);
		Ret.Resize(UnitCount);
		std::memcpy(Ret.Contents.data(), Contents.data(), SizeBytes);
		return Ret;
	}

	template<typename T>
	template<typename T2>
	GLBuffer<T2> GLBuffer<T>::StaticCast(BufferType Type, BufferUsage Usage) const
	{
		GLBuffer<T2> Ret(Type, Usage);
		SizeType Count = Size();
		Ret.Resize(Count);
		for (SizeType i = 0; i < Count; i++)
		{
			Ret[i] = static_cast<T2>(Contents[i]);
		}
		return Ret;
	}

	template<typename T>
	template<typename T2>
	GLBuffer<T2> GLBuffer<T>::DynamicCast(BufferType Type, BufferUsage Usage) const
	{
		GLBuffer<T2> Ret(Type, Usage);
		SizeType Count = Size();
		Ret.Resize(Count);
		for (SizeType i = 0; i < Count; i++)
		{
			Ret[i] = dynamic_cast<T2>(Contents[i]);
		}
		return Ret;
	}
}
