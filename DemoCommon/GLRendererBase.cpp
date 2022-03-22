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

    GLVarType GLGetVarType(const AttribType Type)
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
        case AttribType::Mat4x3: return GLVarType::Float;
        case AttribType::Int:
        case AttribType::IVec2:
        case AttribType::IVec3:
        case AttribType::IVec4: return GLVarType::Int;
        case AttribType::UInt:
        case AttribType::UVec2:
        case AttribType::UVec3:
        case AttribType::UVec4: return GLVarType::UInt;
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
        case AttribType::DMat4x3: return GLVarType::Double;
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
        return GLIsInteger(GLGetVarType(Type));
    }

    bool GLIsInteger(const GLVarType VarType)
    {
        switch (VarType)
        {
        case GLVarType::Int:
        case GLVarType::UInt:
            return true;
        }
        return false;
    }

    bool GLIsDouble(const AttribType Type)
    {
        return GLIsDouble(GLGetVarType(Type));
    }

    bool GLIsDouble(const GLVarType VarType)
    {
        switch (VarType)
        {
        case GLVarType::Double:
            return true;
        }
        return false;
    }
    int GLGetUnitLength(const AttribType Type)
    {
        return GLGetUnitLength(GLGetVarType(Type));
    }
    int GLGetUnitLength(const GLVarType VarType)
    {
        switch (VarType)
        {
        case GLVarType::Bool: return sizeof(GLboolean);
        case GLVarType::Float: return sizeof(GLfloat);
        case GLVarType::Int: return sizeof(GLint);
        case GLVarType::UInt: return sizeof(GLuint);
        case GLVarType::Double: return sizeof(GLdouble);
        default: throw std::invalid_argument(std::string("Invalid `VarType`"));
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

    int GLGetNumRows(const UniformType Type)
    {
        switch (Type)
        {
        case UniformType::Float: return 1;
        case UniformType::FloatVec2: return 1;
        case UniformType::FloatVec3: return 1;
        case UniformType::FloatVec4: return 1;
        case UniformType::Double: return 1;
        case UniformType::DoubleVec2: return 1;
        case UniformType::DoubleVec3: return 1;
        case UniformType::DoubleVec4: return 1;
        case UniformType::Int: return 1;
        case UniformType::IntVec2: return 1;
        case UniformType::IntVec3: return 1;
        case UniformType::IntVec4: return 1;
        case UniformType::UInt: return 1;
        case UniformType::UIntVec2: return 1;
        case UniformType::UIntVec3: return 1;
        case UniformType::UIntVec4: return 1;
        case UniformType::Bool: return 1;
        case UniformType::BoolVec2: return 1;
        case UniformType::BoolVec3: return 1;
        case UniformType::BoolVec4: return 1;
        case UniformType::FloatMat2: return 2;
        case UniformType::FloatMat3: return 3;
        case UniformType::FloatMat4: return 4;
        case UniformType::FloatMat2x3: return 3;
        case UniformType::FloatMat2x4: return 4;
        case UniformType::FloatMat3x2: return 2;
        case UniformType::FloatMat3x4: return 4;
        case UniformType::FloatMat4x2: return 2;
        case UniformType::FloatMat4x3: return 3;
        case UniformType::DoubleMat2: return 2;
        case UniformType::DoubleMat3: return 3;
        case UniformType::DoubleMat4: return 4;
        case UniformType::DoubleMat2x3: return 3;
        case UniformType::DoubleMat2x4: return 4;
        case UniformType::DoubleMat3x2: return 2;
        case UniformType::DoubleMat3x4: return 4;
        case UniformType::DoubleMat4x2: return 2;
        case UniformType::DoubleMat4x3: return 3;
        case UniformType::Sampler1D: return 1;
        case UniformType::Sampler2D: return 1;
        case UniformType::Sampler3D: return 1;
        case UniformType::SamplerCube: return 1;
        case UniformType::Sampler1DShadow: return 1;
        case UniformType::Sampler2DShadow: return 1;
        case UniformType::Sampler1DArray: return 1;
        case UniformType::Sampler2DArray: return 1;
        case UniformType::Sampler1DArrayShadow: return 1;
        case UniformType::Sampler2DArrayShadow: return 1;
        case UniformType::Sampler2DMultisample: return 1;
        case UniformType::Sampler2DMultisampleArray: return 1;
        case UniformType::SamplerCubeShadow: return 1;
        case UniformType::SamplerBuffer: return 1;
        case UniformType::Sampler2DRect: return 1;
        case UniformType::Sampler2DRectShadow: return 1;
        case UniformType::IntSampler1D: return 1;
        case UniformType::IntSampler2D: return 1;
        case UniformType::IntSampler3D: return 1;
        case UniformType::IntSamplerCube: return 1;
        case UniformType::IntSampler1DArray: return 1;
        case UniformType::IntSampler2DArray: return 1;
        case UniformType::IntSampler2DMultisample: return 1;
        case UniformType::IntSampler2DMultisampleArray: return 1;
        case UniformType::IntSamplerBuffer: return 1;
        case UniformType::IntSampler2DRect: return 1;
        case UniformType::UIntSampler1D: return 1;
        case UniformType::UIntSampler2D: return 1;
        case UniformType::UIntSampler3D: return 1;
        case UniformType::UIntSamplerCube: return 1;
        case UniformType::UIntSampler1DArray: return 1;
        case UniformType::UIntSampler2DArray: return 1;
        case UniformType::UIntSampler2DMultisample: return 1;
        case UniformType::UIntSampler2DMultisampleArray: return 1;
        case UniformType::UIntSamplerBuffer: return 1;
        case UniformType::UIntSampler2DRect: return 1;
        case UniformType::Image1D: return 1;
        case UniformType::Image2D: return 1;
        case UniformType::Image3D: return 1;
        case UniformType::Image2DRect: return 1;
        case UniformType::ImageCube: return 1;
        case UniformType::ImageBuffer: return 1;
        case UniformType::Image1DArray: return 1;
        case UniformType::Image2DArray: return 1;
        case UniformType::Image2DMultisample: return 1;
        case UniformType::Image2DMultisampleArray: return 1;
        case UniformType::IntImage1D: return 1;
        case UniformType::IntImage2D: return 1;
        case UniformType::IntImage3D: return 1;
        case UniformType::IntImage2DRect: return 1;
        case UniformType::IntImageCube: return 1;
        case UniformType::IntImageBuffer: return 1;
        case UniformType::IntImage1DArray: return 1;
        case UniformType::IntImage2DArray: return 1;
        case UniformType::IntImage2DMultisample: return 1;
        case UniformType::IntImage2DMultisampleArray: return 1;
        case UniformType::UIntImage1D: return 1;
        case UniformType::UIntImage2D: return 1;
        case UniformType::UIntImage3D: return 1;
        case UniformType::UIntImage2DRect: return 1;
        case UniformType::UIntImageCube: return 1;
        case UniformType::UIntImageBuffer: return 1;
        case UniformType::UIntImage1DArray: return 1;
        case UniformType::UIntImage2DArray: return 1;
        case UniformType::UIntImage2DMultisample: return 1;
        case UniformType::UIntImage2DMultisampleArray: return 1;
        case UniformType::UIntAtomicCounter: return 1;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GLGetNumCols(const UniformType Type)
    {
        switch (Type)
        {
        case UniformType::Float: return 1;
        case UniformType::FloatVec2: return 2;
        case UniformType::FloatVec3: return 3;
        case UniformType::FloatVec4: return 4;
        case UniformType::Double: return 1;
        case UniformType::DoubleVec2: return 2;
        case UniformType::DoubleVec3: return 3;
        case UniformType::DoubleVec4: return 4;
        case UniformType::Int: return 1;
        case UniformType::IntVec2: return 2;
        case UniformType::IntVec3: return 3;
        case UniformType::IntVec4: return 4;
        case UniformType::UInt: return 1;
        case UniformType::UIntVec2: return 2;
        case UniformType::UIntVec3: return 3;
        case UniformType::UIntVec4: return 4;
        case UniformType::Bool: return 1;
        case UniformType::BoolVec2: return 2;
        case UniformType::BoolVec3: return 3;
        case UniformType::BoolVec4: return 4;
        case UniformType::FloatMat2: return 2;
        case UniformType::FloatMat3: return 3;
        case UniformType::FloatMat4: return 4;
        case UniformType::FloatMat2x3: return 2;
        case UniformType::FloatMat2x4: return 2;
        case UniformType::FloatMat3x2: return 3;
        case UniformType::FloatMat3x4: return 3;
        case UniformType::FloatMat4x2: return 4;
        case UniformType::FloatMat4x3: return 4;
        case UniformType::DoubleMat2: return 2;
        case UniformType::DoubleMat3: return 3;
        case UniformType::DoubleMat4: return 4;
        case UniformType::DoubleMat2x3: return 2;
        case UniformType::DoubleMat2x4: return 2;
        case UniformType::DoubleMat3x2: return 3;
        case UniformType::DoubleMat3x4: return 3;
        case UniformType::DoubleMat4x2: return 4;
        case UniformType::DoubleMat4x3: return 4;
        case UniformType::Sampler1D: return 1;
        case UniformType::Sampler2D: return 1;
        case UniformType::Sampler3D: return 1;
        case UniformType::SamplerCube: return 1;
        case UniformType::Sampler1DShadow: return 1;
        case UniformType::Sampler2DShadow: return 1;
        case UniformType::Sampler1DArray: return 1;
        case UniformType::Sampler2DArray: return 1;
        case UniformType::Sampler1DArrayShadow: return 1;
        case UniformType::Sampler2DArrayShadow: return 1;
        case UniformType::Sampler2DMultisample: return 1;
        case UniformType::Sampler2DMultisampleArray: return 1;
        case UniformType::SamplerCubeShadow: return 1;
        case UniformType::SamplerBuffer: return 1;
        case UniformType::Sampler2DRect: return 1;
        case UniformType::Sampler2DRectShadow: return 1;
        case UniformType::IntSampler1D: return 1;
        case UniformType::IntSampler2D: return 1;
        case UniformType::IntSampler3D: return 1;
        case UniformType::IntSamplerCube: return 1;
        case UniformType::IntSampler1DArray: return 1;
        case UniformType::IntSampler2DArray: return 1;
        case UniformType::IntSampler2DMultisample: return 1;
        case UniformType::IntSampler2DMultisampleArray: return 1;
        case UniformType::IntSamplerBuffer: return 1;
        case UniformType::IntSampler2DRect: return 1;
        case UniformType::UIntSampler1D: return 1;
        case UniformType::UIntSampler2D: return 1;
        case UniformType::UIntSampler3D: return 1;
        case UniformType::UIntSamplerCube: return 1;
        case UniformType::UIntSampler1DArray: return 1;
        case UniformType::UIntSampler2DArray: return 1;
        case UniformType::UIntSampler2DMultisample: return 1;
        case UniformType::UIntSampler2DMultisampleArray: return 1;
        case UniformType::UIntSamplerBuffer: return 1;
        case UniformType::UIntSampler2DRect: return 1;
        case UniformType::Image1D: return 1;
        case UniformType::Image2D: return 1;
        case UniformType::Image3D: return 1;
        case UniformType::Image2DRect: return 1;
        case UniformType::ImageCube: return 1;
        case UniformType::ImageBuffer: return 1;
        case UniformType::Image1DArray: return 1;
        case UniformType::Image2DArray: return 1;
        case UniformType::Image2DMultisample: return 1;
        case UniformType::Image2DMultisampleArray: return 1;
        case UniformType::IntImage1D: return 1;
        case UniformType::IntImage2D: return 1;
        case UniformType::IntImage3D: return 1;
        case UniformType::IntImage2DRect: return 1;
        case UniformType::IntImageCube: return 1;
        case UniformType::IntImageBuffer: return 1;
        case UniformType::IntImage1DArray: return 1;
        case UniformType::IntImage2DArray: return 1;
        case UniformType::IntImage2DMultisample: return 1;
        case UniformType::IntImage2DMultisampleArray: return 1;
        case UniformType::UIntImage1D: return 1;
        case UniformType::UIntImage2D: return 1;
        case UniformType::UIntImage3D: return 1;
        case UniformType::UIntImage2DRect: return 1;
        case UniformType::UIntImageCube: return 1;
        case UniformType::UIntImageBuffer: return 1;
        case UniformType::UIntImage1DArray: return 1;
        case UniformType::UIntImage2DArray: return 1;
        case UniformType::UIntImage2DMultisample: return 1;
        case UniformType::UIntImage2DMultisampleArray: return 1;
        case UniformType::UIntAtomicCounter: return 1;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    GLVarType GLGetVarType(const UniformType Type)
    {
        switch (Type)
        {
        case UniformType::Bool:
        case UniformType::BoolVec2:
        case UniformType::BoolVec3:
        case UniformType::BoolVec4: return GLVarType::Bool;
        case UniformType::Float:
        case UniformType::FloatVec2:
        case UniformType::FloatVec3:
        case UniformType::FloatVec4:
        case UniformType::FloatMat2:
        case UniformType::FloatMat3:
        case UniformType::FloatMat4:
        case UniformType::FloatMat2x3:
        case UniformType::FloatMat2x4:
        case UniformType::FloatMat3x2:
        case UniformType::FloatMat3x4:
        case UniformType::FloatMat4x2:
        case UniformType::FloatMat4x3: return GLVarType::Float;
        case UniformType::Double:
        case UniformType::DoubleVec2:
        case UniformType::DoubleVec3:
        case UniformType::DoubleVec4:
        case UniformType::DoubleMat2:
        case UniformType::DoubleMat3:
        case UniformType::DoubleMat4:
        case UniformType::DoubleMat2x3:
        case UniformType::DoubleMat2x4:
        case UniformType::DoubleMat3x2:
        case UniformType::DoubleMat3x4:
        case UniformType::DoubleMat4x2:
        case UniformType::DoubleMat4x3: return GLVarType::Double;
        case UniformType::Int:
        case UniformType::IntVec2:
        case UniformType::IntVec3:
        case UniformType::IntVec4: return GLVarType::Int;
        case UniformType::UInt:
        case UniformType::UIntVec2:
        case UniformType::UIntVec3:
        case UniformType::UIntVec4: return GLVarType::UInt;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GLGetNumUnits(const UniformType Type)
    {
        return GLGetNumRows(Type) * GLGetNumCols(Type);
    }

    int GLGetRowLength(const UniformType Type)
    {
        return GLGetNumRows(Type) * GLGetUnitLength(Type);
    }

    bool GLIsInteger(const UniformType Type)
    {
        return GLIsInteger(GLGetVarType(Type));
    }

    bool GLIsDouble(const UniformType Type)
    {
        return GLIsDouble(GLGetVarType(Type));
    }

    int GLGetUnitLength(const UniformType Type)
    {
        return GLGetUnitLength(GLGetVarType(Type));
    }

    const char *GLUniformTypeToString(const UniformType Type)
    {
        switch (Type)
        {
        case UniformType::Float: return "float";
        case UniformType::FloatVec2: return "vec2";
        case UniformType::FloatVec3: return "vec3";
        case UniformType::FloatVec4: return "vec4";
        case UniformType::Double: return "double";
        case UniformType::DoubleVec2: return "dvec2";
        case UniformType::DoubleVec3: return "dvec3";
        case UniformType::DoubleVec4: return "dvec4";
        case UniformType::Int: return "int";
        case UniformType::IntVec2: return "ivec2";
        case UniformType::IntVec3: return "ivec3";
        case UniformType::IntVec4: return "ivec4";
        case UniformType::UInt: return "unsigned int";
        case UniformType::UIntVec2: return "uvec2";
        case UniformType::UIntVec3: return "uvec3";
        case UniformType::UIntVec4: return "uvec4";
        case UniformType::Bool: return "bool";
        case UniformType::BoolVec2: return "bvec2";
        case UniformType::BoolVec3: return "bvec3";
        case UniformType::BoolVec4: return "bvec4";
        case UniformType::FloatMat2: return "mat2";
        case UniformType::FloatMat3: return "mat3";
        case UniformType::FloatMat4: return "mat4";
        case UniformType::FloatMat2x3: return "mat2x3";
        case UniformType::FloatMat2x4: return "mat2x4";
        case UniformType::FloatMat3x2: return "mat3x2";
        case UniformType::FloatMat3x4: return "mat3x4";
        case UniformType::FloatMat4x2: return "mat4x2";
        case UniformType::FloatMat4x3: return "mat4x3";
        case UniformType::DoubleMat2: return "dmat2";
        case UniformType::DoubleMat3: return "dmat3";
        case UniformType::DoubleMat4: return "dmat4";
        case UniformType::DoubleMat2x3: return "dmat2x3";
        case UniformType::DoubleMat2x4: return "dmat2x4";
        case UniformType::DoubleMat3x2: return "dmat3x2";
        case UniformType::DoubleMat3x4: return "dmat3x4";
        case UniformType::DoubleMat4x2: return "dmat4x2";
        case UniformType::DoubleMat4x3: return "dmat4x3";
        case UniformType::Sampler1D: return "sampler1D";
        case UniformType::Sampler2D: return "sampler2D";
        case UniformType::Sampler3D: return "sampler3D";
        case UniformType::SamplerCube: return "samplerCube";
        case UniformType::Sampler1DShadow: return "sampler1DShadow";
        case UniformType::Sampler2DShadow: return "sampler2DShadow";
        case UniformType::Sampler1DArray: return "sampler1DArray";
        case UniformType::Sampler2DArray: return "sampler2DArray";
        case UniformType::Sampler1DArrayShadow: return "sampler1DArrayShadow";
        case UniformType::Sampler2DArrayShadow: return "sampler2DArrayShadow";
        case UniformType::Sampler2DMultisample: return "sampler2DMS";
        case UniformType::Sampler2DMultisampleArray: return "sampler2DMSArray";
        case UniformType::SamplerCubeShadow: return "samplerCubeShadow";
        case UniformType::SamplerBuffer: return "samplerBuffer";
        case UniformType::Sampler2DRect: return "sampler2DRect";
        case UniformType::Sampler2DRectShadow: return "sampler2DRectShadow";
        case UniformType::IntSampler1D: return "isampler1D";
        case UniformType::IntSampler2D: return "isampler2D";
        case UniformType::IntSampler3D: return "isampler3D";
        case UniformType::IntSamplerCube: return "isamplerCube";
        case UniformType::IntSampler1DArray: return "isampler1DArray";
        case UniformType::IntSampler2DArray: return "isampler2DArray";
        case UniformType::IntSampler2DMultisample: return "isampler2DMS";
        case UniformType::IntSampler2DMultisampleArray: return "isampler2DMSArray";
        case UniformType::IntSamplerBuffer: return "isamplerBuffer";
        case UniformType::IntSampler2DRect: return "isampler2DRect";
        case UniformType::UIntSampler1D: return "usampler1D";
        case UniformType::UIntSampler2D: return "usampler2D";
        case UniformType::UIntSampler3D: return "usampler3D";
        case UniformType::UIntSamplerCube: return "usamplerCube";
        case UniformType::UIntSampler1DArray: return "usampler2DArray";
        case UniformType::UIntSampler2DArray: return "usampler2DArray";
        case UniformType::UIntSampler2DMultisample: return "usampler2DMS";
        case UniformType::UIntSampler2DMultisampleArray: return "usampler2DMSArray";
        case UniformType::UIntSamplerBuffer: return "usamplerBuffer";
        case UniformType::UIntSampler2DRect: return "usampler2DRect";
        case UniformType::Image1D: return "image1D";
        case UniformType::Image2D: return "image2D";
        case UniformType::Image3D: return "image3D";
        case UniformType::Image2DRect: return "image2DRect";
        case UniformType::ImageCube: return "imageCube";
        case UniformType::ImageBuffer: return "imageBuffer";
        case UniformType::Image1DArray: return "image1DArray";
        case UniformType::Image2DArray: return "image2DArray";
        case UniformType::Image2DMultisample: return "image2DMS";
        case UniformType::Image2DMultisampleArray: return "image2DMSArray";
        case UniformType::IntImage1D: return "iimage1D";
        case UniformType::IntImage2D: return "iimage2D";
        case UniformType::IntImage3D: return "iimage3D";
        case UniformType::IntImage2DRect: return "iimage2DRect";
        case UniformType::IntImageCube: return "iimageCube";
        case UniformType::IntImageBuffer: return "iimageBuffer";
        case UniformType::IntImage1DArray: return "iimage1DArray";
        case UniformType::IntImage2DArray: return "iimage2DArray";
        case UniformType::IntImage2DMultisample: return "iimage2DMS";
        case UniformType::IntImage2DMultisampleArray: return "iimage2DMSArray";
        case UniformType::UIntImage1D: return "uimage1D";
        case UniformType::UIntImage2D: return "uimage2D";
        case UniformType::UIntImage3D: return "uimage3D";
        case UniformType::UIntImage2DRect: return "uimage2DRect";
        case UniformType::UIntImageCube: return "uimageCube";
        case UniformType::UIntImageBuffer: return "uimageBuffer";
        case UniformType::UIntImage1DArray: return "uimage1DArray";
        case UniformType::UIntImage2DArray: return "uimage2DArray";
        case UniformType::UIntImage2DMultisample: return "uimage2DMS";
        case UniformType::UIntImage2DMultisampleArray: return "uimage2DMSArray";
        case UniformType::UIntAtomicCounter: return "atomic_uint";
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    UniformType GLStringToUniformType(std::string str)
    {
        if (!str.compare("float")) return UniformType::Float;
        if (!str.compare("vec2")) return UniformType::FloatVec2;
        if (!str.compare("vec3")) return UniformType::FloatVec3;
        if (!str.compare("vec4")) return UniformType::FloatVec4;
        if (!str.compare("double")) return UniformType::Double;
        if (!str.compare("dvec2")) return UniformType::DoubleVec2;
        if (!str.compare("dvec3")) return UniformType::DoubleVec3;
        if (!str.compare("dvec4")) return UniformType::DoubleVec4;
        if (!str.compare("int")) return UniformType::Int;
        if (!str.compare("ivec2")) return UniformType::IntVec2;
        if (!str.compare("ivec3")) return UniformType::IntVec3;
        if (!str.compare("ivec4")) return UniformType::IntVec4;
        if (!str.compare("unsigned int")) return UniformType::UInt;
        if (!str.compare("uvec2")) return UniformType::UIntVec2;
        if (!str.compare("uvec3")) return UniformType::UIntVec3;
        if (!str.compare("uvec4")) return UniformType::UIntVec4;
        if (!str.compare("bool")) return UniformType::Bool;
        if (!str.compare("bvec2")) return UniformType::BoolVec2;
        if (!str.compare("bvec3")) return UniformType::BoolVec3;
        if (!str.compare("bvec4")) return UniformType::BoolVec4;
        if (!str.compare("mat2")) return UniformType::FloatMat2;
        if (!str.compare("mat3")) return UniformType::FloatMat3;
        if (!str.compare("mat4")) return UniformType::FloatMat4;
        if (!str.compare("mat2x3")) return UniformType::FloatMat2x3;
        if (!str.compare("mat2x4")) return UniformType::FloatMat2x4;
        if (!str.compare("mat3x2")) return UniformType::FloatMat3x2;
        if (!str.compare("mat3x4")) return UniformType::FloatMat3x4;
        if (!str.compare("mat4x2")) return UniformType::FloatMat4x2;
        if (!str.compare("mat4x3")) return UniformType::FloatMat4x3;
        if (!str.compare("dmat2")) return UniformType::DoubleMat2;
        if (!str.compare("dmat3")) return UniformType::DoubleMat3;
        if (!str.compare("dmat4")) return UniformType::DoubleMat4;
        if (!str.compare("dmat2x3")) return UniformType::DoubleMat2x3;
        if (!str.compare("dmat2x4")) return UniformType::DoubleMat2x4;
        if (!str.compare("dmat3x2")) return UniformType::DoubleMat3x2;
        if (!str.compare("dmat3x4")) return UniformType::DoubleMat3x4;
        if (!str.compare("dmat4x2")) return UniformType::DoubleMat4x2;
        if (!str.compare("dmat4x3")) return UniformType::DoubleMat4x3;
        if (!str.compare("sampler1D")) return UniformType::Sampler1D;
        if (!str.compare("sampler2D")) return UniformType::Sampler2D;
        if (!str.compare("sampler3D")) return UniformType::Sampler3D;
        if (!str.compare("samplerCube")) return UniformType::SamplerCube;
        if (!str.compare("sampler1DShadow")) return UniformType::Sampler1DShadow;
        if (!str.compare("sampler2DShadow")) return UniformType::Sampler2DShadow;
        if (!str.compare("sampler1DArray")) return UniformType::Sampler1DArray;
        if (!str.compare("sampler2DArray")) return UniformType::Sampler2DArray;
        if (!str.compare("sampler1DArrayShadow")) return UniformType::Sampler1DArrayShadow;
        if (!str.compare("sampler2DArrayShadow")) return UniformType::Sampler2DArrayShadow;
        if (!str.compare("sampler2DMS")) return UniformType::Sampler2DMultisample;
        if (!str.compare("sampler2DMSArray")) return UniformType::Sampler2DMultisampleArray;
        if (!str.compare("samplerCubeShadow")) return UniformType::SamplerCubeShadow;
        if (!str.compare("samplerBuffer")) return UniformType::SamplerBuffer;
        if (!str.compare("sampler2DRect")) return UniformType::Sampler2DRect;
        if (!str.compare("sampler2DRectShadow")) return UniformType::Sampler2DRectShadow;
        if (!str.compare("isampler1D")) return UniformType::IntSampler1D;
        if (!str.compare("isampler2D")) return UniformType::IntSampler2D;
        if (!str.compare("isampler3D")) return UniformType::IntSampler3D;
        if (!str.compare("isamplerCube")) return UniformType::IntSamplerCube;
        if (!str.compare("isampler1DArray")) return UniformType::IntSampler1DArray;
        if (!str.compare("isampler2DArray")) return UniformType::IntSampler2DArray;
        if (!str.compare("isampler2DMS")) return UniformType::IntSampler2DMultisample;
        if (!str.compare("isampler2DMSArray")) return UniformType::IntSampler2DMultisampleArray;
        if (!str.compare("isamplerBuffer")) return UniformType::IntSamplerBuffer;
        if (!str.compare("isampler2DRect")) return UniformType::IntSampler2DRect;
        if (!str.compare("usampler1D")) return UniformType::UIntSampler1D;
        if (!str.compare("usampler2D")) return UniformType::UIntSampler2D;
        if (!str.compare("usampler3D")) return UniformType::UIntSampler3D;
        if (!str.compare("usamplerCube")) return UniformType::UIntSamplerCube;
        if (!str.compare("usampler2DArray")) return UniformType::UIntSampler1DArray;
        if (!str.compare("usampler2DArray")) return UniformType::UIntSampler2DArray;
        if (!str.compare("usampler2DMS")) return UniformType::UIntSampler2DMultisample;
        if (!str.compare("usampler2DMSArray")) return UniformType::UIntSampler2DMultisampleArray;
        if (!str.compare("usamplerBuffer")) return UniformType::UIntSamplerBuffer;
        if (!str.compare("usampler2DRect")) return UniformType::UIntSampler2DRect;
        if (!str.compare("image1D")) return UniformType::Image1D;
        if (!str.compare("image2D")) return UniformType::Image2D;
        if (!str.compare("image3D")) return UniformType::Image3D;
        if (!str.compare("image2DRect")) return UniformType::Image2DRect;
        if (!str.compare("imageCube")) return UniformType::ImageCube;
        if (!str.compare("imageBuffer")) return UniformType::ImageBuffer;
        if (!str.compare("image1DArray")) return UniformType::Image1DArray;
        if (!str.compare("image2DArray")) return UniformType::Image2DArray;
        if (!str.compare("image2DMS")) return UniformType::Image2DMultisample;
        if (!str.compare("image2DMSArray")) return UniformType::Image2DMultisampleArray;
        if (!str.compare("iimage1D")) return UniformType::IntImage1D;
        if (!str.compare("iimage2D")) return UniformType::IntImage2D;
        if (!str.compare("iimage3D")) return UniformType::IntImage3D;
        if (!str.compare("iimage2DRect")) return UniformType::IntImage2DRect;
        if (!str.compare("iimageCube")) return UniformType::IntImageCube;
        if (!str.compare("iimageBuffer")) return UniformType::IntImageBuffer;
        if (!str.compare("iimage1DArray")) return UniformType::IntImage1DArray;
        if (!str.compare("iimage2DArray")) return UniformType::IntImage2DArray;
        if (!str.compare("iimage2DMS")) return UniformType::IntImage2DMultisample;
        if (!str.compare("iimage2DMSArray")) return UniformType::IntImage2DMultisampleArray;
        if (!str.compare("uimage1D")) return UniformType::UIntImage1D;
        if (!str.compare("uimage2D")) return UniformType::UIntImage2D;
        if (!str.compare("uimage3D")) return UniformType::UIntImage3D;
        if (!str.compare("uimage2DRect")) return UniformType::UIntImage2DRect;
        if (!str.compare("uimageCube")) return UniformType::UIntImageCube;
        if (!str.compare("uimageBuffer")) return UniformType::UIntImageBuffer;
        if (!str.compare("uimage1DArray")) return UniformType::UIntImage1DArray;
        if (!str.compare("uimage2DArray")) return UniformType::UIntImage2DArray;
        if (!str.compare("uimage2DMS")) return UniformType::UIntImage2DMultisample;
        if (!str.compare("uimage2DMSArray")) return UniformType::UIntImage2DMultisampleArray;
        if (!str.compare("atomic_uint")) return UniformType::UIntAtomicCounter;
        throw std::invalid_argument(std::string("Invalid `Type`"));
    }

    InvalidUsageException::InvalidUsageException(std::string What) noexcept :
        std::runtime_error(What)
    {
    }
}
