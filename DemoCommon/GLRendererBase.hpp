#pragma once
#include<string>
#include<cstdint>
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

    enum class AttribUnitType
    {
        Unknown = 0,
        Float = 0x1406,
        Int = 0x1404,
        UInt = 0x1405,
        Double = 0x140A
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
    AttribUnitType GLGetUnitType(const AttribType Type);
    int GLGetNumUnits(const AttribType Type);
    int GLGetRowLength(const AttribType Type);
    bool GLIsInteger(const AttribType Type);
    bool GLIsInteger(const AttribUnitType UnitType);
    bool GLIsDouble(const AttribType Type);
    bool GLIsDouble(const AttribUnitType UnitType);
    int GLGetUnitLength(const AttribType Type);
    int GLGetUnitLength(const AttribUnitType UnitType);
    const char *GLAttribTypeToString(const AttribType Type);
    AttribType GLStringToAttribType(std::string str);

    template <class T>
    inline void GLHashCombine(std::size_t &seed, const T &v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

