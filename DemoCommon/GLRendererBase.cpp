#include "GLRendererBase.hpp"
#include <stdexcept>
#include <GL/glew.h>
namespace GLRenderer
{
    int GLGetNumRows(const AttribType Type)
    {
        switch (Type)
        {
        case AttribType::Float: return 1;
        case AttribType::Vec2: return 1;
        case AttribType::Vec3: return 1;
        case AttribType::Vec4: return 1;
        case AttribType::Mat2: return 2;
        case AttribType::Mat3: return 3;
        case AttribType::Mat4: return 4;
        case AttribType::Mat2x3: return 3;
        case AttribType::Mat2x4: return 4;
        case AttribType::Mat3x2: return 2;
        case AttribType::Mat3x4: return 4;
        case AttribType::Mat4x2: return 2;
        case AttribType::Mat4x3: return 3;
        case AttribType::Int: return 1;
        case AttribType::IVec2: return 1;
        case AttribType::IVec3: return 1;
        case AttribType::IVec4: return 1;
        case AttribType::UInt: return 1;
        case AttribType::UVec2: return 1;
        case AttribType::UVec3: return 1;
        case AttribType::UVec4: return 1;
        case AttribType::Double: return 1;
        case AttribType::DVec2: return 1;
        case AttribType::DVec3: return 1;
        case AttribType::DVec4: return 1;
        case AttribType::DMat2: return 2;
        case AttribType::DMat3: return 3;
        case AttribType::DMat4: return 4;
        case AttribType::DMat2x3: return 3;
        case AttribType::DMat2x4: return 4;
        case AttribType::DMat3x2: return 2;
        case AttribType::DMat3x4: return 4;
        case AttribType::DMat4x2: return 2;
        case AttribType::DMat4x3: return 3;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GLGetNumCols(const AttribType Type)
    {
        switch (Type)
        {
        case AttribType::Float: return 1;
        case AttribType::Vec2: return 2;
        case AttribType::Vec3: return 3;
        case AttribType::Vec4: return 4;
        case AttribType::Mat2: return 2;
        case AttribType::Mat3: return 3;
        case AttribType::Mat4: return 4;
        case AttribType::Mat2x3: return 2;
        case AttribType::Mat2x4: return 2;
        case AttribType::Mat3x2: return 3;
        case AttribType::Mat3x4: return 3;
        case AttribType::Mat4x2: return 4;
        case AttribType::Mat4x3: return 4;
        case AttribType::Int: return 1;
        case AttribType::IVec2: return 2;
        case AttribType::IVec3: return 3;
        case AttribType::IVec4: return 4;
        case AttribType::UInt: return 1;
        case AttribType::UVec2: return 2;
        case AttribType::UVec3: return 3;
        case AttribType::UVec4: return 4;
        case AttribType::Double: return 1;
        case AttribType::DVec2: return 2;
        case AttribType::DVec3: return 3;
        case AttribType::DVec4: return 4;
        case AttribType::DMat2: return 2;
        case AttribType::DMat3: return 3;
        case AttribType::DMat4: return 4;
        case AttribType::DMat2x3: return 2;
        case AttribType::DMat2x4: return 2;
        case AttribType::DMat3x2: return 3;
        case AttribType::DMat3x4: return 3;
        case AttribType::DMat4x2: return 4;
        case AttribType::DMat4x3: return 4;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    AttribUnitType GLGetUnitType(const AttribType Type)
    {
        switch (Type)
        {
        case AttribType::Float:
        case AttribType::Vec2:
        case AttribType::Vec3:
        case AttribType::Vec4:
        case AttribType::Mat2:
        case AttribType::Mat3:
        case AttribType::Mat4:
        case AttribType::Mat2x3:
        case AttribType::Mat2x4:
        case AttribType::Mat3x2:
        case AttribType::Mat3x4:
        case AttribType::Mat4x2:
        case AttribType::Mat4x3: return AttribUnitType::Float;
        case AttribType::Int:
        case AttribType::IVec2:
        case AttribType::IVec3:
        case AttribType::IVec4: return AttribUnitType::Int;
        case AttribType::UInt:
        case AttribType::UVec2:
        case AttribType::UVec3:
        case AttribType::UVec4: return AttribUnitType::UInt;
        case AttribType::Double:
        case AttribType::DVec2:
        case AttribType::DVec3:
        case AttribType::DVec4:
        case AttribType::DMat2:
        case AttribType::DMat3:
        case AttribType::DMat4:
        case AttribType::DMat2x3:
        case AttribType::DMat2x4:
        case AttribType::DMat3x2:
        case AttribType::DMat3x4:
        case AttribType::DMat4x2:
        case AttribType::DMat4x3: return AttribUnitType::Double;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GLGetNumUnits(const AttribType Type)
    {
        return GLGetNumRows(Type) * GLGetNumCols(Type);
    }

    int GLGetRowLength(const AttribType Type)
    {
        return GLGetNumRows(Type) * GLGetUnitLength(Type);
    }

    bool GLIsInteger(const AttribType Type)
    {
        return GLIsInteger(GLGetUnitType(Type));
    }

    bool GLIsInteger(const AttribUnitType UnitType)
    {
        switch (UnitType)
        {
        case AttribUnitType::Int:
        case AttribUnitType::UInt:
            return true;
        }
        return false;
    }

    bool GLIsDouble(const AttribType Type)
    {
        return GLIsDouble(GLGetUnitType(Type));
    }

    bool GLIsDouble(const AttribUnitType UnitType)
    {
        switch (UnitType)
        {
        case AttribUnitType::Double:
            return true;
        }
        return false;
    }
    int GLGetUnitLength(const AttribType Type)
    {
        return GLGetUnitLength(GLGetUnitType(Type));
    }
    int GLGetUnitLength(const AttribUnitType UnitType)
    {
        switch (UnitType)
        {
        case AttribUnitType::Float: return sizeof(GLfloat);
        case AttribUnitType::Int: return sizeof(GLint);
        case AttribUnitType::UInt: return sizeof(GLuint);
        case AttribUnitType::Double: return sizeof(GLdouble);
        default: throw std::invalid_argument(std::string("Invalid `UnitType`"));
        }
    }

    const char *GLAttribTypeToString(const AttribType Type)
    {
        switch (Type)
        {
        case AttribType::Float: return "float";
        case AttribType::Vec2: return "vec2";
        case AttribType::Vec3: return "vec3";
        case AttribType::Vec4: return "vec4";
        case AttribType::Mat2: return "mat2";
        case AttribType::Mat3: return "mat3";
        case AttribType::Mat4: return "mat4";
        case AttribType::Mat2x3: return "mat2x3";
        case AttribType::Mat2x4: return "mat2x4";
        case AttribType::Mat3x2: return "mat3x2";
        case AttribType::Mat3x4: return "mat3x4";
        case AttribType::Mat4x2: return "mat4x2";
        case AttribType::Mat4x3: return "mat4x3";
        case AttribType::Int: return "int";
        case AttribType::IVec2: return "ivec2";
        case AttribType::IVec3: return "ivec3";
        case AttribType::IVec4: return "ivec4";
        case AttribType::UInt: return "unsigned int";
        case AttribType::UVec2: return "uvec2";
        case AttribType::UVec3: return "uvec3";
        case AttribType::UVec4: return "uvec4";
        case AttribType::Double: return "double";
        case AttribType::DVec2: return "dvec2";
        case AttribType::DVec3: return "dvec3";
        case AttribType::DVec4: return "dvec4";
        case AttribType::DMat2: return "dmat2";
        case AttribType::DMat3: return "dmat3";
        case AttribType::DMat4: return "dmat4";
        case AttribType::DMat2x3: return "dmat2x3";
        case AttribType::DMat2x4: return "dmat2x4";
        case AttribType::DMat3x2: return "dmat3x2";
        case AttribType::DMat3x4: return "dmat3x4";
        case AttribType::DMat4x2: return "dmat4x2";
        case AttribType::DMat4x3: return "dmat4x3";
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    AttribType GLStringToAttribType(std::string str)
    {
        if (!str.compare("float")) return AttribType::Float;
        if (!str.compare("vec2")) return AttribType::Vec2;
        if (!str.compare("vec3")) return AttribType::Vec3;
        if (!str.compare("vec4")) return AttribType::Vec4;
        if (!str.compare("mat2")) return AttribType::Mat2;
        if (!str.compare("mat3")) return AttribType::Mat3;
        if (!str.compare("mat4")) return AttribType::Mat4;
        if (!str.compare("mat2x3")) return AttribType::Mat2x3;
        if (!str.compare("mat2x4")) return AttribType::Mat2x4;
        if (!str.compare("mat3x2")) return AttribType::Mat3x2;
        if (!str.compare("mat3x4")) return AttribType::Mat3x4;
        if (!str.compare("mat4x2")) return AttribType::Mat4x2;
        if (!str.compare("mat4x3")) return AttribType::Mat4x3;
        if (!str.compare("int")) return AttribType::Int;
        if (!str.compare("ivec2")) return AttribType::IVec2;
        if (!str.compare("ivec3")) return AttribType::IVec3;
        if (!str.compare("ivec4")) return AttribType::IVec4;
        if (!str.compare("unsigned int")) return AttribType::UInt;
        if (!str.compare("uvec2")) return AttribType::UVec2;
        if (!str.compare("uvec3")) return AttribType::UVec3;
        if (!str.compare("uvec4")) return AttribType::UVec4;
        if (!str.compare("double")) return AttribType::Double;
        if (!str.compare("dvec2")) return AttribType::DVec2;
        if (!str.compare("dvec3")) return AttribType::DVec3;
        if (!str.compare("dvec4")) return AttribType::DVec4;
        if (!str.compare("dmat2")) return AttribType::DMat2;
        if (!str.compare("dmat3")) return AttribType::DMat3;
        if (!str.compare("dmat4")) return AttribType::DMat4;
        if (!str.compare("dmat2x3")) return AttribType::DMat2x3;
        if (!str.compare("dmat2x4")) return AttribType::DMat2x4;
        if (!str.compare("dmat3x2")) return AttribType::DMat3x2;
        if (!str.compare("dmat3x4")) return AttribType::DMat3x4;
        if (!str.compare("dmat4x2")) return AttribType::DMat4x2;
        if (!str.compare("dmat4x3")) return AttribType::DMat4x3;
        throw std::invalid_argument(std::string("Invalid `Type`"));
    }
}
