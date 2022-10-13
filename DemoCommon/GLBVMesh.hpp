#pragma once
#include<GLRendererBase.hpp>
#include<unordered_map>
#include<GLBufferVector.hpp>
#include<GLMesh.hpp>
#include<type_traits>
#include<ObjMeshLoader.hpp>
namespace GLRenderer
{
	template<
		typename VertexType,
		typename InstanceType,
		MeshElementType ElementType = MeshElementType::UnsignedInt>
	class GLBVMesh : public GLMesh
	{
	protected:
		using IndexType = TypeOfElement<ElementType>;
		using VertexBufferType = GLBufferVector<VertexType>;
		using IndexBufferType = GLBufferVector<IndexType>;
		using InstanceBufferType = GLBufferVector<InstanceType>;
		using CommandBufferType = GLBufferVector<DrawCommand>;

		void VerifyBufferFormat() override
		{
			GLsizei CurOffset = 0;
			for (auto& it : VertexBufferFormat)
			{
				if (it.Offset == 0) it.Offset = CurOffset;
				if (it.Stride == 0) it.Stride = sizeof(VertexType);
				CurOffset = it.Offset + it.GetSizeBytes();
			}
			CurOffset = 0;
			for (auto& it : InstanceBufferFormat)
			{
				if (it.Offset == 0) it.Offset = CurOffset;
				if (it.Stride == 0) it.Stride = sizeof(InstanceType);
				CurOffset = it.Offset + it.GetSizeBytes();
			}
		}

	public:
		VertexBufferType VertexBufferVector;
		IndexBufferType IndexBufferVector;
		InstanceBufferType InstanceBufferVector;
		CommandBufferType CommandBufferVector;

		GLBVMesh(MeshPrimitiveType PrimitiveType) :
			GLMesh(PrimitiveType),
			VertexBufferVector(BufferType::ArrayBuffer, BufferUsage::StaticDraw, VertexBuffer),
			IndexBufferVector(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw, IndexBuffer),
			InstanceBufferVector(BufferType::ArrayBuffer, BufferUsage::StreamDraw, InstanceBuffer),
			CommandBufferVector(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw, CommandBuffer)
		{
			IndexBufferElementType = ElementType;
		}

		GLBVMesh(MeshPrimitiveType PrimitiveType, const std::vector<VertexType> &VertexData) :
			GLBVMesh(PrimitiveType)
		{
			VertexBufferVector.PushBack(VertexData);
		}

		GLBVMesh(MeshPrimitiveType PrimitiveType, const std::vector<VertexType> &VertexData, const std::vector<IndexType> &IndexData) :
			GLBVMesh(PrimitiveType, VertexData)
		{
			IndexBufferVector.PushBack(IndexData);
		}

		GLBVMesh(const GLBVMesh &CopyFrom) :
			GLMesh(CopyFrom),
			VertexBufferVector(BufferType::ArrayBuffer, BufferUsage::StaticDraw, VertexBuffer),
			IndexBufferVector(BufferType::ElementArrayBuffer, BufferUsage::StaticDraw, IndexBuffer),
			InstanceBufferVector(BufferType::ArrayBuffer, BufferUsage::StreamDraw, InstanceBuffer),
			CommandBufferVector(BufferType::DrawIndirectBuffer, BufferUsage::StaticDraw, CommandBuffer)
		{
		}
	};

	extern template GLBufferVector<GeneralObjVertexType>;
	extern template GLBufferVector<DrawCommand>;

	template<
		typename InstanceType,
		MeshElementType ElementType = MeshElementType::UnsignedInt>
	using GLBVMesh_Obj = GLBVMesh< GeneralObjVertexType,
		InstanceType,
		ElementType>;
}
