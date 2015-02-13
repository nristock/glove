#include <GL/glew.h>
#include <GL/gl.h>

#include "internal/OpenGLWrapper.hpp"

namespace glove {
namespace gl {

OpenGLWrapperPtr OpenGLWrapper::sharedWrapper = OpenGLWrapperPtr(new OpenGLWrapper());

void OpenGLWrapper::SetSharedOpenGLWrapper(const OpenGLWrapperPtr& wrapper) {
    sharedWrapper = wrapper;
}

void OpenGLWrapper::DeleteVertexArrays(GLsizei n, const GLuint* arrays) {
    sharedWrapper->_glDeleteVertexArrays(n, arrays);
}

void OpenGLWrapper::GenVertexArrays(GLsizei n, GLuint* arrays) {
    sharedWrapper->_glGenVertexArrays(n, arrays);
}

void OpenGLWrapper::BindVertexArray(GLuint array) {
    sharedWrapper->_glBindVertexArray(array);
}

void OpenGLWrapper::EnableVertexAttribArray(GLuint index) {
    sharedWrapper->_glEnableVertexAttribArray(index);
}

void OpenGLWrapper::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                        const GLvoid* pointer) {
    sharedWrapper->_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void OpenGLWrapper::Clear(GLbitfield mask) {
    sharedWrapper->_glClear(mask);
}

GLuint OpenGLWrapper::CreateShader(GLenum shaderType) {
    return sharedWrapper->_glCreateShader(shaderType);
}

void OpenGLWrapper::ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) {
    sharedWrapper->_glShaderSource(shader, count, string, length);
}

void OpenGLWrapper::CompileShader(GLuint shader) {
    sharedWrapper->_glCompileShader(shader);
}

void OpenGLWrapper::GetShaderiv(GLuint shader, GLenum pname, GLint* params) {
    sharedWrapper->_glGetShaderiv(shader, pname, params);
}

void OpenGLWrapper::DeleteShader(GLuint shader) {
    sharedWrapper->_glDeleteShader(shader);
}

void OpenGLWrapper::AttachShader(GLuint program, GLuint shader) {
    sharedWrapper->_glAttachShader(program, shader);
}

void OpenGLWrapper::LinkProgram(GLuint program) {
    sharedWrapper->_glLinkProgram(program);
}

GLuint OpenGLWrapper::CreateProgram() {
    return sharedWrapper->_glCreateProgram();
}

void OpenGLWrapper::GetProgramiv(GLuint program, GLenum pname, GLint* params) {
    sharedWrapper->_glGetProgramiv(program, pname, params);
}

void OpenGLWrapper::DeleteProgram(GLuint program) {
    sharedWrapper->_glDeleteProgram(program);
}

GLint OpenGLWrapper::GetUniformLocation(GLuint program, const GLchar* name) {
    return sharedWrapper->_glGetUniformLocation(program, name);
}

GLint OpenGLWrapper::GetAttribLocation(GLuint program, const GLchar* name) {
    return sharedWrapper->_glGetAttribLocation(program, name);
}

void OpenGLWrapper::UseProgram(GLuint program) {
    sharedWrapper->_glUseProgram(program);
}

void OpenGLWrapper::UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    sharedWrapper->_glUniformMatrix3fv(location, count, transpose, value);
}

void OpenGLWrapper::UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    sharedWrapper->_glUniformMatrix4fv(location, count, transpose, value);
}

void OpenGLWrapper::Uniform3fv(GLint location, GLsizei count, const GLfloat* value) {
    sharedWrapper->_glUniform3fv(location, count, value);
}

void OpenGLWrapper::Uniform4fv(GLint location, GLsizei count, const GLfloat* value) {
    sharedWrapper->_glUniform4fv(location, count, value);
}

void OpenGLWrapper::Uniform1f(GLint location, GLfloat value) {
    sharedWrapper->_glUniform1f(location, value);
}

