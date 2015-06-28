#pragma once

#include <mutex>
#include <atomic>

#include <GL/glew.h>
#include "glove/BlueDwarfFwd.hpp"

#include "subsystem/OpenGLRendererModule.hpp"

namespace BlueDwarf {
namespace gl {

/// @ingroup Internal
class OpenGLWrapper {
  public:
    virtual ~OpenGLWrapper() = default;

    /// @brief Sets the shared wrapper instance. This method is *not* thread-safe and primarily intended to make the
    ///        module easier to test.
    static void SetSharedOpenGLWrapper(const OpenGLWrapperPtr& wrapper);

    static void DeleteVertexArrays(GLsizei n, const GLuint* arrays);
    static void GenVertexArrays(GLsizei n, GLuint* arrays);
    static void BindVertexArray(GLuint array);
    static void EnableVertexAttribArray(GLuint index);
    static void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                 GLsizei stride, const GLvoid* pointer);
    static void Clear(GLbitfield mask);
    static GLuint CreateShader(GLenum shaderType);
    static void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
    static void CompileShader(GLuint shader);
    static void GetShaderiv(GLuint shader, GLenum pname, GLint* params);
    static void DeleteShader(GLuint shader);
    static void AttachShader(GLuint program, GLuint shader);
    static void LinkProgram(GLuint program);
    static GLuint CreateProgram();
    static void GetProgramiv(GLuint program, GLenum pname, GLint* params);
    static void DeleteProgram(GLuint program);
    static GLint GetUniformLocation(GLuint program, const GLchar* name);
    static GLint GetAttribLocation(GLuint program, const GLchar* name);
    static void UseProgram(GLuint program);
    static void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    static void Uniform3fv(GLint location, GLsizei count, const GLfloat* value);
    static void Uniform4fv(GLint location, GLsizei count, const GLfloat* value);
    static void Uniform1f(GLint location, GLfloat value);
    static void GenBuffers(GLsizei n, GLuint* buffers);
    static void DeleteBuffers(GLsizei n, const GLuint* buffers);
    static void BindBuffer(GLenum target, GLuint buffer);
    static void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    static void DrawArrays(GLenum mode, GLint first, GLsizei count);
    static void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    static void GenFramebuffers(GLsizei n, GLuint* ids);
    static void BindFramebuffer(GLenum target, GLuint framebuffer);
    static void FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
    static void GenRenderbuffers(GLsizei n, GLuint* renderbuffers);
    static void BindRenderbuffer(GLenum target, GLuint renderbuffer);
    static void DrawBuffers(GLsizei n, const GLenum* bufs);
    static void GenTextures(GLsizei n, GLuint* textures);
    static void BindTexture(GLenum target, GLuint texture);
    static void TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                                        GLint border, GLenum format, GLenum type, const GLvoid* data);
    static void TexParameteri(GLenum target, GLenum pname, GLint param);
    static void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
    static void ActiveTexture(GLenum texture);
    static void Uniform1i(GLint location, GLint value);
    static void* MapBuffer(GLenum target, GLenum access);
    static void* MapNamedBuffer(GLuint buffer, GLenum access);
    static void UnmapBuffer(GLenum target);
    static void DeleteFramebuffers(GLsizei n, GLuint* framebuffers) {
        sharedWrapper->_glDeleteFramebuffers(n, framebuffers);
    }
    static void RenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height) {
        sharedWrapper->_glRenderbufferStorage(target, internalFormat, width, height);
    }
    static GLenum GetError() {
        return sharedWrapper->_glGetError();
    }
    static void Scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
        sharedWrapper->_glScissor(x, y, width, height);
    }
    static void Enable(GLenum cap) {
        sharedWrapper->_glEnable(cap);
    }
    static void Disable(GLenum cap) {
        sharedWrapper->_glDisable(cap);
    }
    static GLenum CheckFramebufferStatus(GLenum target) {
        return sharedWrapper->_glCheckFramebufferStatus(target);
    }
    static void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data) {
        sharedWrapper->_glReadPixels(x, y, width, height, format, type, data);
    }

  protected:
    virtual void _glDeleteVertexArrays(GLsizei n, const GLuint* arrays);
    virtual void _glGenVertexArrays(GLsizei n, GLuint* arrays);
    virtual void _glBindVertexArray(GLuint array);
    virtual void _glEnableVertexAttribArray(GLuint index);
    virtual void _glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                                     GLsizei stride, const GLvoid* pointer);
    virtual void _glClear(GLbitfield mask);
    virtual GLuint _glCreateShader(GLenum shaderType);
    virtual void _glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
    virtual void _glCompileShader(GLuint shader);
    virtual void _glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
    virtual void _glDeleteShader(GLuint shader);
    virtual void _glAttachShader(GLuint program, GLuint shader);
    virtual void _glLinkProgram(GLuint program);
    virtual GLuint _glCreateProgram();
    virtual void _glGetProgramiv(GLuint program, GLenum pname, GLint* params);
    virtual void _glDeleteProgram(GLuint program);
    virtual GLint _glGetUniformLocation(GLuint program, const GLchar* name);
    virtual GLint _glGetAttribLocation(GLuint program, const GLchar* name);
    virtual void _glUseProgram(GLuint program);
    virtual void _glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value);
    virtual void _glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose,
                                                  const GLfloat* value);
    virtual void _glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
    virtual void _glUniform4fv(GLint location, GLsizei count, const GLfloat* value);
    virtual void _glUniform1f(GLint location, GLfloat value);
    virtual void _glGenBuffers(GLsizei n, GLuint* buffers);
    virtual void _glDeleteBuffers(GLsizei n, const GLuint* buffers);
    virtual void _glBindBuffer(GLenum target, GLuint buffer);
    virtual void _glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    virtual void _glDrawArrays(GLenum mode, GLint first, GLsizei count);
    virtual void _glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    virtual void _glGenFramebuffers(GLsizei n, GLuint* ids);
    virtual void _glBindFramebuffer(GLenum target, GLuint framebuffer);
    virtual void _glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
    virtual void _glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
    virtual void _glBindRenderbuffer(GLenum target, GLuint renderbuffer);
    virtual void _glDrawBuffers(GLsizei n, const GLenum* bufs);
    virtual void _glGenTextures(GLsizei n, GLuint* textures);
    virtual void _glBindTexture(GLenum target, GLuint texture);
    virtual void _glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width,
                                            GLsizei height, GLint border, GLenum format, GLenum type,
                                            const GLvoid* data);
    virtual void _glTexParameteri(GLenum target, GLenum pname, GLint param);
    virtual void _glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    virtual void _glActiveTexture(GLenum texture);
    virtual void _glUniform1i(GLint location, GLint value);
    virtual void* _glMapBuffer(GLenum target, GLenum access);
    virtual void* _glMapNamedBuffer(GLuint buffer, GLenum access);
    virtual void _glUnmapBuffer(GLenum target);
    virtual void _glDeleteFramebuffers(GLsizei n, GLuint* framebuffers) {
        glDeleteFramebuffers(n, framebuffers);
    }
    virtual void _glRenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height) {
        glRenderbufferStorage(target, internalFormat, width, height);
    }
    virtual GLenum _glGetError() {
        return glGetError();
    }
    virtual void _glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
        glScissor(x, y, width, height);
    }
    virtual void _glEnable(GLenum cap) {
        glEnable(cap);
    }
    virtual void _glDisable(GLenum cap) {
        glDisable(cap);
    }
    virtual GLenum _glCheckFramebufferStatus(GLenum target) {
        return glCheckFramebufferStatus(target);
    }

    virtual void _glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* data) {
        glReadPixels(x, y, width, height, format, type, data);
    }

  private:
    static OpenGLWrapperPtr sharedWrapper;
};

using GL = OpenGLWrapper;
}
}