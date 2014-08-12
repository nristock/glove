/*
 * ShaderUtils.h
 *
 *  Created on: Jul 29, 2014
 *      Author: monofraps
 */

#ifndef SHADERUTILS_H_
#define SHADERUTILS_H_

#include <GL/gl.h>

namespace glove {
namespace utils {
void PrintShaderCompilerLog(GLuint shaderId);
void PrintShaderProgramLinkLog(GLuint programId);
}
}


#endif /* SHADERUTILS_H_ */
