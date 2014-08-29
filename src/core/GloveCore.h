/*
 * GloveCore.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVECORE_H_
#define GLOVECORE_H_

#include "GloveFwd.h"

#include "rendering/GloveRenderer.h"
#include "GloveObject.h"

namespace glove {

class GloveCore : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GloveCore")
public:
	GloveCore();
	virtual ~GloveCore();

	void Init(int argc, char** argv);
	void InitializeRenderingContext(int argc, char** argv, int windowWidth, int windowHeight);
	void InitializeScripting();

	void Exit();

private:
	GloveRendererPtr renderer;
	GlovePythonEnginePtr pythonEngine;

	std::wstring executableName;
	std::wstring executablePath;
};

} /* namespace glove */

#endif /* GLOVECORE_H_ */
