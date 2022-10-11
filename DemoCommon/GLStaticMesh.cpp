#include "GLStaticMesh.hpp"
using namespace GLRenderer;

GLStaticMesh::GLStaticMesh() :
	PrimitiveType(MeshPrimitiveType::Triangles),
	IndexBufferElementType(MeshElementType::UnsignedInt)
{
}

GLVAO& GLStaticMesh::Describe(const GLShaderProgram& Shader)
{
	bool ShouldDescribe = ArrayBuffer.get() != DescribedArrayBuffer || InstanceBuffer.get() != DescribedInstanceBuffer;
	GLVAO& VAO = VAOsForEachShader[Shader];
	if (!VAO.IsDescribed()) ShouldDescribe = true;
	VAO.Bind();
	if (ShouldDescribe)
	{
		if (ArrayBuffer && ArrayBufferFormat.size())
		{
			GLsizei LastOffset = 0;
			ArrayBuffer->Bind();
			for (auto& it : ArrayBufferFormat)
			{
				if (it.Offset == -1) it.Offset = LastOffset;
				LastOffset = it.Offset + it.GetSizeBytes();
				it.Describe(Shader, 0);
			}
			ArrayBuffer->Unbind();
			DescribedArrayBuffer = ArrayBuffer.get();
		}
		if (InstanceBuffer && InstanceBufferFormat.size())
		{
			GLsizei LastOffset = 0;
			InstanceBuffer->Bind();
			for (auto& it : InstanceBufferFormat)
			{
				if (it.Offset == -1) it.Offset = LastOffset;
				LastOffset = it.Offset + it.GetSizeBytes();
				it.Describe(Shader, 1);
			}
			InstanceBuffer->Unbind();
			DescribedInstanceBuffer = InstanceBuffer.get();
		}
		VAO.SetDescribed();
	}
	return VAO;
}

void GLStaticMesh::CreateArrayBuffer(size_t Size)
{
	if (Size) ArrayBuffer = std::make_shared<GLBufferObject>(BufferType::ArrayBuffer, Size, BufferUsage::StaticDraw);
	else ArrayBuffer.reset();
}

void GLStaticMesh::CreateIndexBuffer(MeshElementType ElementType, size_t Size)
{
	if (Size) IndexBuffer = std::make_shared<GLBufferObject>(BufferType::ElementArrayBuffer, Size, BufferUsage::StaticDraw);
	else IndexBuffer.reset();
	IndexBufferElementType = ElementType;
}

void GLStaticMesh::CreateInstanceBuffer(size_t Size, size_t DrawInstanceCount)
{
	if (Size) InstanceBuffer = std::make_shared<GLBufferObject>(BufferType::ArrayBuffer, Size, BufferUsage::DynamicDraw);
	else InstanceBuffer.reset();
	InstanceCount = DrawInstanceCount;
}

void GLStaticMesh::CreateCommandBuffer(size_t Count)
{
	if (Count) CommandBuffer = std::make_shared<GLBufferObject>(BufferType::DrawIndirectBuffer, Count * sizeof(DrawCommand), BufferUsage::DynamicDraw);
	else CommandBuffer.reset();
}

void GLStaticMesh::SetArrayBufferSize(size_t Size)
{
	if (ArrayBuffer && Size) ArrayBuffer = std::make_shared<GLBufferObject>(*ArrayBuffer, Size, -1);
	else
		CreateArrayBuffer(Size);
}

void GLStaticMesh::SetIndexBufferSize(size_t Size)
{
	if (IndexBuffer) IndexBuffer = std::make_shared<GLBufferObject>(*IndexBuffer, Size, -1);
	else CreateIndexBuffer(IndexBufferElementType, Size);
}

void GLStaticMesh::SetInstanceBufferSize(size_t Size, size_t DrawInstanceCount)
{
	if (InstanceBuffer)
	{
		InstanceBuffer = std::make_shared<GLBufferObject>(*InstanceBuffer, Size, -1);
		InstanceCount = DrawInstanceCount;
	}
	else CreateInstanceBuffer(Size, DrawInstanceCount);
}

void GLStaticMesh::SetCommandBufferCount(size_t Count)
{
	if (CommandBuffer) CommandBuffer = std::make_shared<GLBufferObject>(*CommandBuffer, Count * sizeof(DrawCommand), -1);
	else CreateCommandBuffer(Count);
}

void GLStaticMesh::Draw(const GLShaderProgram& Shader)
{
	Shader.Use();
	auto& VAO = Describe(Shader);
	if (IndexBuffer)
	{
		IndexBuffer->Bind();
		if (CommandBuffer)
		{
			CommandBuffer->Bind();
			VAO.DrawByElements(PrimitiveType, IndexBufferElementType, GetDrawCommandCount());
			CommandBuffer->Unbind();
		}
		else
		{
			VAO.DrawByElements(PrimitiveType, IndexBufferElementType, GetIndexCount(), static_cast<GLsizei>(InstanceCount));
		}
		IndexBuffer->Unbind();
	}
	else
	{
		if (CommandBuffer)
		{
			CommandBuffer->Bind();
			VAO.Draw(PrimitiveType, static_cast<GLsizei>(GetDrawCommandCount()));
			CommandBuffer->Unbind();
		}
		else VAO.Draw(PrimitiveType, VertexCount, InstanceCount);
	}
	Shader.Unuse();
}