void OpenGLWrapper::GenBuffers(GLsizei n, GLuint* buffers) {
    sharedWrapper->_glGenBuffers(n, buffers);
}

void OpenGLWrapper::DeleteBuffers(GLsizei n, const GLuint* buffers) {
    sharedWrapper->_glDeleteBuffers(n, buffers);
}

void OpenGLWrapper::BindBuffer(GLenum target, GLuint buffer) {
    sharedWrapper->_glBindBuffer(target, buffer);
}

void OpenGLWrapper::BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
    sharedWrapper->_glBufferData(target, size, data, usage);
}

void OpenGLWrapper::DrawArrays(GLenum mode, GLint first, GLsizei count) {
    sharedWrapper->_glDrawArrays(mode, first, count);
}

void OpenGLWrapper::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) {
    sharedWrapper->_glDrawElements(mode, count, type, indices);
}

void OpenGLWrapper::GenFramebuffers(GLsizei n, GLuint* ids) {
    sharedWrapper->_glGenFramebuffers(n, ids);
}

void OpenGLWrapper::GenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
    sharedWrapper->_glGenRenderbuffers(n, renderbuffers);
}

void OpenGLWrapper::GenTextures(GLsizei n, GLuint* textures) {
    sharedWrapper->_glGenTextures(n, textures);
}

void OpenGLWrapper::BindFramebuffer(GLenum target, GLuint framebuffer) {
    sharedWrapper->_glBindFramebuffer(target, framebuffer);
}

void OpenGLWrapper::FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    sharedWrapper->_glFramebufferTexture(target, attachment, texture, level);
}

void OpenGLWrapper::BindRenderbuffer(GLenum target, GLuint renderbuffer) {
    sharedWrapper->_glBindRenderbuffer(target, renderbuffer);
}

void OpenGLWrapper::DrawBuffers(GLsizei n, const GLenum* bufs) {
    sharedWrapper->_glDrawBuffers(n, bufs);
}

void OpenGLWrapper::BindTexture(GLenum target, GLuint texture) {
    sharedWrapper->_glBindTexture(target, texture);
}

void OpenGLWrapper::TexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                               GLint border, GLenum format, GLenum type, const GLvoid* data) {
    sharedWrapper->_glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
}

void OpenGLWrapper::TexParameteri(GLenum target, GLenum pname, GLint param) {
    sharedWrapper->_glTexParameteri(target, pname, param);
}

void OpenGLWrapper::Viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    sharedWrapper->_glViewport(x, y, width, height);
}

void OpenGLWrapper::ActiveTexture(GLenum texture) {
    sharedWrapper->_glActiveTexture(texture);
}

void OpenGLWrapper::_glDeleteVertexArrays(GLsizei n, const GLuint* arrays) {
    glDeleteVertexArrays(n, arrays);
}

void OpenGLWrapper::_glGenVertexArrays(GLsizei n, GLuint* arrays) {
    glGenVertexArrays(n, arrays);
}

void OpenGLWrapper::_glClear(GLbitfield mask) {
    glClear(mask);
}

void OpenGLWrapper::_glBindVertexArray(GLuint array) {
    glBindVertexArray(array);
}

void OpenGLWrapper::_glEnableVertexAttribArray(GLuint index) {
    glEnableVertexAttribArray(index);
}

void OpenGLWrapper::_glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride,
                                           const GLvoid* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

GLuint OpenGLWrapper::_glCreateShader(GLenum shaderType) {
    return glCreateShader(shaderType);
}

void OpenGLWrapper::_glShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) {
    glShaderSource(shader, count, string, length);
}

void OpenGLWrapper::_glCompileShader(GLuint shader) {
    glCompileShader(shader);
}

void OpenGLWrapper::_glGetShaderiv(GLuint shader, GLenum pname, GLint* params) {
    glGetShaderiv(shader, pname, params);
}

void OpenGLWrapper::_glDeleteShader(GLuint shader) {
    glDeleteShader(shader);
}

