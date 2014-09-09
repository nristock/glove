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

	/*!
	 * Initializes the Glove engine and all subsystems. Must be called from main thread.
	 */
	void Init(int argc, char** argv);
		
	void Exit();

	/*!
	 * Starts the main application loop. Must be called from main thread.
	 */
	void EnterMainLoop();

	void Update();
	void Render();

	GlovePythonEnginePtr GetPythonEngine() const { return pythonEngine; }

	std::string MakeDataPath(std::string& relPath);

private:
	GloveRendererPtr renderer;
	GlovePythonEnginePtr pythonEngine;

	std::wstring executableName;
	std::wstring executablePath;

	GloveWindowPointer mainWindow;

	unsigned long frameCounter;
	
	void InitializeRenderingContext(int argc, char** argv, int windowWidth, int windowHeight);
	void InitializeScripting();
};

} /* namespace glove */

#endif /* GLOVECORE_H_ */
