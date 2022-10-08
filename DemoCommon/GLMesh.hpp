#pragma once
#include<GLRendererBase.hpp>
#include<GLBufferObject.hpp>
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

		inline operator GLuint() const { return VAO; }
		inline bool IsDescribed() const { return Described; }
		inline void SetDescribed() { Described = true; }

		void Bind() const;
		void Draw(MeshPrimitiveType PrimitiveType, GLsizei CommandCount) const;
		void Draw(MeshPrimitiveType PrimitiveType, GLsizei VertexCount, GLsizei InstanceCount) const;
		void DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei CommandCount) const;
		void DrawByElements(MeshPrimitiveType PrimitiveType, MeshElementType ElementType, GLsizei VertexCount, GLsizei InstanceCount) const;
	};

	using VAOContainer = std::unordered_map<GLShaderProgram, GLVAO, GLShaderProgramHasher>;

	class AttribDesc
	{
	public:
		std::string Name;
		AttribTypeEnum Type;
		VarTypeEnum VarType;
		GLsizei Offset; // If `Offset` is -1, it means the offset should be calculated automatically.
		int ColCount; // e.g. vec2, vec3, vec4
		int RowCount; // e.g. mat4x2, mat4x3, mat4x4
		int Length;
		bool AsFloat;
		bool Normalize;

		AttribDesc(std::string Name, AttribTypeEnum Type, GLsizei Offset = -1, bool AsFloat = true, bool Normalize = false);
		AttribDesc(std::string Name, std::string Type, GLsizei Offset = -1, bool AsFloat = true, bool Normalize = false);

		void Describe(const GLShaderProgram& Shader, GLsizei Stride, GLuint AVD) const;
		inline GLsizei GetSizeBytes() const { return GetNumUnits(Type) * GetUnitLength(Type); }
	};

}
