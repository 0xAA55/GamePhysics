#pragma once
#include<GLRendererBase.hpp>
#include<GLMeshVAO.hpp>
#include<memory>
#include<vector>
#include<unordered_map>
namespace GLRenderer
{
	class GLStaticMesh
	{
	protected:
		VAOContainer VAOsForEachShader;

	public:
		std::shared_ptr<GLBufferObject> ArrayBuffer;
		std::shared_ptr<GLBufferObject> IndexBuffer;
		std::shared_ptr<GLBufferObject> InstanceBuffer;
		std::shared_ptr<GLBufferObject> CommandBuffer;
		AttribDescArray ArrayBufferFormat;
		AttribDescArray InstanceBufferFormat;
		MeshPrimitiveType PrimitiveType;
		MeshElementType IndexBufferElementType;
		GLsizei VertexCount;
		GLsizei InstanceCount;

		inline GLsizei GetIndexCount()
		{
			if (!IndexBuffer) return 0;
			return static_cast<GLsizei>(IndexBuffer->GetLength() / GetElementTypeSize(IndexBufferElementType));
		}

		inline GLsizei GetDrawCommandCount()
		{
			if (!CommandBuffer) return 0;
			return static_cast<GLsizei>(CommandBuffer->GetLength() / sizeof(DrawCommand));
		}

	protected:
		GLBufferObject* DescribedArrayBuffer;
		GLBufferObject* DescribedInstanceBuffer;
		GLVAO& Describe(const GLShaderProgram& Shader);

	public:
		GLStaticMesh();
		GLStaticMesh(GLStaticMesh& CreateFrom);
		GLStaticMesh(const GLStaticMesh& CopyFrom);

		void CreateArrayBuffer(size_t Size);
		void CreateIndexBuffer(MeshElementType ElementType, size_t Size);
		void CreateInstanceBuffer(size_t Size, size_t DrawInstanceCount);
		void CreateCommandBuffer(size_t Count);

		void SetArrayBufferSize(size_t Size);
		void SetIndexBufferSize(size_t Size);
		void SetInstanceBufferSize(size_t Size, size_t DrawInstanceCount);
		void SetCommandBufferCount(size_t Count);

		void Draw(const GLShaderProgram& Shader);
	};

};

