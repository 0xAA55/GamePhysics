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

    enum class GLVarType
    {
        Unknown = 0,
        Bool = 0x8B56,
        Float = 0x1406,
        Int = 0x1404,
        UInt = 0x1405,
        Double = 0x140A
    };

    // Each has it's corresponding OpenGL constant name
    enum class AttribType
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

    enum class UniformType
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

    enum class TextureInternalFormat
    {
        R = 0x1903,
        RG = 0x8227,
        RGB = 0x1907,
        RGBA = 0x1908,
        Depth = 0x1902,
        DepthStencil = 0x84F9,
        R8 = 0x8229,
        R8_SN = 0x8F94,
        R16 = 0x822A,
        R16_SN = 0x8F98,
        RG8 = 0x822B,
        RG8_SN = 0x8F95,
        RG16 = 0x822C,
        RG16_SN = 0x8F99,
        R3_G3_B2 = 0x2A10,
        RGB4 = 0x804F,
        RGB5 = 0x8050,
        RGB8 = 0x8051,
        RGB8_SN = 0x8F96,
        RGB10 = 0x8052,
        RGB12 = 0x8053,
        RGB16_SN = 0x8F9A,
        RGBA2 = 0x8055,
        RGBA4 = 0x8056,
        RGB5_A1 = 0x8057,
        RGBA8 = 0x8058,
        RGBA8_SN = 0x8F97,
        RGB10_A2 = 0x8059,
        RGB10_A2UI = 0x906F,
        RGBA12 = 0x805A,
        RGBA16 = 0x805B,
        SRGB8 = 0x8C41,
        SRGB8_ALPHA8 = 0x8C43,
        R16F = 0x822D,
        RG16F = 0x822F,
        RGB16F = 0x881B,
        RGBA16F = 0x881A,
        R32F = 0x822E,
        RG32F = 0x8230,
        RGB32F = 0x8815,
        RGBA32F = 0x8814,
        R11F_G11F_B10F = 0x8C3A,
        RGB9_E5 = 0x8C3D,
        R8I = 0x8231,
        R8UI = 0x8232,
        R16I = 0x8233,
        R16UI = 0x8234,
        R32I = 0x8235,
        R32UI = 0x8236,
        RG8I = 0x8237,
        RG8UI = 0x8238,
        RG16I = 0x8239,
        RG16UI = 0x823A,
        RG32I = 0x823B,
        RG32UI = 0x823C,
        RGB8I = 0x8D8F,
        RGB8UI = 0x8D7D,
        RGB16I = 0x8D89,
        RGB16UI = 0x8D77,
        RGB32I = 0x8D83,
        RGB32UI = 0x8D71,
        RGBA8I = 0x8D8E,
        RGBA8UI = 0x8D7C,
        RGBA16I = 0x8D88,
        RGBA16UI = 0x8D76,
        RGBA32I = 0x8D82,
        RGBA32UI = 0x8D70
    };

    template<AttribType Type> struct TypeOfAttrib_s;
    template<> struct TypeOfAttrib_s<AttribType::Unknown> { using Type = void; using BaseType = void; };
    template<> struct TypeOfAttrib_s<AttribType::Float> { using Type = GLfloat; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Vec2> { using Type = vec2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Vec3> { using Type = vec3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Vec4> { using Type = vec4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat2> { using Type = mat2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat3> { using Type = mat3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat4> { using Type = mat4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat2x3> { using Type = mat2x3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat2x4> { using Type = mat2x4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat3x2> { using Type = mat3x2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat3x4> { using Type = mat3x4; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat4x2> { using Type = mat4x2; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Mat4x3> { using Type = mat4x3; using BaseType = GLfloat; };
    template<> struct TypeOfAttrib_s<AttribType::Int> { using Type = GLint; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribType::IVec2> { using Type = ivec2; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribType::IVec3> { using Type = ivec3; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribType::IVec4> { using Type = ivec4; using BaseType = GLint; };
    template<> struct TypeOfAttrib_s<AttribType::UInt> { using Type = GLuint; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribType::UVec2> { using Type = uvec2; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribType::UVec3> { using Type = uvec3; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribType::UVec4> { using Type = uvec4; using BaseType = GLuint; };
    template<> struct TypeOfAttrib_s<AttribType::Double> { using Type = GLdouble; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DVec2> { using Type = dvec2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DVec3> { using Type = dvec3; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DVec4> { using Type = dvec4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat2> { using Type = dmat2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat3> { using Type = dmat3; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat4> { using Type = dmat4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat2x3> { using Type = dmat2x3; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat2x4> { using Type = dmat2x4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat3x2> { using Type = dmat3x2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat3x4> { using Type = dmat3x4; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat4x2> { using Type = dmat4x2; using BaseType = GLdouble; };
    template<> struct TypeOfAttrib_s<AttribType::DMat4x3> { using Type = dmat4x3; using BaseType = GLdouble; };
    template<AttribType Type> using TypeOfAttrib = typename TypeOfAttrib_s<Type>::Type;
    template<AttribType Type> using BaseTypeOfAttrib = typename TypeOfAttrib_s<Type>::BaseType;

    int GLGetNumRows(const AttribType Type);
    int GLGetNumCols(const AttribType Type);
    GLVarType GLGetVarType(const AttribType Type);
    int GLGetNumUnits(const AttribType Type);
    int GLGetRowLength(const AttribType Type);
    bool GLIsInteger(const AttribType Type);
    bool GLIsInteger(const GLVarType VarType);
    bool GLIsDouble(const AttribType Type);
    bool GLIsDouble(const GLVarType VarType);
    int GLGetUnitLength(const AttribType Type);
    int GLGetUnitLength(const GLVarType VarType);
    const char *GLAttribTypeToString(const AttribType Type);
    AttribType GLStringToAttribType(std::string str);

    int GLGetNumRows(const UniformType Type);
    int GLGetNumCols(const UniformType Type);
    GLVarType GLGetVarType(const UniformType Type);
    int GLGetNumUnits(const UniformType Type);
    int GLGetRowLength(const UniformType Type);
    bool GLIsInteger(const UniformType Type);
    bool GLIsDouble(const UniformType Type);
    int GLGetUnitLength(const UniformType Type);
    const char *GLUniformTypeToString(const UniformType Type);
    UniformType GLStringToUniformType(std::string str);

    class InvalidUsageException : public std::runtime_error
    {
    public:
        InvalidUsageException(std::string What) noexcept;
    };
};
