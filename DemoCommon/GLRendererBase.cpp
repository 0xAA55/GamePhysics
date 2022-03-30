#include "GLRendererBase.hpp"
#include <stdexcept>
#include <GL/glew.h>
namespace GLRenderer
{
    int GetNumRows(const AttribTypeEnum Type)
    {
        switch (Type)
        {
        case AttribTypeEnum::Float: return 1;
        case AttribTypeEnum::Vec2: return 1;
        case AttribTypeEnum::Vec3: return 1;
        case AttribTypeEnum::Vec4: return 1;
        case AttribTypeEnum::Mat2: return 2;
        case AttribTypeEnum::Mat3: return 3;
        case AttribTypeEnum::Mat4: return 4;
        case AttribTypeEnum::Mat2x3: return 3;
        case AttribTypeEnum::Mat2x4: return 4;
        case AttribTypeEnum::Mat3x2: return 2;
        case AttribTypeEnum::Mat3x4: return 4;
        case AttribTypeEnum::Mat4x2: return 2;
        case AttribTypeEnum::Mat4x3: return 3;
        case AttribTypeEnum::Int: return 1;
        case AttribTypeEnum::IVec2: return 1;
        case AttribTypeEnum::IVec3: return 1;
        case AttribTypeEnum::IVec4: return 1;
        case AttribTypeEnum::UInt: return 1;
        case AttribTypeEnum::UVec2: return 1;
        case AttribTypeEnum::UVec3: return 1;
        case AttribTypeEnum::UVec4: return 1;
        case AttribTypeEnum::Double: return 1;
        case AttribTypeEnum::DVec2: return 1;
        case AttribTypeEnum::DVec3: return 1;
        case AttribTypeEnum::DVec4: return 1;
        case AttribTypeEnum::DMat2: return 2;
        case AttribTypeEnum::DMat3: return 3;
        case AttribTypeEnum::DMat4: return 4;
        case AttribTypeEnum::DMat2x3: return 3;
        case AttribTypeEnum::DMat2x4: return 4;
        case AttribTypeEnum::DMat3x2: return 2;
        case AttribTypeEnum::DMat3x4: return 4;
        case AttribTypeEnum::DMat4x2: return 2;
        case AttribTypeEnum::DMat4x3: return 3;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GetNumCols(const AttribTypeEnum Type)
    {
        switch (Type)
        {
        case AttribTypeEnum::Float: return 1;
        case AttribTypeEnum::Vec2: return 2;
        case AttribTypeEnum::Vec3: return 3;
        case AttribTypeEnum::Vec4: return 4;
        case AttribTypeEnum::Mat2: return 2;
        case AttribTypeEnum::Mat3: return 3;
        case AttribTypeEnum::Mat4: return 4;
        case AttribTypeEnum::Mat2x3: return 2;
        case AttribTypeEnum::Mat2x4: return 2;
        case AttribTypeEnum::Mat3x2: return 3;
        case AttribTypeEnum::Mat3x4: return 3;
        case AttribTypeEnum::Mat4x2: return 4;
        case AttribTypeEnum::Mat4x3: return 4;
        case AttribTypeEnum::Int: return 1;
        case AttribTypeEnum::IVec2: return 2;
        case AttribTypeEnum::IVec3: return 3;
        case AttribTypeEnum::IVec4: return 4;
        case AttribTypeEnum::UInt: return 1;
        case AttribTypeEnum::UVec2: return 2;
        case AttribTypeEnum::UVec3: return 3;
        case AttribTypeEnum::UVec4: return 4;
        case AttribTypeEnum::Double: return 1;
        case AttribTypeEnum::DVec2: return 2;
        case AttribTypeEnum::DVec3: return 3;
        case AttribTypeEnum::DVec4: return 4;
        case AttribTypeEnum::DMat2: return 2;
        case AttribTypeEnum::DMat3: return 3;
        case AttribTypeEnum::DMat4: return 4;
        case AttribTypeEnum::DMat2x3: return 2;
        case AttribTypeEnum::DMat2x4: return 2;
        case AttribTypeEnum::DMat3x2: return 3;
        case AttribTypeEnum::DMat3x4: return 3;
        case AttribTypeEnum::DMat4x2: return 4;
        case AttribTypeEnum::DMat4x3: return 4;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    VarTypeEnum GetVarType(const AttribTypeEnum Type)
    {
        switch (Type)
        {
        case AttribTypeEnum::Float:
        case AttribTypeEnum::Vec2:
        case AttribTypeEnum::Vec3:
        case AttribTypeEnum::Vec4:
        case AttribTypeEnum::Mat2:
        case AttribTypeEnum::Mat3:
        case AttribTypeEnum::Mat4:
        case AttribTypeEnum::Mat2x3:
        case AttribTypeEnum::Mat2x4:
        case AttribTypeEnum::Mat3x2:
        case AttribTypeEnum::Mat3x4:
        case AttribTypeEnum::Mat4x2:
        case AttribTypeEnum::Mat4x3: return VarTypeEnum::Float;
        case AttribTypeEnum::Int:
        case AttribTypeEnum::IVec2:
        case AttribTypeEnum::IVec3:
        case AttribTypeEnum::IVec4: return VarTypeEnum::Int;
        case AttribTypeEnum::UInt:
        case AttribTypeEnum::UVec2:
        case AttribTypeEnum::UVec3:
        case AttribTypeEnum::UVec4: return VarTypeEnum::UInt;
        case AttribTypeEnum::Double:
        case AttribTypeEnum::DVec2:
        case AttribTypeEnum::DVec3:
        case AttribTypeEnum::DVec4:
        case AttribTypeEnum::DMat2:
        case AttribTypeEnum::DMat3:
        case AttribTypeEnum::DMat4:
        case AttribTypeEnum::DMat2x3:
        case AttribTypeEnum::DMat2x4:
        case AttribTypeEnum::DMat3x2:
        case AttribTypeEnum::DMat3x4:
        case AttribTypeEnum::DMat4x2:
        case AttribTypeEnum::DMat4x3: return VarTypeEnum::Double;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GetNumUnits(const AttribTypeEnum Type)
    {
        return GetNumRows(Type) * GetNumCols(Type);
    }

    int GetRowLength(const AttribTypeEnum Type)
    {
        return GetNumRows(Type) * GetUnitLength(Type);
    }

    bool IsInteger(const AttribTypeEnum Type)
    {
        return IsInteger(GetVarType(Type));
    }

    bool IsInteger(const VarTypeEnum VarType)
    {
        switch (VarType)
        {
        case VarTypeEnum::Int:
        case VarTypeEnum::UInt:
            return true;
        }
        return false;
    }

    bool IsDouble(const AttribTypeEnum Type)
    {
        return IsDouble(GetVarType(Type));
    }

    bool IsDouble(const VarTypeEnum VarType)
    {
        switch (VarType)
        {
        case VarTypeEnum::Double:
            return true;
        }
        return false;
    }
    int GetUnitLength(const AttribTypeEnum Type)
    {
        return GetUnitLength(GetVarType(Type));
    }
    int GetUnitLength(const VarTypeEnum VarType)
    {
        switch (VarType)
        {
        case VarTypeEnum::Bool: return sizeof(GLboolean);
        case VarTypeEnum::Float: return sizeof(GLfloat);
        case VarTypeEnum::Int: return sizeof(GLint);
        case VarTypeEnum::UInt: return sizeof(GLuint);
        case VarTypeEnum::Double: return sizeof(GLdouble);
        default: throw std::invalid_argument(std::string("Invalid `VarType`"));
        }
    }

    const char *AttribTypeToString(const AttribTypeEnum Type)
    {
        switch (Type)
        {
        case AttribTypeEnum::Float: return "float";
        case AttribTypeEnum::Vec2: return "vec2";
        case AttribTypeEnum::Vec3: return "vec3";
        case AttribTypeEnum::Vec4: return "vec4";
        case AttribTypeEnum::Mat2: return "mat2";
        case AttribTypeEnum::Mat3: return "mat3";
        case AttribTypeEnum::Mat4: return "mat4";
        case AttribTypeEnum::Mat2x3: return "mat2x3";
        case AttribTypeEnum::Mat2x4: return "mat2x4";
        case AttribTypeEnum::Mat3x2: return "mat3x2";
        case AttribTypeEnum::Mat3x4: return "mat3x4";
        case AttribTypeEnum::Mat4x2: return "mat4x2";
        case AttribTypeEnum::Mat4x3: return "mat4x3";
        case AttribTypeEnum::Int: return "int";
        case AttribTypeEnum::IVec2: return "ivec2";
        case AttribTypeEnum::IVec3: return "ivec3";
        case AttribTypeEnum::IVec4: return "ivec4";
        case AttribTypeEnum::UInt: return "unsigned int";
        case AttribTypeEnum::UVec2: return "uvec2";
        case AttribTypeEnum::UVec3: return "uvec3";
        case AttribTypeEnum::UVec4: return "uvec4";
        case AttribTypeEnum::Double: return "double";
        case AttribTypeEnum::DVec2: return "dvec2";
        case AttribTypeEnum::DVec3: return "dvec3";
        case AttribTypeEnum::DVec4: return "dvec4";
        case AttribTypeEnum::DMat2: return "dmat2";
        case AttribTypeEnum::DMat3: return "dmat3";
        case AttribTypeEnum::DMat4: return "dmat4";
        case AttribTypeEnum::DMat2x3: return "dmat2x3";
        case AttribTypeEnum::DMat2x4: return "dmat2x4";
        case AttribTypeEnum::DMat3x2: return "dmat3x2";
        case AttribTypeEnum::DMat3x4: return "dmat3x4";
        case AttribTypeEnum::DMat4x2: return "dmat4x2";
        case AttribTypeEnum::DMat4x3: return "dmat4x3";
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    AttribTypeEnum StringToAttribType(std::string str)
    {
        if (!str.compare("float")) return AttribTypeEnum::Float;
        if (!str.compare("vec2")) return AttribTypeEnum::Vec2;
        if (!str.compare("vec3")) return AttribTypeEnum::Vec3;
        if (!str.compare("vec4")) return AttribTypeEnum::Vec4;
        if (!str.compare("mat2")) return AttribTypeEnum::Mat2;
        if (!str.compare("mat3")) return AttribTypeEnum::Mat3;
        if (!str.compare("mat4")) return AttribTypeEnum::Mat4;
        if (!str.compare("mat2x3")) return AttribTypeEnum::Mat2x3;
        if (!str.compare("mat2x4")) return AttribTypeEnum::Mat2x4;
        if (!str.compare("mat3x2")) return AttribTypeEnum::Mat3x2;
        if (!str.compare("mat3x4")) return AttribTypeEnum::Mat3x4;
        if (!str.compare("mat4x2")) return AttribTypeEnum::Mat4x2;
        if (!str.compare("mat4x3")) return AttribTypeEnum::Mat4x3;
        if (!str.compare("int")) return AttribTypeEnum::Int;
        if (!str.compare("ivec2")) return AttribTypeEnum::IVec2;
        if (!str.compare("ivec3")) return AttribTypeEnum::IVec3;
        if (!str.compare("ivec4")) return AttribTypeEnum::IVec4;
        if (!str.compare("unsigned int")) return AttribTypeEnum::UInt;
        if (!str.compare("uvec2")) return AttribTypeEnum::UVec2;
        if (!str.compare("uvec3")) return AttribTypeEnum::UVec3;
        if (!str.compare("uvec4")) return AttribTypeEnum::UVec4;
        if (!str.compare("double")) return AttribTypeEnum::Double;
        if (!str.compare("dvec2")) return AttribTypeEnum::DVec2;
        if (!str.compare("dvec3")) return AttribTypeEnum::DVec3;
        if (!str.compare("dvec4")) return AttribTypeEnum::DVec4;
        if (!str.compare("dmat2")) return AttribTypeEnum::DMat2;
        if (!str.compare("dmat3")) return AttribTypeEnum::DMat3;
        if (!str.compare("dmat4")) return AttribTypeEnum::DMat4;
        if (!str.compare("dmat2x3")) return AttribTypeEnum::DMat2x3;
        if (!str.compare("dmat2x4")) return AttribTypeEnum::DMat2x4;
        if (!str.compare("dmat3x2")) return AttribTypeEnum::DMat3x2;
        if (!str.compare("dmat3x4")) return AttribTypeEnum::DMat3x4;
        if (!str.compare("dmat4x2")) return AttribTypeEnum::DMat4x2;
        if (!str.compare("dmat4x3")) return AttribTypeEnum::DMat4x3;
        throw std::invalid_argument(std::string("Invalid `Type`"));
    }

    int GetNumRows(const UniformTypeEnum Type)
    {
        switch (Type)
        {
        case UniformTypeEnum::Float: return 1;
        case UniformTypeEnum::FloatVec2: return 1;
        case UniformTypeEnum::FloatVec3: return 1;
        case UniformTypeEnum::FloatVec4: return 1;
        case UniformTypeEnum::Double: return 1;
        case UniformTypeEnum::DoubleVec2: return 1;
        case UniformTypeEnum::DoubleVec3: return 1;
        case UniformTypeEnum::DoubleVec4: return 1;
        case UniformTypeEnum::Int: return 1;
        case UniformTypeEnum::IntVec2: return 1;
        case UniformTypeEnum::IntVec3: return 1;
        case UniformTypeEnum::IntVec4: return 1;
        case UniformTypeEnum::UInt: return 1;
        case UniformTypeEnum::UIntVec2: return 1;
        case UniformTypeEnum::UIntVec3: return 1;
        case UniformTypeEnum::UIntVec4: return 1;
        case UniformTypeEnum::Bool: return 1;
        case UniformTypeEnum::BoolVec2: return 1;
        case UniformTypeEnum::BoolVec3: return 1;
        case UniformTypeEnum::BoolVec4: return 1;
        case UniformTypeEnum::FloatMat2: return 2;
        case UniformTypeEnum::FloatMat3: return 3;
        case UniformTypeEnum::FloatMat4: return 4;
        case UniformTypeEnum::FloatMat2x3: return 3;
        case UniformTypeEnum::FloatMat2x4: return 4;
        case UniformTypeEnum::FloatMat3x2: return 2;
        case UniformTypeEnum::FloatMat3x4: return 4;
        case UniformTypeEnum::FloatMat4x2: return 2;
        case UniformTypeEnum::FloatMat4x3: return 3;
        case UniformTypeEnum::DoubleMat2: return 2;
        case UniformTypeEnum::DoubleMat3: return 3;
        case UniformTypeEnum::DoubleMat4: return 4;
        case UniformTypeEnum::DoubleMat2x3: return 3;
        case UniformTypeEnum::DoubleMat2x4: return 4;
        case UniformTypeEnum::DoubleMat3x2: return 2;
        case UniformTypeEnum::DoubleMat3x4: return 4;
        case UniformTypeEnum::DoubleMat4x2: return 2;
        case UniformTypeEnum::DoubleMat4x3: return 3;
        case UniformTypeEnum::Sampler1D: return 1;
        case UniformTypeEnum::Sampler2D: return 1;
        case UniformTypeEnum::Sampler3D: return 1;
        case UniformTypeEnum::SamplerCube: return 1;
        case UniformTypeEnum::Sampler1DShadow: return 1;
        case UniformTypeEnum::Sampler2DShadow: return 1;
        case UniformTypeEnum::Sampler1DArray: return 1;
        case UniformTypeEnum::Sampler2DArray: return 1;
        case UniformTypeEnum::Sampler1DArrayShadow: return 1;
        case UniformTypeEnum::Sampler2DArrayShadow: return 1;
        case UniformTypeEnum::Sampler2DMultisample: return 1;
        case UniformTypeEnum::Sampler2DMultisampleArray: return 1;
        case UniformTypeEnum::SamplerCubeShadow: return 1;
        case UniformTypeEnum::SamplerBuffer: return 1;
        case UniformTypeEnum::Sampler2DRect: return 1;
        case UniformTypeEnum::Sampler2DRectShadow: return 1;
        case UniformTypeEnum::IntSampler1D: return 1;
        case UniformTypeEnum::IntSampler2D: return 1;
        case UniformTypeEnum::IntSampler3D: return 1;
        case UniformTypeEnum::IntSamplerCube: return 1;
        case UniformTypeEnum::IntSampler1DArray: return 1;
        case UniformTypeEnum::IntSampler2DArray: return 1;
        case UniformTypeEnum::IntSampler2DMultisample: return 1;
        case UniformTypeEnum::IntSampler2DMultisampleArray: return 1;
        case UniformTypeEnum::IntSamplerBuffer: return 1;
        case UniformTypeEnum::IntSampler2DRect: return 1;
        case UniformTypeEnum::UIntSampler1D: return 1;
        case UniformTypeEnum::UIntSampler2D: return 1;
        case UniformTypeEnum::UIntSampler3D: return 1;
        case UniformTypeEnum::UIntSamplerCube: return 1;
        case UniformTypeEnum::UIntSampler1DArray: return 1;
        case UniformTypeEnum::UIntSampler2DArray: return 1;
        case UniformTypeEnum::UIntSampler2DMultisample: return 1;
        case UniformTypeEnum::UIntSampler2DMultisampleArray: return 1;
        case UniformTypeEnum::UIntSamplerBuffer: return 1;
        case UniformTypeEnum::UIntSampler2DRect: return 1;
        case UniformTypeEnum::Image1D: return 1;
        case UniformTypeEnum::Image2D: return 1;
        case UniformTypeEnum::Image3D: return 1;
        case UniformTypeEnum::Image2DRect: return 1;
        case UniformTypeEnum::ImageCube: return 1;
        case UniformTypeEnum::ImageBuffer: return 1;
        case UniformTypeEnum::Image1DArray: return 1;
        case UniformTypeEnum::Image2DArray: return 1;
        case UniformTypeEnum::Image2DMultisample: return 1;
        case UniformTypeEnum::Image2DMultisampleArray: return 1;
        case UniformTypeEnum::IntImage1D: return 1;
        case UniformTypeEnum::IntImage2D: return 1;
        case UniformTypeEnum::IntImage3D: return 1;
        case UniformTypeEnum::IntImage2DRect: return 1;
        case UniformTypeEnum::IntImageCube: return 1;
        case UniformTypeEnum::IntImageBuffer: return 1;
        case UniformTypeEnum::IntImage1DArray: return 1;
        case UniformTypeEnum::IntImage2DArray: return 1;
        case UniformTypeEnum::IntImage2DMultisample: return 1;
        case UniformTypeEnum::IntImage2DMultisampleArray: return 1;
        case UniformTypeEnum::UIntImage1D: return 1;
        case UniformTypeEnum::UIntImage2D: return 1;
        case UniformTypeEnum::UIntImage3D: return 1;
        case UniformTypeEnum::UIntImage2DRect: return 1;
        case UniformTypeEnum::UIntImageCube: return 1;
        case UniformTypeEnum::UIntImageBuffer: return 1;
        case UniformTypeEnum::UIntImage1DArray: return 1;
        case UniformTypeEnum::UIntImage2DArray: return 1;
        case UniformTypeEnum::UIntImage2DMultisample: return 1;
        case UniformTypeEnum::UIntImage2DMultisampleArray: return 1;
        case UniformTypeEnum::UIntAtomicCounter: return 1;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GetNumCols(const UniformTypeEnum Type)
    {
        switch (Type)
        {
        case UniformTypeEnum::Float: return 1;
        case UniformTypeEnum::FloatVec2: return 2;
        case UniformTypeEnum::FloatVec3: return 3;
        case UniformTypeEnum::FloatVec4: return 4;
        case UniformTypeEnum::Double: return 1;
        case UniformTypeEnum::DoubleVec2: return 2;
        case UniformTypeEnum::DoubleVec3: return 3;
        case UniformTypeEnum::DoubleVec4: return 4;
        case UniformTypeEnum::Int: return 1;
        case UniformTypeEnum::IntVec2: return 2;
        case UniformTypeEnum::IntVec3: return 3;
        case UniformTypeEnum::IntVec4: return 4;
        case UniformTypeEnum::UInt: return 1;
        case UniformTypeEnum::UIntVec2: return 2;
        case UniformTypeEnum::UIntVec3: return 3;
        case UniformTypeEnum::UIntVec4: return 4;
        case UniformTypeEnum::Bool: return 1;
        case UniformTypeEnum::BoolVec2: return 2;
        case UniformTypeEnum::BoolVec3: return 3;
        case UniformTypeEnum::BoolVec4: return 4;
        case UniformTypeEnum::FloatMat2: return 2;
        case UniformTypeEnum::FloatMat3: return 3;
        case UniformTypeEnum::FloatMat4: return 4;
        case UniformTypeEnum::FloatMat2x3: return 2;
        case UniformTypeEnum::FloatMat2x4: return 2;
        case UniformTypeEnum::FloatMat3x2: return 3;
        case UniformTypeEnum::FloatMat3x4: return 3;
        case UniformTypeEnum::FloatMat4x2: return 4;
        case UniformTypeEnum::FloatMat4x3: return 4;
        case UniformTypeEnum::DoubleMat2: return 2;
        case UniformTypeEnum::DoubleMat3: return 3;
        case UniformTypeEnum::DoubleMat4: return 4;
        case UniformTypeEnum::DoubleMat2x3: return 2;
        case UniformTypeEnum::DoubleMat2x4: return 2;
        case UniformTypeEnum::DoubleMat3x2: return 3;
        case UniformTypeEnum::DoubleMat3x4: return 3;
        case UniformTypeEnum::DoubleMat4x2: return 4;
        case UniformTypeEnum::DoubleMat4x3: return 4;
        case UniformTypeEnum::Sampler1D: return 1;
        case UniformTypeEnum::Sampler2D: return 1;
        case UniformTypeEnum::Sampler3D: return 1;
        case UniformTypeEnum::SamplerCube: return 1;
        case UniformTypeEnum::Sampler1DShadow: return 1;
        case UniformTypeEnum::Sampler2DShadow: return 1;
        case UniformTypeEnum::Sampler1DArray: return 1;
        case UniformTypeEnum::Sampler2DArray: return 1;
        case UniformTypeEnum::Sampler1DArrayShadow: return 1;
        case UniformTypeEnum::Sampler2DArrayShadow: return 1;
        case UniformTypeEnum::Sampler2DMultisample: return 1;
        case UniformTypeEnum::Sampler2DMultisampleArray: return 1;
        case UniformTypeEnum::SamplerCubeShadow: return 1;
        case UniformTypeEnum::SamplerBuffer: return 1;
        case UniformTypeEnum::Sampler2DRect: return 1;
        case UniformTypeEnum::Sampler2DRectShadow: return 1;
        case UniformTypeEnum::IntSampler1D: return 1;
        case UniformTypeEnum::IntSampler2D: return 1;
        case UniformTypeEnum::IntSampler3D: return 1;
        case UniformTypeEnum::IntSamplerCube: return 1;
        case UniformTypeEnum::IntSampler1DArray: return 1;
        case UniformTypeEnum::IntSampler2DArray: return 1;
        case UniformTypeEnum::IntSampler2DMultisample: return 1;
        case UniformTypeEnum::IntSampler2DMultisampleArray: return 1;
        case UniformTypeEnum::IntSamplerBuffer: return 1;
        case UniformTypeEnum::IntSampler2DRect: return 1;
        case UniformTypeEnum::UIntSampler1D: return 1;
        case UniformTypeEnum::UIntSampler2D: return 1;
        case UniformTypeEnum::UIntSampler3D: return 1;
        case UniformTypeEnum::UIntSamplerCube: return 1;
        case UniformTypeEnum::UIntSampler1DArray: return 1;
        case UniformTypeEnum::UIntSampler2DArray: return 1;
        case UniformTypeEnum::UIntSampler2DMultisample: return 1;
        case UniformTypeEnum::UIntSampler2DMultisampleArray: return 1;
        case UniformTypeEnum::UIntSamplerBuffer: return 1;
        case UniformTypeEnum::UIntSampler2DRect: return 1;
        case UniformTypeEnum::Image1D: return 1;
        case UniformTypeEnum::Image2D: return 1;
        case UniformTypeEnum::Image3D: return 1;
        case UniformTypeEnum::Image2DRect: return 1;
        case UniformTypeEnum::ImageCube: return 1;
        case UniformTypeEnum::ImageBuffer: return 1;
        case UniformTypeEnum::Image1DArray: return 1;
        case UniformTypeEnum::Image2DArray: return 1;
        case UniformTypeEnum::Image2DMultisample: return 1;
        case UniformTypeEnum::Image2DMultisampleArray: return 1;
        case UniformTypeEnum::IntImage1D: return 1;
        case UniformTypeEnum::IntImage2D: return 1;
        case UniformTypeEnum::IntImage3D: return 1;
        case UniformTypeEnum::IntImage2DRect: return 1;
        case UniformTypeEnum::IntImageCube: return 1;
        case UniformTypeEnum::IntImageBuffer: return 1;
        case UniformTypeEnum::IntImage1DArray: return 1;
        case UniformTypeEnum::IntImage2DArray: return 1;
        case UniformTypeEnum::IntImage2DMultisample: return 1;
        case UniformTypeEnum::IntImage2DMultisampleArray: return 1;
        case UniformTypeEnum::UIntImage1D: return 1;
        case UniformTypeEnum::UIntImage2D: return 1;
        case UniformTypeEnum::UIntImage3D: return 1;
        case UniformTypeEnum::UIntImage2DRect: return 1;
        case UniformTypeEnum::UIntImageCube: return 1;
        case UniformTypeEnum::UIntImageBuffer: return 1;
        case UniformTypeEnum::UIntImage1DArray: return 1;
        case UniformTypeEnum::UIntImage2DArray: return 1;
        case UniformTypeEnum::UIntImage2DMultisample: return 1;
        case UniformTypeEnum::UIntImage2DMultisampleArray: return 1;
        case UniformTypeEnum::UIntAtomicCounter: return 1;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    VarTypeEnum GetVarType(const UniformTypeEnum Type)
    {
        switch (Type)
        {
        case UniformTypeEnum::Bool:
        case UniformTypeEnum::BoolVec2:
        case UniformTypeEnum::BoolVec3:
        case UniformTypeEnum::BoolVec4: return VarTypeEnum::Bool;
        case UniformTypeEnum::Float:
        case UniformTypeEnum::FloatVec2:
        case UniformTypeEnum::FloatVec3:
        case UniformTypeEnum::FloatVec4:
        case UniformTypeEnum::FloatMat2:
        case UniformTypeEnum::FloatMat3:
        case UniformTypeEnum::FloatMat4:
        case UniformTypeEnum::FloatMat2x3:
        case UniformTypeEnum::FloatMat2x4:
        case UniformTypeEnum::FloatMat3x2:
        case UniformTypeEnum::FloatMat3x4:
        case UniformTypeEnum::FloatMat4x2:
        case UniformTypeEnum::FloatMat4x3: return VarTypeEnum::Float;
        case UniformTypeEnum::Double:
        case UniformTypeEnum::DoubleVec2:
        case UniformTypeEnum::DoubleVec3:
        case UniformTypeEnum::DoubleVec4:
        case UniformTypeEnum::DoubleMat2:
        case UniformTypeEnum::DoubleMat3:
        case UniformTypeEnum::DoubleMat4:
        case UniformTypeEnum::DoubleMat2x3:
        case UniformTypeEnum::DoubleMat2x4:
        case UniformTypeEnum::DoubleMat3x2:
        case UniformTypeEnum::DoubleMat3x4:
        case UniformTypeEnum::DoubleMat4x2:
        case UniformTypeEnum::DoubleMat4x3: return VarTypeEnum::Double;
        case UniformTypeEnum::Int:
        case UniformTypeEnum::IntVec2:
        case UniformTypeEnum::IntVec3:
        case UniformTypeEnum::IntVec4: return VarTypeEnum::Int;
        case UniformTypeEnum::UInt:
        case UniformTypeEnum::UIntVec2:
        case UniformTypeEnum::UIntVec3:
        case UniformTypeEnum::UIntVec4: return VarTypeEnum::UInt;
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    int GetNumUnits(const UniformTypeEnum Type)
    {
        return GetNumRows(Type) * GetNumCols(Type);
    }

    int GetRowLength(const UniformTypeEnum Type)
    {
        return GetNumRows(Type) * GetUnitLength(Type);
    }

    bool IsInteger(const UniformTypeEnum Type)
    {
        return IsInteger(GetVarType(Type));
    }

    bool IsDouble(const UniformTypeEnum Type)
    {
        return IsDouble(GetVarType(Type));
    }

    int GetUnitLength(const UniformTypeEnum Type)
    {
        return GetUnitLength(GetVarType(Type));
    }

    const char *UniformTypeToString(const UniformTypeEnum Type)
    {
        switch (Type)
        {
        case UniformTypeEnum::Float: return "float";
        case UniformTypeEnum::FloatVec2: return "vec2";
        case UniformTypeEnum::FloatVec3: return "vec3";
        case UniformTypeEnum::FloatVec4: return "vec4";
        case UniformTypeEnum::Double: return "double";
        case UniformTypeEnum::DoubleVec2: return "dvec2";
        case UniformTypeEnum::DoubleVec3: return "dvec3";
        case UniformTypeEnum::DoubleVec4: return "dvec4";
        case UniformTypeEnum::Int: return "int";
        case UniformTypeEnum::IntVec2: return "ivec2";
        case UniformTypeEnum::IntVec3: return "ivec3";
        case UniformTypeEnum::IntVec4: return "ivec4";
        case UniformTypeEnum::UInt: return "unsigned int";
        case UniformTypeEnum::UIntVec2: return "uvec2";
        case UniformTypeEnum::UIntVec3: return "uvec3";
        case UniformTypeEnum::UIntVec4: return "uvec4";
        case UniformTypeEnum::Bool: return "bool";
        case UniformTypeEnum::BoolVec2: return "bvec2";
        case UniformTypeEnum::BoolVec3: return "bvec3";
        case UniformTypeEnum::BoolVec4: return "bvec4";
        case UniformTypeEnum::FloatMat2: return "mat2";
        case UniformTypeEnum::FloatMat3: return "mat3";
        case UniformTypeEnum::FloatMat4: return "mat4";
        case UniformTypeEnum::FloatMat2x3: return "mat2x3";
        case UniformTypeEnum::FloatMat2x4: return "mat2x4";
        case UniformTypeEnum::FloatMat3x2: return "mat3x2";
        case UniformTypeEnum::FloatMat3x4: return "mat3x4";
        case UniformTypeEnum::FloatMat4x2: return "mat4x2";
        case UniformTypeEnum::FloatMat4x3: return "mat4x3";
        case UniformTypeEnum::DoubleMat2: return "dmat2";
        case UniformTypeEnum::DoubleMat3: return "dmat3";
        case UniformTypeEnum::DoubleMat4: return "dmat4";
        case UniformTypeEnum::DoubleMat2x3: return "dmat2x3";
        case UniformTypeEnum::DoubleMat2x4: return "dmat2x4";
        case UniformTypeEnum::DoubleMat3x2: return "dmat3x2";
        case UniformTypeEnum::DoubleMat3x4: return "dmat3x4";
        case UniformTypeEnum::DoubleMat4x2: return "dmat4x2";
        case UniformTypeEnum::DoubleMat4x3: return "dmat4x3";
        case UniformTypeEnum::Sampler1D: return "sampler1D";
        case UniformTypeEnum::Sampler2D: return "sampler2D";
        case UniformTypeEnum::Sampler3D: return "sampler3D";
        case UniformTypeEnum::SamplerCube: return "samplerCube";
        case UniformTypeEnum::Sampler1DShadow: return "sampler1DShadow";
        case UniformTypeEnum::Sampler2DShadow: return "sampler2DShadow";
        case UniformTypeEnum::Sampler1DArray: return "sampler1DArray";
        case UniformTypeEnum::Sampler2DArray: return "sampler2DArray";
        case UniformTypeEnum::Sampler1DArrayShadow: return "sampler1DArrayShadow";
        case UniformTypeEnum::Sampler2DArrayShadow: return "sampler2DArrayShadow";
        case UniformTypeEnum::Sampler2DMultisample: return "sampler2DMS";
        case UniformTypeEnum::Sampler2DMultisampleArray: return "sampler2DMSArray";
        case UniformTypeEnum::SamplerCubeShadow: return "samplerCubeShadow";
        case UniformTypeEnum::SamplerBuffer: return "samplerBuffer";
        case UniformTypeEnum::Sampler2DRect: return "sampler2DRect";
        case UniformTypeEnum::Sampler2DRectShadow: return "sampler2DRectShadow";
        case UniformTypeEnum::IntSampler1D: return "isampler1D";
        case UniformTypeEnum::IntSampler2D: return "isampler2D";
        case UniformTypeEnum::IntSampler3D: return "isampler3D";
        case UniformTypeEnum::IntSamplerCube: return "isamplerCube";
        case UniformTypeEnum::IntSampler1DArray: return "isampler1DArray";
        case UniformTypeEnum::IntSampler2DArray: return "isampler2DArray";
        case UniformTypeEnum::IntSampler2DMultisample: return "isampler2DMS";
        case UniformTypeEnum::IntSampler2DMultisampleArray: return "isampler2DMSArray";
        case UniformTypeEnum::IntSamplerBuffer: return "isamplerBuffer";
        case UniformTypeEnum::IntSampler2DRect: return "isampler2DRect";
        case UniformTypeEnum::UIntSampler1D: return "usampler1D";
        case UniformTypeEnum::UIntSampler2D: return "usampler2D";
        case UniformTypeEnum::UIntSampler3D: return "usampler3D";
        case UniformTypeEnum::UIntSamplerCube: return "usamplerCube";
        case UniformTypeEnum::UIntSampler1DArray: return "usampler2DArray";
        case UniformTypeEnum::UIntSampler2DArray: return "usampler2DArray";
        case UniformTypeEnum::UIntSampler2DMultisample: return "usampler2DMS";
        case UniformTypeEnum::UIntSampler2DMultisampleArray: return "usampler2DMSArray";
        case UniformTypeEnum::UIntSamplerBuffer: return "usamplerBuffer";
        case UniformTypeEnum::UIntSampler2DRect: return "usampler2DRect";
        case UniformTypeEnum::Image1D: return "image1D";
        case UniformTypeEnum::Image2D: return "image2D";
        case UniformTypeEnum::Image3D: return "image3D";
        case UniformTypeEnum::Image2DRect: return "image2DRect";
        case UniformTypeEnum::ImageCube: return "imageCube";
        case UniformTypeEnum::ImageBuffer: return "imageBuffer";
        case UniformTypeEnum::Image1DArray: return "image1DArray";
        case UniformTypeEnum::Image2DArray: return "image2DArray";
        case UniformTypeEnum::Image2DMultisample: return "image2DMS";
        case UniformTypeEnum::Image2DMultisampleArray: return "image2DMSArray";
        case UniformTypeEnum::IntImage1D: return "iimage1D";
        case UniformTypeEnum::IntImage2D: return "iimage2D";
        case UniformTypeEnum::IntImage3D: return "iimage3D";
        case UniformTypeEnum::IntImage2DRect: return "iimage2DRect";
        case UniformTypeEnum::IntImageCube: return "iimageCube";
        case UniformTypeEnum::IntImageBuffer: return "iimageBuffer";
        case UniformTypeEnum::IntImage1DArray: return "iimage1DArray";
        case UniformTypeEnum::IntImage2DArray: return "iimage2DArray";
        case UniformTypeEnum::IntImage2DMultisample: return "iimage2DMS";
        case UniformTypeEnum::IntImage2DMultisampleArray: return "iimage2DMSArray";
        case UniformTypeEnum::UIntImage1D: return "uimage1D";
        case UniformTypeEnum::UIntImage2D: return "uimage2D";
        case UniformTypeEnum::UIntImage3D: return "uimage3D";
        case UniformTypeEnum::UIntImage2DRect: return "uimage2DRect";
        case UniformTypeEnum::UIntImageCube: return "uimageCube";
        case UniformTypeEnum::UIntImageBuffer: return "uimageBuffer";
        case UniformTypeEnum::UIntImage1DArray: return "uimage1DArray";
        case UniformTypeEnum::UIntImage2DArray: return "uimage2DArray";
        case UniformTypeEnum::UIntImage2DMultisample: return "uimage2DMS";
        case UniformTypeEnum::UIntImage2DMultisampleArray: return "uimage2DMSArray";
        case UniformTypeEnum::UIntAtomicCounter: return "atomic_uint";
        default: throw std::invalid_argument(std::string("Invalid `Type`"));
        }
    }

    UniformTypeEnum StringToUniformType(std::string str)
    {
        if (!str.compare("float")) return UniformTypeEnum::Float;
        if (!str.compare("vec2")) return UniformTypeEnum::FloatVec2;
        if (!str.compare("vec3")) return UniformTypeEnum::FloatVec3;
        if (!str.compare("vec4")) return UniformTypeEnum::FloatVec4;
        if (!str.compare("double")) return UniformTypeEnum::Double;
        if (!str.compare("dvec2")) return UniformTypeEnum::DoubleVec2;
        if (!str.compare("dvec3")) return UniformTypeEnum::DoubleVec3;
        if (!str.compare("dvec4")) return UniformTypeEnum::DoubleVec4;
        if (!str.compare("int")) return UniformTypeEnum::Int;
        if (!str.compare("ivec2")) return UniformTypeEnum::IntVec2;
        if (!str.compare("ivec3")) return UniformTypeEnum::IntVec3;
        if (!str.compare("ivec4")) return UniformTypeEnum::IntVec4;
        if (!str.compare("unsigned int")) return UniformTypeEnum::UInt;
        if (!str.compare("uvec2")) return UniformTypeEnum::UIntVec2;
        if (!str.compare("uvec3")) return UniformTypeEnum::UIntVec3;
        if (!str.compare("uvec4")) return UniformTypeEnum::UIntVec4;
        if (!str.compare("bool")) return UniformTypeEnum::Bool;
        if (!str.compare("bvec2")) return UniformTypeEnum::BoolVec2;
        if (!str.compare("bvec3")) return UniformTypeEnum::BoolVec3;
        if (!str.compare("bvec4")) return UniformTypeEnum::BoolVec4;
        if (!str.compare("mat2")) return UniformTypeEnum::FloatMat2;
        if (!str.compare("mat3")) return UniformTypeEnum::FloatMat3;
        if (!str.compare("mat4")) return UniformTypeEnum::FloatMat4;
        if (!str.compare("mat2x3")) return UniformTypeEnum::FloatMat2x3;
        if (!str.compare("mat2x4")) return UniformTypeEnum::FloatMat2x4;
        if (!str.compare("mat3x2")) return UniformTypeEnum::FloatMat3x2;
        if (!str.compare("mat3x4")) return UniformTypeEnum::FloatMat3x4;
        if (!str.compare("mat4x2")) return UniformTypeEnum::FloatMat4x2;
        if (!str.compare("mat4x3")) return UniformTypeEnum::FloatMat4x3;
        if (!str.compare("dmat2")) return UniformTypeEnum::DoubleMat2;
        if (!str.compare("dmat3")) return UniformTypeEnum::DoubleMat3;
        if (!str.compare("dmat4")) return UniformTypeEnum::DoubleMat4;
        if (!str.compare("dmat2x3")) return UniformTypeEnum::DoubleMat2x3;
        if (!str.compare("dmat2x4")) return UniformTypeEnum::DoubleMat2x4;
        if (!str.compare("dmat3x2")) return UniformTypeEnum::DoubleMat3x2;
        if (!str.compare("dmat3x4")) return UniformTypeEnum::DoubleMat3x4;
        if (!str.compare("dmat4x2")) return UniformTypeEnum::DoubleMat4x2;
        if (!str.compare("dmat4x3")) return UniformTypeEnum::DoubleMat4x3;
        if (!str.compare("sampler1D")) return UniformTypeEnum::Sampler1D;
        if (!str.compare("sampler2D")) return UniformTypeEnum::Sampler2D;
        if (!str.compare("sampler3D")) return UniformTypeEnum::Sampler3D;
        if (!str.compare("samplerCube")) return UniformTypeEnum::SamplerCube;
        if (!str.compare("sampler1DShadow")) return UniformTypeEnum::Sampler1DShadow;
        if (!str.compare("sampler2DShadow")) return UniformTypeEnum::Sampler2DShadow;
        if (!str.compare("sampler1DArray")) return UniformTypeEnum::Sampler1DArray;
        if (!str.compare("sampler2DArray")) return UniformTypeEnum::Sampler2DArray;
        if (!str.compare("sampler1DArrayShadow")) return UniformTypeEnum::Sampler1DArrayShadow;
        if (!str.compare("sampler2DArrayShadow")) return UniformTypeEnum::Sampler2DArrayShadow;
        if (!str.compare("sampler2DMS")) return UniformTypeEnum::Sampler2DMultisample;
        if (!str.compare("sampler2DMSArray")) return UniformTypeEnum::Sampler2DMultisampleArray;
        if (!str.compare("samplerCubeShadow")) return UniformTypeEnum::SamplerCubeShadow;
        if (!str.compare("samplerBuffer")) return UniformTypeEnum::SamplerBuffer;
        if (!str.compare("sampler2DRect")) return UniformTypeEnum::Sampler2DRect;
        if (!str.compare("sampler2DRectShadow")) return UniformTypeEnum::Sampler2DRectShadow;
        if (!str.compare("isampler1D")) return UniformTypeEnum::IntSampler1D;
        if (!str.compare("isampler2D")) return UniformTypeEnum::IntSampler2D;
        if (!str.compare("isampler3D")) return UniformTypeEnum::IntSampler3D;
        if (!str.compare("isamplerCube")) return UniformTypeEnum::IntSamplerCube;
        if (!str.compare("isampler1DArray")) return UniformTypeEnum::IntSampler1DArray;
        if (!str.compare("isampler2DArray")) return UniformTypeEnum::IntSampler2DArray;
        if (!str.compare("isampler2DMS")) return UniformTypeEnum::IntSampler2DMultisample;
        if (!str.compare("isampler2DMSArray")) return UniformTypeEnum::IntSampler2DMultisampleArray;
        if (!str.compare("isamplerBuffer")) return UniformTypeEnum::IntSamplerBuffer;
        if (!str.compare("isampler2DRect")) return UniformTypeEnum::IntSampler2DRect;
        if (!str.compare("usampler1D")) return UniformTypeEnum::UIntSampler1D;
        if (!str.compare("usampler2D")) return UniformTypeEnum::UIntSampler2D;
        if (!str.compare("usampler3D")) return UniformTypeEnum::UIntSampler3D;
        if (!str.compare("usamplerCube")) return UniformTypeEnum::UIntSamplerCube;
        if (!str.compare("usampler2DArray")) return UniformTypeEnum::UIntSampler1DArray;
        if (!str.compare("usampler2DArray")) return UniformTypeEnum::UIntSampler2DArray;
        if (!str.compare("usampler2DMS")) return UniformTypeEnum::UIntSampler2DMultisample;
        if (!str.compare("usampler2DMSArray")) return UniformTypeEnum::UIntSampler2DMultisampleArray;
        if (!str.compare("usamplerBuffer")) return UniformTypeEnum::UIntSamplerBuffer;
        if (!str.compare("usampler2DRect")) return UniformTypeEnum::UIntSampler2DRect;
        if (!str.compare("image1D")) return UniformTypeEnum::Image1D;
        if (!str.compare("image2D")) return UniformTypeEnum::Image2D;
        if (!str.compare("image3D")) return UniformTypeEnum::Image3D;
        if (!str.compare("image2DRect")) return UniformTypeEnum::Image2DRect;
        if (!str.compare("imageCube")) return UniformTypeEnum::ImageCube;
        if (!str.compare("imageBuffer")) return UniformTypeEnum::ImageBuffer;
        if (!str.compare("image1DArray")) return UniformTypeEnum::Image1DArray;
        if (!str.compare("image2DArray")) return UniformTypeEnum::Image2DArray;
        if (!str.compare("image2DMS")) return UniformTypeEnum::Image2DMultisample;
        if (!str.compare("image2DMSArray")) return UniformTypeEnum::Image2DMultisampleArray;
        if (!str.compare("iimage1D")) return UniformTypeEnum::IntImage1D;
        if (!str.compare("iimage2D")) return UniformTypeEnum::IntImage2D;
        if (!str.compare("iimage3D")) return UniformTypeEnum::IntImage3D;
        if (!str.compare("iimage2DRect")) return UniformTypeEnum::IntImage2DRect;
        if (!str.compare("iimageCube")) return UniformTypeEnum::IntImageCube;
        if (!str.compare("iimageBuffer")) return UniformTypeEnum::IntImageBuffer;
        if (!str.compare("iimage1DArray")) return UniformTypeEnum::IntImage1DArray;
        if (!str.compare("iimage2DArray")) return UniformTypeEnum::IntImage2DArray;
        if (!str.compare("iimage2DMS")) return UniformTypeEnum::IntImage2DMultisample;
        if (!str.compare("iimage2DMSArray")) return UniformTypeEnum::IntImage2DMultisampleArray;
        if (!str.compare("uimage1D")) return UniformTypeEnum::UIntImage1D;
        if (!str.compare("uimage2D")) return UniformTypeEnum::UIntImage2D;
        if (!str.compare("uimage3D")) return UniformTypeEnum::UIntImage3D;
        if (!str.compare("uimage2DRect")) return UniformTypeEnum::UIntImage2DRect;
        if (!str.compare("uimageCube")) return UniformTypeEnum::UIntImageCube;
        if (!str.compare("uimageBuffer")) return UniformTypeEnum::UIntImageBuffer;
        if (!str.compare("uimage1DArray")) return UniformTypeEnum::UIntImage1DArray;
        if (!str.compare("uimage2DArray")) return UniformTypeEnum::UIntImage2DArray;
        if (!str.compare("uimage2DMS")) return UniformTypeEnum::UIntImage2DMultisample;
        if (!str.compare("uimage2DMSArray")) return UniformTypeEnum::UIntImage2DMultisampleArray;
        if (!str.compare("atomic_uint")) return UniformTypeEnum::UIntAtomicCounter;
        throw std::invalid_argument(std::string("Invalid `Type`"));
    }
}
