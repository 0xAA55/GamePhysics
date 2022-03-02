#pragma once
#include<GLRendererBase.hpp>
#include<unordered_map>
#include<GLBuffer.hpp>
#include<GLShader.hpp>
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

		operator GLuint() const;
		void Bind() const;
		bool IsDescribed() const;
		void SetDescribed();
		void Draw(MeshPrimitiveType PrimitiveType, GLsizei CommandCount) const;
		void Draw(MeshPrimitiveType PrimitiveType, GLsizei VertexCount, GLsizei InstanceCount) const;
		void DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei CommandCount) const;
		void DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei VertexCount, GLsizei InstanceCount) const;
	};

	template<typename VertexType, typename InstanceType, MeshElementType ElementType = MeshElementType::UnsignedInt>
	class GLMesh
	{
	protected:
		using IndexType = TypeOfElement<ElementType>;
		using VertexBufferType = GLBuffer<VertexType>;
		using IndexBufferType = GLBuffer<IndexType>;
		using InstanceBufferType = GLBuffer<InstanceType>;
		using CommandBufferType = GLBuffer<DrawCommand>;
		using AttribDescArray = std::vector<AttribDesc>;
		using VAOContainer = std::unordered_map<GLShaderProgram, GLVAO, GLShaderProgramHasher>;

		VAOContainer VAOsForEachShader;
		GLVAO& Describe(const GLShaderProgram &Shader);

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

	template<typename VertexType, typename InstanceType, MeshElementType ElementType>
	GLVAO &GLMesh<VertexType, InstanceType, ElementType>::Describe(const GLShaderProgram &Shader)
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
				VertexBuffer.Bind();
				for (auto &it : VertexBufferFormat) it.Describe(Shader, sizeof(VertexType), 0);
				VertexBuffer.Unbind();
			}
			if (InstanceBuffer.Size())
			{
				InstanceBuffer.Bind();
				for (auto &it : InstanceBufferFormat) it.Describe(Shader, sizeof(InstanceType), 1);
				InstanceBuffer.Unbind();
			}
			VAO.SetDescribed();
		}
		return VAO;
	}

	class AttribDesc
	{
	public:
		std::string Name;
		AttribType Type;
		AttribUnitType UnitType;
		GLsizei Offset;
		int ColCount; // e.g. vec2, vec3, vec4
		int RowCount; // e.g. mat4x2, mat4x3, mat4x4
		int Length;
		bool AsFloat;
		bool Normalize;

		AttribDesc(std::string Name, AttribType Type, GLsizei Offset, bool AsFloat = true, bool Normalize = false);
		AttribDesc(std::string Name, std::string Type, GLsizei Offset, bool AsFloat = true, bool Normalize = false);

		void Describe(const GLShaderProgram &Shader, GLsizei Stride, GLuint AVD) const;
	};
}
