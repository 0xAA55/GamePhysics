#pragma once
#include<GLRendererBase.hpp>
#include<unordered_map>
#include<GLBufferVector.hpp>
#include<GLMeshVAO.hpp>
#include<type_traits>
namespace GLRenderer
{
	template<
		typename VertexType,
		typename InstanceType,
		MeshElementType ElementType = MeshElementType::UnsignedInt,
		bool VertexBufferUseCachedBuffer = true,
		bool IndexBufferUseCachedBuffer = true,
		bool InstanceBufferUseCachedBuffer = true,
		bool CommandBufferUseCachedBuffer = true>
	class GLBVMesh
	{
	protected:
		using IndexType = TypeOfElement<ElementType>;
		using VertexBufferType = std::conditional_t<VertexBufferUseCachedBuffer, GLBufferVector<VertexType>, GLBufferVectorNC<VertexType>>;
		using IndexBufferType = std::conditional_t<IndexBufferUseCachedBuffer, GLBufferVector<IndexType>, GLBufferVectorNC<IndexType>>;
		using InstanceBufferType = std::conditional_t<InstanceBufferUseCachedBuffer, GLBufferVector<InstanceType>, GLBufferVectorNC<InstanceType>>;
		using CommandBufferType = std::conditional_t<CommandBufferUseCachedBuffer, GLBufferVector<DrawCommand>, GLBufferVectorNC<DrawCommand>>;
		using AttribDescArray = std::vector<AttribDesc>;

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
						if (it.Stride == -1) it.Stride = sizeof(VertexType);
						LastOffset = it.Offset + it.GetSizeBytes();
						it.Describe(Shader, 0);
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
						if (it.Stride == -1) it.Stride = sizeof(InstanceType);
						LastOffset = it.Offset + it.GetSizeBytes();
						it.Describe(Shader, 1);
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

		GLBVMesh(MeshPrimitiveType PrimitiveType) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLBVMesh(MeshPrimitiveType PrimitiveType, const std::vector<VertexType> &VertexData) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw, VertexData),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLBVMesh(MeshPrimitiveType PrimitiveType, const std::vector<IndexType> &IndexData) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw, IndexData),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLBVMesh(MeshPrimitiveType PrimitiveType, const std::vector<VertexType> &VertexData, const std::vector<IndexType> &IndexData) :
			PrimitiveType(PrimitiveType),
			VertexBuffer(BufferType::ArrayBuffer, BufferUsage::StaticDraw, VertexData),
			IndexBuffer(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw, IndexData),
			InstanceBuffer(BufferType::ArrayBuffer, BufferUsage::StreamDraw),
			CommandBuffer(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw)
		{
		}

		GLBVMesh(const GLBVMesh &CopyFrom) :
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

	class WaveFrontObjVertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoord;
	};

	extern template GLBufferVector<WaveFrontObjVertex>;
	extern template GLBufferVectorNC<WaveFrontObjVertex>;
	extern template GLBufferVector<DrawCommand>;
	extern template GLBufferVectorNC<DrawCommand>;

	template<
		typename InstanceType,
		MeshElementType ElementType = MeshElementType::UnsignedInt,
		bool VertexBufferUseCachedBuffer = false,
		bool IndexBufferUseCachedBuffer = false,
		bool InstanceBufferUseCachedBuffer = false,
		bool CommandBufferUseCachedBuffer = false>
	using GLBVMesh_Obj = GLBVMesh<WaveFrontObjVertex,
		InstanceType,
		ElementType,
		VertexBufferUseCachedBuffer,
		IndexBufferUseCachedBuffer,
		InstanceBufferUseCachedBuffer,
		CommandBufferUseCachedBuffer>;
}
