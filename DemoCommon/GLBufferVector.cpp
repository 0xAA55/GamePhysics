#include "GLBufferVector.hpp"
using namespace GLRenderer;

BufferCastingError::BufferCastingError(std::string What) noexcept :
	std::runtime_error(What)
{
}

template GLBufferVector<GLubyte>;
template GLBufferVector<GLushort>;
template GLBufferVector<GLuint>;

template GLBufferVectorNC<GLubyte>;
template GLBufferVectorNC<GLushort>;
template GLBufferVectorNC<GLuint>;