void OpenGLWrapper::_glAttachShader(GLuint program, GLuint shader) {
    glAttachShader(program, shader);
}

void OpenGLWrapper::_glLinkProgram(GLuint program) {
    glLinkProgram(program);
}

GLuint OpenGLWrapper::_glCreateProgram() {
    return glCreateProgram();
}

void OpenGLWrapper::_glGetProgramiv(GLuint program, GLenum pname, GLint* params) {
    glGetProgramiv(program, pname, params);
}

void OpenGLWrapper::_glDeleteProgram(GLuint program) {
    glDeleteProgram(program);
}

GLint OpenGLWrapper::_glGetUniformLocation(GLuint program, const GLchar* name) {
    return glGetUniformLocation(program, name);
}

GLint OpenGLWrapper::_glGetAttribLocation(GLuint program, const GLchar* name) {
    return glGetAttribLocation(program, name);
}

void OpenGLWrapper::_glUseProgram(GLuint program) {
    glUseProgram(program);
}

void OpenGLWrapper::_glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    glUniformMatrix3fv(location, count, transpose, value);
}

void OpenGLWrapper::_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    glUniformMatrix4fv(location, count, transpose, value);
}

void OpenGLWrapper::_glUniform3fv(GLint location, GLsizei count, const GLfloat* value) {
    glUniform3fv(location, count, value);
}

void OpenGLWrapper::_glUniform4fv(GLint location, GLsizei count, const GLfloat* value) {
    glUniform4fv(location, count, value);
}

void OpenGLWrapper::_glUniform1f(GLint location, GLfloat value) {
    glUniform1f(location, value);
}

void OpenGLWrapper::_glGenBuffers(GLsizei n, GLuint* buffers) {
    glGenBuffers(n, buffers);
}

void OpenGLWrapper::_glDeleteBuffers(GLsizei n, const GLuint* buffers) {
    glDeleteBuffers(n, buffers);
}

void OpenGLWrapper::_glBindBuffer(GLenum target, GLuint buffer) {
    glBindBuffer(target, buffer);
}

void OpenGLWrapper::_glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
    glBufferData(target, size, data, usage);
}

void OpenGLWrapper::_glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    glDrawArrays(mode, first, count);
}

void OpenGLWrapper::_glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) {
    glDrawElements(mode, count, type, indices);
}

void OpenGLWrapper::_glGenFramebuffers(GLsizei n, GLuint* ids) {
    glGenFramebuffers(n, ids);
}

void OpenGLWrapper::_glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
    glGenRenderbuffers(n, renderbuffers);
}

void OpenGLWrapper::_glGenTextures(GLsizei n, GLuint* textures) {
    glGenTextures(n, textures);
}

void OpenGLWrapper::_glBindFramebuffer(GLenum target, GLuint framebuffer) {
    glBindFramebuffer(target, framebuffer);
}

void OpenGLWrapper::_glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    glFramebufferTexture(target, attachment, texture, level);
}

void OpenGLWrapper::_glBindRenderbuffer(GLenum target, GLuint renderbuffer) {
    glBindRenderbuffer(target, renderbuffer);
}

void OpenGLWrapper::_glDrawBuffers(GLsizei n, const GLenum* bufs) {
    glDrawBuffers(n, bufs);
}

void OpenGLWrapper::_glBindTexture(GLenum target, GLuint texture) {
    glBindTexture(target, texture);
}

void OpenGLWrapper::_glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                                  GLint border, GLenum format, GLenum type, const GLvoid* data) {
    glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
}

void OpenGLWrapper::_glTexParameteri(GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
}

void OpenGLWrapper::_glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
}

void OpenGLWrapper::_glActiveTexture(GLenum texture) {
    glActiveTexture(texture);
}

void OpenGLWrapper::Uniform1i(GLint location, GLint value) {
    sharedWrapper->_glUniform1i(location, value);
}

void OpenGLWrapper::_glUniform1i(GLint location, GLint value) {
    glUniform1i(location, value);
}
}
}
