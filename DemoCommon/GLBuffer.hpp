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

	class GLBufferOwnership
	{
	protected:
		GLBufferObject* BufferObject;

	public:
		bool ObjectChanged;

		inline GLBufferOwnership() noexcept  :
			ObjectChanged(false),
			BufferObject(nullptr)
		{}

		inline GLBufferOwnership(GLBufferObject * BufferObject) noexcept :
			ObjectChanged(false),
			BufferObject(BufferObject)
		{}

		inline GLBufferOwnership(const GLBufferOwnership& CopyFrom) noexcept :
			ObjectChanged(false),
			BufferObject(CopyFrom.BufferObject)
		{}

		inline ~GLBufferOwnership() noexcept
		{
			Discard();
		}

		inline GLBufferOwnership &operator =(GLBufferObject *BufferObject)
		{
			this->BufferObject = BufferObject;
			ObjectChanged = true;
			return *this;
		}

		inline operator GLBufferObject() const noexcept { return *BufferObject; }
		inline GLBufferObject &operator *() const noexcept { return *BufferObject; }
		inline GLBufferObject *operator ->() const noexcept { return BufferObject; }
		inline GLBufferObject *Get() const noexcept { return BufferObject; }
		inline operator bool() const noexcept { return BufferObject ? true : false; }

		inline void Discard() noexcept
		{
			BufferObject = nullptr;
			ObjectChanged = true;
		}

		inline bool Empty() const noexcept
		{
			return BufferObject == nullptr;
		}
	};

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
	class GLBufferVector;

	template<typename T>
	class GLBufferVectorNC;

	template<typename T>
	class GLBufferVector
	{
	public:
		using VectorWithoutCache = GLBufferVectorNC<T>;
		using VectorType = std::vector<T>;
		using BoolVecType = std::vector<bool>;
		using SizeType = typename VectorType::size_type;
		using DifferenceType = typename VectorType::difference_type;
		using Iterator = GLBufferIterator<T>;
		using ConstIterator = GLBufferConstIterator<T>;

	protected:
		BufferUsage Usage;

		GLBufferOwnership BufferObject;
		VectorType Contents;

		BoolVecType Updated;
		DifferenceType Updated_MinIndex;
		DifferenceType Updated_MaxIndex;
		bool Flushed;

		void SetFlushed()
		{
			Updated.clear();
			Updated.resize(Size(), false);
			Updated_MinIndex = -1;
			Updated_MaxIndex = -1;
			Flushed = true;
		}

	public:
		BufferType Type;
		const SizeType FlushingGap = 16;

		GLBufferVector() = delete;
		GLBufferVector(BufferType Type, BufferUsage Usage) :
			Type(Type),
			Usage(Usage),
			BufferObject(nullptr),
			Contents(),
			Updated(),
			Updated_MinIndex(-1),
			Updated_MaxIndex(-1),
			Flushed(false)
		{
		}

		GLBufferVector(const GLBufferVector &CopyFrom) :
			Type(CopyFrom.Type),
			Usage(CopyFrom.Usage),
			BufferObject(CopyFrom.BufferObject),
			Contents(CopyFrom.Contents),
			Updated(CopyFrom.Updated),
			Updated_MinIndex(CopyFrom.Updated_MinIndex),
			Updated_MaxIndex(CopyFrom.Updated_MaxIndex),
			Flushed(CopyFrom.Flushed)
		{
		}

		GLBufferVector(BufferType Type, BufferUsage Usage, const std::vector<T>& Data) :
			Type(Type),
			Usage(Usage),
			BufferObject(nullptr),
			Contents(Data),
			Updated(),
			Updated_MinIndex(0),
			Updated_MaxIndex(Data.size() - 1),
			Flushed(false)
		{
			Updated.clear();
			Updated.resize(Size(), true);
		}

		GLBufferVector &operator =(const GLBufferVector &CopyFrom)
		{
			Type = CopyFrom.Type;
			Usage = CopyFrom.Usage;

			BufferObject = CopyFrom.BufferObject;
			Contents = CopyFrom.Contents;

			Updated = CopyFrom.Updated;
			Updated_MinIndex = CopyFrom.Updated_MinIndex;
			Updated_MaxIndex = CopyFrom.Updated_MaxIndex;
			Flushed = CopyFrom.Flushed;
			return *this;
		}

		inline void SetUpdated(DifferenceType index)
		{
			if (Updated_MinIndex == -1 || Updated_MinIndex > index) Updated_MinIndex = index;
			if (Updated_MaxIndex == -1 || Updated_MaxIndex < index) Updated_MaxIndex = index;
			Updated[index] = true;
			Flushed = false;
		}

		inline void SetItem(DifferenceType index, const T &item)
		{
			SetUpdated(index);
			Contents[index] = item;
		}

		inline T GetItem(DifferenceType index) const
		{
			return Contents[index];
		}

		inline T &GetItem(DifferenceType index)
		{
			SetUpdated(index);
			return Contents[index];
		}

		inline bool Empty() const
		{
			return Size() == 0;
		}

		inline SizeType Size() const
		{
			return Contents.size();
		}

		inline SizeType Capacity() const
		{
			return Contents.capacity();
		}

		inline void Resize(SizeType Count)
		{
			Contents.resize(Count);
			Updated.resize(Count, true);
			BufferObject = new GLBufferObject(*BufferObject, Capacity() * sizeof(T), Count * sizeof(T));
		}

		inline void Resize(SizeType Count, const T& Value)
		{
			Contents.resize(Count, Value);
			Updated.resize(Count, true);
			BufferObject = new GLBufferObject(*BufferObject, Capacity() * sizeof(T), Count * sizeof(T));
		}

		inline void Reserve(SizeType NewCapacity)
		{
			Contents.reserve(NewCapacity);
			Updated.reserve(NewCapacity);
			BufferObject = new GLBufferObject(*BufferObject, Capacity() * sizeof(T), Size() * sizeof(T));
		}

		inline void Clear()
		{
			Contents.clear();
			Updated.clear();
		}

		inline void ShrinkToFit()
		{
			Contents.shrink_to_fit();
			Updated.shrink_to_fit();
			SizeType SizeBytes = Size() * sizeof(T);
			SizeType CapacityBytes = Capacity() * sizeof(T);
			if (!BufferObject.Empty())
			{
				if (BufferObject->GetLength() != CapacityBytes)
				{
					BufferObject = new GLBufferObject(*BufferObject, SizeBytes);
					Flushed = false;
				}
			}
		}

		inline void PushBack(const T &item)
		{
			Contents.push_back(item);
			Updated.push_back(true);
			Flushed = false;
		}

		inline void PushBack(const T items[], SizeType Count)
		{
			for (SizeType i = 0; i < Count; i++)
			{
				Contents.push_back(items[i]);
				Updated.push_back(true);
			}
			Flushed = false;
		}

		inline void PushBack(const std::vector<T> &items)
		{
			SizeType Count = items.size();
			for (SizeType i = 0; i < Count; i++)
			{
				Contents.push_back(items[i]);
				Updated.push_back(true);
			}
			Flushed = false;
		}

		inline void WatchForObjectChanged() noexcept
		{
			BufferObject.ObjectChanged = false;
		}

		inline bool CheckObjectChanged() const
		{
			return BufferObject.ObjectChanged;
		}

		inline void Bind()
		{
			Flush();
			if (!BufferObject.Empty()) BufferObject->Bind();
		}

		inline void Unbind()
		{
			if (!BufferObject.Empty()) BufferObject->Unbind();
		}

		inline T operator [] (SizeType index) const
		{
			return Contents[index];
		}

		inline T &operator [] (SizeType index)
		{
			SetUpdated(index);
			return Contents[index];
		}

		inline BufferUsage GetUsage() const
		{
			return Usage;
		}

		void Flush()
		{
			if (Flushed) return;
			if (!Size())
			{
				BufferObject.Discard();
				return;
			}
			SizeType SizeBytes = Size() * sizeof(T);
			SizeType CapacityBytes = Capacity() * sizeof(T);
			if (!BufferObject.Empty())
			{
				if (BufferObject->GetLength() != CapacityBytes)
				{
					BufferObject = new GLBufferObject(*BufferObject, SizeBytes);
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
				BufferObject->Bind();
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
								BufferObject->SetData(Offset, BlockLengthBytes, &Contents[BlockBegin]);
							}
						}
					}
				}
				if (IsInBlock)
				{
					Offset = BlockBegin * sizeof(T);
					BlockLengthBytes = (BlockEnd + 1 - BlockBegin) * sizeof(T);
					BufferObject->SetData(Offset, BlockLengthBytes, &Contents[BlockBegin]);
				}
				BufferObject->Unbind();
				SetFlushed();
			}
			else
			{
				BufferObject = new GLBufferObject(Type, CapacityBytes, Usage);
				BufferObject->Bind();
				BufferObject->SetData(Contents.data());
				BufferObject->Unbind();
				SetFlushed();
				return;
			}
		}

		GLBufferObject *GetBufferObject()
		{
			Flush();
			return BufferObject.Get();
		}

		template<typename T2> GLBufferVector<T2> ReinterpretCast(BufferType Type, BufferUsage Usage) const
		{
			GLBufferVector<T2> Ret(Type, Usage);
			SizeType SizeBytes = Size() * sizeof(T);
			if (SizeBytes % sizeof(T2))
			{
				throw BufferCastingError("Element count not divisible.");
			}
			SizeType UnitCount = SizeBytes / sizeof(T2);
			Ret.Resize(UnitCount);
			std::memcpy(Ret.Contents.data(), Contents.data(), SizeBytes);
			Ret.Flush();
			return Ret;
		}

		template<typename T2> GLBufferVector<T2> StaticCast(BufferType Type, BufferUsage Usage) const
		{
			GLBufferVector<T2> Ret(Type, Usage);
			SizeType Count = Size();
			Ret.Resize(Count);
			for (SizeType i = 0; i < Count; i++)
			{
				Ret[i] = static_cast<T2>(Contents[i]);
			}
			Ret.Flush();
			return Ret;
		}

		template<typename T2> GLBufferVector<T2> DynamicCast(BufferType Type, BufferUsage Usage) const
		{
			GLBufferVector<T2> Ret(Type, Usage);
			SizeType Count = Size();
			Ret.Resize(Count);
			for (SizeType i = 0; i < Count; i++)
			{
				Ret[i] = dynamic_cast<T2>(Contents[i]);
			}
			Ret.Flush();
			return Ret;
		}
	};

	template<typename T>
	class GLBufferIterator
	{
		using Container = GLBufferVector<T>;
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
		using Container = GLBufferVector<T>;
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
	class GLBufferVectorNC
	{
	public:
		using VectorWithCache = GLBufferVector<T>;
		using SizeType = typename VectorWithCache::SizeType;
		using DifferenceType = typename VectorWithCache::DifferenceType;

	protected:
		BufferUsage Usage;

		GLBufferOwnership BufferObject;
		SizeType ItemCount;
		SizeType ItemCapacity;

	public:
		BufferType Type;

		GLBufferVectorNC() = delete;
		GLBufferVectorNC(BufferType Type, BufferUsage Usage, SizeType InitCapacity = 32) :
			Type(Type),
			Usage(Usage),
			ItemCount(0),
			ItemCapacity(InitCapacity),
			BufferObject(new GLBufferObject(Type, InitCapacity * sizeof(T), Usage))
		{
		}
		GLBufferVectorNC(BufferType Type, BufferUsage Usage, const std::vector<T>& Data) :
			Type(Type),
			Usage(Usage),
			ItemCount(Data.size()),
			ItemCapacity(Data.capacity()),
			BufferObject(new GLBufferObject(Type, Data.capacity() * sizeof(T), Usage))
		{
			BufferObject->Bind();
			BufferObject->SetData(0, ItemCount * sizeof(T), Data.data());
		}
		GLBufferVectorNC(const GLBufferVectorNC &From) :
			Type(From.Type),
			Usage(From.Usage),
			ItemCount(From.Size()),
			ItemCapacity(From.Capacity()),
			BufferObject(new GLBufferObject(From.Type, From.Capacity() * sizeof(T), From.Usage, *From.BufferObject))
		{
		}
		GLBufferVectorNC(VectorWithCache &From) :
			Type(From.Type),
			Usage(From.GetUsage()),
			ItemCount(From.Size()),
			ItemCapacity(From.Capacity())
		{
			BufferObject = new GLBufferObject(From.Type, From.Capacity() * sizeof(T), From.GetUsage(), *From.GetBufferObject());
		}

		inline SizeType Size() const noexcept
		{
			return ItemCount;
		}

		inline SizeType Capacity() const noexcept
		{
			return ItemCapacity;
		}

		inline bool Empty() const noexcept
		{
			return Size() == 0;
		}

		inline void SetItem(DifferenceType Index, const T &Item) noexcept
		{
			BufferObject->Bind();
			BufferObject->SetData(Index * sizeof(T), sizeof(T), &Item);
		}

		inline T GetItem(DifferenceType Index) const noexcept
		{
			T Ret;
			BufferObject->Bind();
			BufferObject->GetData(Index * sizeof(T), sizeof(T), &Ret);
			return Ret;
		}

		inline void Reserve(SizeType NewCapacity)
		{
			if (NewCapacity <= ItemCapacity) return;
			BufferObject = new GLBufferObject(*BufferObject, NewCapacity * sizeof(T), ItemCount * sizeof(T));
			ItemCapacity = NewCapacity;
		}

		inline void Resize(SizeType Count, const T &Value)
		{
			if (ItemCapacity < Count) Reserve(Count);
			if (Count > ItemCount)
			{
				size_t MapSize = Count - ItemCount;
				BufferObject->Bind();
				T *MapPointer = static_cast<T *>(BufferObject->MapWO(ItemCount * sizeof(T), MapSize * sizeof(T)));
				for (size_t i = 0; i < MapSize; i++) MapPointer[ItemCount + i] = Value;
				BufferObject->Unmap();
			}
			ItemCount = Count;
		}

		inline void Resize(SizeType Count)
		{
			Resize(Count, T());
		}

		inline void Clear()
		{
			ItemCount = 0;
		}

		inline void ShrinkToFit()
		{
			if (ItemCapacity > ItemCount)
			{
				ItemCapacity = ItemCount;
				BufferObject = new GLBufferObject(*BufferObject, ItemCount * sizeof(T));
			}
		}

		inline void PushBack(const T &item)
		{
			size_t Index = ItemCount;
			if (ItemCount++ >= ItemCapacity) Reserve(ItemCapacity * 3 / 2 + 1);
			SetItem(Index, item);
		}

		inline void PushBack(const T Items[], SizeType Count)
		{
			if (!Count) return;

			size_t TotalSize = ItemCount + Count;
			if (TotalSize > ItemCapacity)
			{
				size_t NewCap = ItemCapacity * 3 / 2 + 1;
				if (NewCap < TotalSize) NewCap = TotalSize;
				Reserve(NewCap);
			}
			BufferObject->Bind();
			BufferObject->SetData(ItemCount * sizeof(T), Count * sizeof(T), &Items[0]);
			ItemCount = TotalSize;
		}

		inline void PushBack(const std::vector<T> &items)
		{
			PushBack(items.data(), items.size());
		}

		inline void WatchForObjectChanged() noexcept
		{
			BufferObject.ObjectChanged = false;
		}

		inline bool CheckObjectChanged() const
		{
			return BufferObject.ObjectChanged;
		}

		inline void Bind()
		{
			BufferObject->Bind();
		}

		inline void Unbind()
		{
			BufferObject->Unbind();
		}

		inline const T operator [] (SizeType index) const
		{
			return GetItem(index);
		}

		inline BufferUsage GetUsage() const
		{
			return Usage;
		}

		inline void Flush()
		{
		}

		GLBufferObject *GetBufferObject()
		{
			return BufferObject.Get();
		}

		// returns actual copied data size
		inline SizeType GetAllData(T *Buffer, SizeType BufferSize)
		{
			SizeType CopySize = min(BufferSize, Size() * sizeof(T));
			BufferObject->GetData(0, CopySize, Buffer);
			return CopySize;
		}

		template<typename T2> GLBufferVectorNC<T2> ReinterpretCast(BufferType Type, BufferUsage Usage) const
		{
			SizeType SizeBytes = Size() * sizeof(T);
			if (SizeBytes % sizeof(T2))
			{
				throw BufferCastingError("Element count not divisible.");
			}
			SizeType UnitCount = SizeBytes / sizeof(T2);
			GLBufferVectorNC<T2> Ret(Type, Usage, UnitCount);
			Ret.BufferObject = new GLBufferObject(Type, SizeBytes, Usage, BufferObject, SizeBytes);
			Ret.ItemCount = UnitCount;
			return Ret;
		}

		template<typename T2> GLBufferVectorNC<T2> StaticCast(BufferType Type, BufferUsage Usage) const
		{
			SizeType Count = Size();
			GLBufferVector<T2> Ret(Type, Usage, Count);
			Ret.Resize(Count);
			Ret.BufferObject->Bind();
			T2 *MapPtr = Ret.BufferObject->MapWO();
			BufferObject->Bind();
			for (SizeType i = 0; i < Count; i++)
			{
				MapPtr[i] = static_cast<T2>(GetItem(i));
			}
			Ret.BufferObject->Bind();
			Ret.BufferObject->Unmap();
			return Ret;
		}

		template<typename T2> GLBufferVectorNC<T2> DynamicCast(BufferType Type, BufferUsage Usage) const
		{
			SizeType Count = Size();
			GLBufferVector<T2> Ret(Type, Usage, Count);
			Ret.Resize(Count);
			Ret.BufferObject->Bind();
			T2 *MapPtr = Ret.BufferObject->MapWO();
			BufferObject->Bind();
			for (SizeType i = 0; i < Count; i++)
			{
				MapPtr[i] = dynamic_cast<T2>(GetItem(i));
			}
			Ret.BufferObject->Bind();
			Ret.BufferObject->Unmap();
			return Ret;
		}

		class GLBufferNoCacheWriter
		{
		protected:
			GLBufferVectorNC &Buffer;
			DifferenceType Index;
			T Value;

		public:
			GLBufferNoCacheWriter() = delete;
			inline GLBufferNoCacheWriter(GLBufferVectorNC &Buffer, DifferenceType Index) :
				Buffer(Buffer), Index(Index), Value(Buffer.GetItem(static_cast<SizeType>(Index)))
			{
			}
			inline operator T() const { return Value; }
			inline GLBufferNoCacheWriter &operator =(const T &Other)
			{
				Value = Other;
				Buffer.SetItem(Index, Value);
				return *this;
			}
		};

		inline GLBufferNoCacheWriter operator[] (SizeType index)
		{
			return GLBufferNoCacheWriter(*this, static_cast<DifferenceType>(index));
		}
	};
}
