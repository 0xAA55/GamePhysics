#pragma once
#include<GLRendererBase.hpp>
#include<unordered_map>
#include<GLBuffer.hpp>
#include<GLShader.hpp>
#include<type_traits>
namespace GLRenderer
{
	class AttribDesc;

	enum class MeshPrimitiveType
	{
		Points = 0x0000,
		Lines = 0x0001,
		LineLoop = 0x0002,
		LineStrip = 0x0003,
		Triangles = 0x0004,
		TriangleStrip = 0x0005,
		TriangleFan = 0x0006,
		Quads = 0x0007,
		QuadStrip = 0x0008,
		Polygon = 0x0009
	};

	enum class MeshElementType
	{
		UnsignedByte = 0x1401,
		UnsignedShort = 0x1403,
		UnsignedInt = 0x1405
	};

	template<MeshElementType Type> struct TypeOfElement_s;
	template<> struct TypeOfElement_s<MeshElementType::UnsignedByte> { using Type = GLubyte; };
	template<> struct TypeOfElement_s<MeshElementType::UnsignedShort> { using Type = GLushort; };
	template<> struct TypeOfElement_s<MeshElementType::UnsignedInt> { using Type = GLuint; };
	template<MeshElementType Type> using TypeOfElement = typename TypeOfElement_s<Type>::Type;

	class DrawCommand
	{
	public:
		GLuint VertexCount;
		GLuint InstanceCount;
		GLuint FirstVertex;
		GLuint BaseInstance;
	};

	class GLVAO
	{
	protected:
		GLuint VAO;
		bool Described;

	public:
		GLVAO();
		~GLVAO();

		inline operator GLuint() const { return VAO; }
		inline bool IsDescribed() const { return Described; }
		inline void SetDescribed() { Described = true; }

