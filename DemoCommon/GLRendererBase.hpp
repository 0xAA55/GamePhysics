#pragma once
#include<string>
#include<cstdint>
#include<stdexcept>
#include<type_traits>
#include<glm/glm.hpp>
namespace GLRenderer
{
	using namespace glm;

	typedef unsigned int GLenum;
	typedef unsigned int GLbitfield;
	typedef unsigned int GLuint;
	typedef int GLint;
	typedef int GLsizei;
	typedef unsigned char GLboolean;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned long GLulong;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef char GLchar;
	typedef int64_t GLint64;
	typedef uint64_t GLuint64;

    template <class T>
    inline void GLHashCombine(std::size_t &seed, const T &v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    enum class VarTypeEnum
    {
        Unknown = 0,
        Bool = 0x8B56,
        Float = 0x1406,
        Int = 0x1404,
        UInt = 0x1405,
        Double = 0x140A
    };

    // Each has it's corresponding OpenGL constant name
    enum class AttribTypeEnum
    {
        Unknown = 0,
        Float = 0x1406,
        Vec2 = 0x8B50,
        Vec3 = 0x8B51,
        Vec4 = 0x8B52,
        Mat2 = 0x8B5A,
        Mat3 = 0x8B5B,
        Mat4 = 0x8B5C,
        Mat2x3 = 0x8B65,
        Mat2x4 = 0x8B66,
        Mat3x2 = 0x8B67,
        Mat3x4 = 0x8B68,
        Mat4x2 = 0x8B69,
        Mat4x3 = 0x8B6A,
        Int = 0x1404,
        IVec2 = 0x8B53,
        IVec3 = 0x8B54,
        IVec4 = 0x8B55,
        UInt = 0x1405,
        UVec2 = 0x8DC6,
        UVec3 = 0x8DC7,
        UVec4 = 0x8DC8,
        Double = 0x140A,
        DVec2 = 0x8FFC,
        DVec3 = 0x8FFD,
        DVec4 = 0x8FFE,
        DMat2 = 0x8F46,
        DMat3 = 0x8F47,
        DMat4 = 0x8F48,
        DMat2x3 = 0x8F49,
        DMat2x4 = 0x8F4A,
        DMat3x2 = 0x8F4B,
        DMat3x4 = 0x8F4C,
        DMat4x2 = 0x8F4D,
        DMat4x3 = 0x8F4E
    };

    enum class UniformTypeEnum
    {
        Unknown = 0,
        Float = 0x1406,
        FloatVec2 = 0x8B50,
        FloatVec3 = 0x8B51,
        FloatVec4 = 0x8B52,
        Double = 0x140A,
        DoubleVec2 = 0x8FFC,
        DoubleVec3 = 0x8FFD,
        DoubleVec4 = 0x8FFE,
        Int = 0x1404,
        IntVec2 = 0x8B53,
        IntVec3 = 0x8B54,
        IntVec4 = 0x8B55,
        UInt = 0x1405,
        UIntVec2 = 0x8DC6,
        UIntVec3 = 0x8DC7,
        UIntVec4 = 0x8DC8,
        Bool = 0x8B56,
        BoolVec2 = 0x8B57,
        BoolVec3 = 0x8B58,
        BoolVec4 = 0x8B59,
        FloatMat2 = 0x8B5A,
        FloatMat3 = 0x8B5B,
        FloatMat4 = 0x8B5C,
        FloatMat2x3 = 0x8B65,
        FloatMat2x4 = 0x8B66,
        FloatMat3x2 = 0x8B67,
        FloatMat3x4 = 0x8B68,
        FloatMat4x2 = 0x8B69,
        FloatMat4x3 = 0x8B6A,
        DoubleMat2 = 0x8F46,
        DoubleMat3 = 0x8F47,
        DoubleMat4 = 0x8F48,
        DoubleMat2x3 = 0x8F49,
        DoubleMat2x4 = 0x8F4A,
        DoubleMat3x2 = 0x8F4B,
        DoubleMat3x4 = 0x8F4C,
        DoubleMat4x2 = 0x8F4D,
        DoubleMat4x3 = 0x8F4E,
        Sampler1D = 0x8B5D,
        Sampler2D = 0x8B5E,
        Sampler3D = 0x8B5F,
        SamplerCube = 0x8B60,
        Sampler1DShadow = 0x8B61,
        Sampler2DShadow = 0x8B62,
        Sampler1DArray = 0x8DC0,
        Sampler2DArray = 0x8DC1,
        Sampler1DArrayShadow = 0x8DC3,
        Sampler2DArrayShadow = 0x8DC4,
        Sampler2DMultisample = 0x9108,
        Sampler2DMultisampleArray = 0x910B,
        SamplerCubeShadow = 0x8DC5,
        SamplerBuffer = 0x8DC2,
        Sampler2DRect = 0x8B63,
        Sampler2DRectShadow = 0x8B64,
        IntSampler1D = 0x8DC9,
        IntSampler2D = 0x8DCA,
        IntSampler3D = 0x8DCB,
        IntSamplerCube = 0x8DCC,
        IntSampler1DArray = 0x8DCE,
        IntSampler2DArray = 0x8DCF,
        IntSampler2DMultisample = 0x9109,
        IntSampler2DMultisampleArray = 0x910C,
        IntSamplerBuffer = 0x8DD0,
        IntSampler2DRect = 0x8DCD,
        UIntSampler1D = 0x8DD1,
        UIntSampler2D = 0x8DD2,
        UIntSampler3D = 0x8DD3,
        UIntSamplerCube = 0x8DD4,
        UIntSampler1DArray = 0x8DD6,
        UIntSampler2DArray = 0x8DD7,
        UIntSampler2DMultisample = 0x910A,
        UIntSampler2DMultisampleArray = 0x910D,
        UIntSamplerBuffer = 0x8DD8,
        UIntSampler2DRect = 0x8DD5,
        Image1D = 0x904C,
        Image2D = 0x904D,
        Image3D = 0x904E,
        Image2DRect = 0x904F,
        ImageCube = 0x9050,
        ImageBuffer = 0x9051,
        Image1DArray = 0x9052,
        Image2DArray = 0x9053,
        Image2DMultisample = 0x9055,
        Image2DMultisampleArray = 0x9056,
        IntImage1D = 0x9057,
        IntImage2D = 0x9058,
        IntImage3D = 0x9059,
        IntImage2DRect = 0x905A,
        IntImageCube = 0x905B,
        IntImageBuffer = 0x905C,
        IntImage1DArray = 0x905D,
        IntImage2DArray = 0x905E,
        IntImage2DMultisample = 0x9060,
        IntImage2DMultisampleArray = 0x9061,
        UIntImage1D = 0x9062,
        UIntImage2D = 0x9063,
        UIntImage3D = 0x9064,
        UIntImage2DRect = 0x9065,
        UIntImageCube = 0x9066,
        UIntImageBuffer = 0x9067,
        UIntImage1DArray = 0x9068,
        UIntImage2DArray = 0x9069,
        UIntImage2DMultisample = 0x906B,
        UIntImage2DMultisampleArray = 0x906C,
        UIntAtomicCounter = 0x92DB
    };

    template<AttribTypeEnum Type> struct TypeOfAttrib_s;
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Unknown> { using Type = void; using BaseType = void; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Float> { using Type = GLfloat; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Vec2> { using Type = vec2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Vec3> { using Type = vec3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Vec4> { using Type = vec4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat2> { using Type = mat2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat3> { using Type = mat3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat4> { using Type = mat4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat2x3> { using Type = mat2x3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat2x4> { using Type = mat2x4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat3x2> { using Type = mat3x2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat3x4> { using Type = mat3x4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat4x2> { using Type = mat4x2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Mat4x3> { using Type = mat4x3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Int> { using Type = GLint; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::IVec2> { using Type = ivec2; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::IVec3> { using Type = ivec3; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::IVec4> { using Type = ivec4; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::UInt> { using Type = GLuint; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::UVec2> { using Type = uvec2; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::UVec3> { using Type = uvec3; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::UVec4> { using Type = uvec4; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::Double> { using Type = GLdouble; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DVec2> { using Type = dvec2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DVec3> { using Type = dvec3; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DVec4> { using Type = dvec4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat2> { using Type = dmat2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat3> { using Type = dmat3; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat4> { using Type = dmat4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat2x3> { using Type = dmat2x3; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat2x4> { using Type = dmat2x4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat3x2> { using Type = dmat3x2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat3x4> { using Type = dmat3x4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat4x2> { using Type = dmat4x2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribTypeEnum::DMat4x3> { using Type = dmat4x3; using BaseType = GLdouble; };
    template<AttribTypeEnum Type> using TypeOfAttrib = typename TypeOfAttrib_s<Type>::Type;
    template<AttribTypeEnum Type> using BaseTypeOfAttrib = typename TypeOfAttrib_s<Type>::BaseType;

    int GetNumRows(const AttribTypeEnum Type);
    int GetNumCols(const AttribTypeEnum Type);
    VarTypeEnum GetVarType(const AttribTypeEnum Type);
    int GetNumUnits(const AttribTypeEnum Type);
    int GetRowLength(const AttribTypeEnum Type);
    bool IsInteger(const AttribTypeEnum Type);
    bool IsInteger(const VarTypeEnum VarType);
    bool IsDouble(const AttribTypeEnum Type);
    bool IsDouble(const VarTypeEnum VarType);
    int GetUnitLength(const AttribTypeEnum Type);
    int GetUnitLength(const VarTypeEnum VarType);
    const char *AttribTypeToString(const AttribTypeEnum Type);
    AttribTypeEnum StringToAttribType(std::string str);

    int GetNumRows(const UniformTypeEnum Type);
    int GetNumCols(const UniformTypeEnum Type);
    VarTypeEnum GetVarType(const UniformTypeEnum Type);
    int GetNumUnits(const UniformTypeEnum Type);
    int GetRowLength(const UniformTypeEnum Type);
    bool IsInteger(const UniformTypeEnum Type);
    bool IsDouble(const UniformTypeEnum Type);
    int GetUnitLength(const UniformTypeEnum Type);
    const char *UniformTypeToString(const UniformTypeEnum Type);
    UniformTypeEnum StringToUniformType(std::string str);

    template<typename T> inline T CalcBitmapPitch(T Width, T BPP, int AlignSize = 4)
    {
        return ((Width * BPP - 1) / (AlignSize * 8) + 1) * AlignSize;
    }

    class InvalidUsageException : public std::runtime_error
    {
    public:
        inline InvalidUsageException(std::string What) noexcept : std::runtime_error(What) {}
    };
};
