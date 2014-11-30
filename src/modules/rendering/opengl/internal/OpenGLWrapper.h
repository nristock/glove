#pragma once

#include <mutex>
#include <atomic>

#include <GL/glew.h>
#include <core/GloveFwd.h>

#include "../subsystem/OpenGLRendererModule.h"

namespace glove {
namespace gl {

/// @ingroup Internal
class OpenGLWrapper {
  public:
    virtual ~OpenGLWrapper() = default;

    /// @brief Sets the shared wrapper instance. This method is *not* thread-safe and primarily intended to make the
    ///        module easier to test.
    static GLOVE_INLINE void SetSharedOpenGLWrapper(const OpenGLWrapperPtr& wrapper);

    static GLOVE_INLINE void DeleteVertexArrays(GLsizei n, const GLuint* arrays);
    static GLOVE_INLINE void GenVertexArrays(GLsizei n, GLuint* arrays);
    static GLOVE_INLINE void BindVertexArray(GLuint array);
    static GLOVE_INLINE void EnableVertexAttribArray(GLuint index);
    static GLOVE_INLINE void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                 GLsizei stride, const GLvoid* pointer);
    static GLOVE_INLINE void Clear(GLbitfield mask);
    static GLOVE_INLINE GLuint CreateShader(GLenum shaderType);
    static GLOVE_INLINE void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
    static GLOVE_INLINE void CompileShader(GLuint shader);
    static GLOVE_INLINE void GetShaderiv(GLuint shader, GLenum pname, GLint* params);
    static GLOVE_INLINE void DeleteShader(GLuint shader);
    static GLOVE_INLINE void AttachShader(GLuint program, GLuint shader);
    static GLOVE_INLINE void LinkProgram(GLuint program);
    static GLOVE_INLINE GLuint CreateProgram();
    static GLOVE_INLINE void GetProgramiv(GLuint program, GLenum pname, GLint* params);
    static GLOVE_INLINE void DeleteProgram(GLuint program);
    static GLOVE_INLINE GLint GetUniformLocation(GLuint program, const GLchar* name);
    static GLOVE_INLINE GLint GetAttribLocation(GLuint program, const GLchar* name);
    static GLOVE_INLINE void UseProgram(GLuint program);
    static GLOVE_INLINE void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static GLOVE_INLINE void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static GLOVE_INLINE void Uniform3fv(GLint location, GLsizei count, const GLfloat* value);
    static GLOVE_INLINE void Uniform4fv(GLint location, GLsizei count, const GLfloat* value);
    static GLOVE_INLINE void Uniform1f(GLint location, GLfloat value);
    static GLOVE_INLINE void GenBuffers(GLsizei n, GLuint* buffers);
    static GLOVE_INLINE void DeleteBuffers(GLsizei n, const GLuint* buffers);
    static GLOVE_INLINE void BindBuffer(GLenum target, GLuint buffer);
    static GLOVE_INLINE void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    static GLOVE_INLINE void DrawArrays(GLenum mode, GLint first, GLsizei count);
    static GLOVE_INLINE void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);

  protected:
    virtual GLOVE_INLINE void _glDeleteVertexArrays(GLsizei n, const GLuint* arrays);
    virtual GLOVE_INLINE void _glGenVertexArrays(GLsizei n, GLuint* arrays);
    virtual GLOVE_INLINE void _glBindVertexArray(GLuint array);
    virtual GLOVE_INLINE void _glEnableVertexAttribArray(GLuint index);
    virtual GLOVE_INLINE void _glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                     GLsizei stride, const GLvoid* pointer);
    virtual GLOVE_INLINE void _glClear(GLbitfield mask);
    virtual GLOVE_INLINE GLuint _glCreateShader(GLenum shaderType);
    virtual GLOVE_INLINE void _glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
    virtual GLOVE_INLINE void _glCompileShader(GLuint shader);
    virtual GLOVE_INLINE void _glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
    virtual GLOVE_INLINE void _glDeleteShader(GLuint shader);
    virtual GLOVE_INLINE void _glAttachShader(GLuint program, GLuint shader);
    virtual GLOVE_INLINE void _glLinkProgram(GLuint program);
    virtual GLOVE_INLINE GLuint _glCreateProgram();
    virtual GLOVE_INLINE void _glGetProgramiv(GLuint program, GLenum pname, GLint* params);
    virtual GLOVE_INLINE void _glDeleteProgram(GLuint program);
    virtual GLOVE_INLINE GLint _glGetUniformLocation(GLuint program, const GLchar* name);
    virtual GLOVE_INLINE GLint _glGetAttribLocation(GLuint program, const GLchar* name);
    virtual GLOVE_INLINE void _glUseProgram(GLuint program);
    virtual GLOVE_INLINE void _glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value);
    virtual GLOVE_INLINE void _glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value);
    virtual GLOVE_INLINE void _glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
    virtual GLOVE_INLINE void _glUniform4fv(GLint location, GLsizei count, const GLfloat* value);
    virtual GLOVE_INLINE void _glUniform1f(GLint location, GLfloat value);
    virtual GLOVE_INLINE void _glGenBuffers(GLsizei n, GLuint* buffers);
    virtual GLOVE_INLINE void _glDeleteBuffers(GLsizei n, const GLuint* buffers);
    virtual GLOVE_INLINE void _glBindBuffer(GLenum target, GLuint buffer);
    virtual GLOVE_INLINE void _glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    virtual GLOVE_INLINE void _glDrawArrays(GLenum mode, GLint first, GLsizei count);
    virtual GLOVE_INLINE void _glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);

  private:
    static OpenGLWrapperPtr sharedWrapper;
};
}
}