		void Bind() const;
		void Draw(MeshPrimitiveType PrimitiveType, GLsizei CommandCount) const;
		void Draw(MeshPrimitiveType PrimitiveType, GLsizei VertexCount, GLsizei InstanceCount) const;
		void DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei CommandCount) const;
		void DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei VertexCount, GLsizei InstanceCount) const;
	};

	template<
		typename VertexType,
		typename InstanceType,
		MeshElementType ElementType = MeshElementType::UnsignedInt,
		bool VertexBufferUseCachedBuffer = true,
		bool IndexBufferUseCachedBuffer = true,
		bool InstanceBufferUseCachedBuffer = true,
		bool CommandBufferUseCachedBuffer = true>
	class GLMesh
	{
	protected:
		using IndexType = TypeOfElement<ElementType>;
		using VertexBufferType = std::conditional_t<VertexBufferUseCachedBuffer, GLBuffer<VertexType>, GLBufferNoCache<VertexType>>;
		using IndexBufferType = std::conditional_t<IndexBufferUseCachedBuffer, GLBuffer<IndexType>, GLBufferNoCache<IndexType>>;
		using InstanceBufferType = std::conditional_t<InstanceBufferUseCachedBuffer, GLBuffer<InstanceType>, GLBufferNoCache<InstanceType>>;
		using CommandBufferType = std::conditional_t<CommandBufferUseCachedBuffer, GLBuffer<DrawCommand>, GLBufferNoCache<DrawCommand>>;
		using AttribDescArray = std::vector<AttribDesc>;
		using VAOContainer = std::unordered_map<GLShaderProgram, GLVAO, GLShaderProgramHasher>;

		VAOContainer VAOsForEachShader;
		GLVAO& Describe(const GLShaderProgram &Shader)
		{
			VertexBuffer.WatchForObjectChanged();
			InstanceBuffer.WatchForObjectChanged();
			VertexBuffer.Flush();
			InstanceBuffer.Flush();
			bool ShouldDescribe = VertexBuffer.CheckObjectChanged() || InstanceBuffer.CheckObjectChanged();
			GLVAO &VAO = VAOsForEachShader[Shader];
			if (!VAO.IsDescribed()) ShouldDescribe = true;
			VAO.Bind();
			if (ShouldDescribe)
			{
				if (VertexBuffer.Size())
				{
					GLsizei LastOffset = 0;
					VertexBuffer.Bind();
					for (auto &it : VertexBufferFormat)
					{
						if (it.Offset == -1) it.Offset = LastOffset;
						LastOffset = it.Offset + it.GetSizeBytes();
						it.Describe(Shader, sizeof(VertexType), 0);
					}
					VertexBuffer.Unbind();
				}
				if (InstanceBuffer.Size())
				{
					GLsizei LastOffset = 0;
					InstanceBuffer.Bind();
					for (auto &it : InstanceBufferFormat)
					{
						if (it.Offset == -1) it.Offset = LastOffset;
						LastOffset = it.Offset + it.GetSizeBytes();
						it.Describe(Shader, sizeof(InstanceType), 1);
					}
					InstanceBuffer.Unbind();
				}
				VAO.SetDescribed();
			}
			return VAO;
		}

	public:
		VertexBufferType VertexBuffer;
		IndexBufferType IndexBuffer;
		InstanceBufferType InstanceBuffer;
		CommandBufferType CommandBuffer;
		AttribDescArray VertexBufferFormat;
		AttribDescArray InstanceBufferFormat;
		MeshPrimitiveType PrimitiveType;

		GLMesh(MeshPrimitiveType PrimitiveType) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLMesh(MeshPrimitiveType PrimitiveType, const std::vector<VertexType> &VertexData) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw, VertexData),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLMesh(MeshPrimitiveType PrimitiveType, const std::vector<IndexType> &IndexData) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw, IndexData),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLMesh(MeshPrimitiveType PrimitiveType, const std::vector<VertexType> &VertexData, const std::vector<IndexType> &IndexData) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw, VertexData),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw, IndexData),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLMesh(const GLMesh &CopyFrom) :
			PrimitiveType(CopyFrom.PrimitiveType),
			VertexBufferFormat(CopyFrom.VertexBufferFormat),
			InstanceBufferFormat(CopyFrom.InstanceBufferFormat),
			VertexBuffer(CopyFrom.VertexBuffer),
			IndexBuffer(CopyFrom.IndexBuffer),
			InstanceBuffer(CopyFrom.InstanceBuffer),
			CommandBuffer(CopyFrom.DrawIndirectBuffer)
		{
		}

		void Draw(const GLShaderProgram &Shader)
		{
			Shader.Use();
			auto &VAO = Describe(Shader);
			if (IndexBuffer.Size())
			{
				IndexBuffer.Bind();
				if (CommandBuffer.Size())
				{
					CommandBuffer.Bind();
					VAO.DrawByElements(PrimitiveType, ElementType, static_cast<GLsizei>(CommandBuffer.Size()));
					CommandBuffer.Unbind();
				}
				else VAO.DrawByElements(PrimitiveType, ElementType, static_cast<GLsizei>(IndexBuffer.Size()), static_cast<GLsizei>(InstanceBuffer.Size()));
				IndexBuffer.Unbind();
			}
			else
			{
				if (CommandBuffer.Size())
				{
					CommandBuffer.Bind();
					VAO.Draw(PrimitiveType, static_cast<GLsizei>(CommandBuffer.Size()));
					CommandBuffer.Unbind();
				}
				else VAO.Draw(PrimitiveType, static_cast<GLsizei>(VertexBuffer.Size()), static_cast<GLsizei>(InstanceBuffer.Size()));
			}
			Shader.Unuse();
		}
	};

	class AttribDesc
	{
	public:
		std::string Name;
		AttribType Type;
		GLVarType VarType;
		GLsizei Offset; // If `Offset` is -1, it means the offset should be calculated automatically.
		int ColCount; // e.g. vec2, vec3, vec4
		int RowCount; // e.g. mat4x2, mat4x3, mat4x4
		int Length;
		bool AsFloat;
		bool Normalize;

		AttribDesc(std::string Name, AttribType Type, GLsizei Offset = -1, bool AsFloat = true, bool Normalize = false);
		AttribDesc(std::string Name, std::string Type, GLsizei Offset = -1, bool AsFloat = true, bool Normalize = false);

		void Describe(const GLShaderProgram &Shader, GLsizei Stride, GLuint AVD) const;
		inline GLsizei GetSizeBytes() const { return GLGetNumUnits(Type) * GLGetUnitLength(Type); }
	};

	class WaveFrontObjVertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoord;
	};

	extern template GLBuffer<WaveFrontObjVertex>;
	extern template GLBuffer<DrawCommand>;
	extern template GLBufferNoCache<WaveFrontObjVertex>;
	extern template GLBufferNoCache<DrawCommand>;

	extern template GLBuffer<GLubyte>;
	extern template GLBuffer<GLushort>;
	extern template GLBuffer<GLuint>;

	extern template GLBufferNoCache<GLubyte>;
	extern template GLBufferNoCache<GLushort>;
	extern template GLBufferNoCache<GLuint>;

	template <typename InstanceType, MeshElementType ElementType = MeshElementType::UnsignedInt, bool VertexBufferUseCachedBuffer = true, bool IndexBufferUseCachedBuffer = true, bool InstanceBufferUseCachedBuffer = true, bool CommandBufferUseCachedBuffer = true>
	using GLObjMesh = GLMesh<WaveFrontObjVertex, InstanceType, ElementType, VertexBufferUseCachedBuffer, IndexBufferUseCachedBuffer, InstanceBufferUseCachedBuffer, CommandBufferUseCachedBuffer>;
}
