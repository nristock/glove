/*
 * GloveCore.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVECORE_H_
#define GLOVECORE_H_

#include <chrono>

#include "GloveFwd.h"

#include "rendering/GloveRenderer.h"
#include "GloveObject.h"
#include "GloveException.h"
#include "rendering/FrameData.h"

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
	void Render(ScenegraphPointer scenegraph);

	GlovePythonEnginePtr GetPythonEngine() const { return pythonEngine; }
	PyShedLoaderPtr GetPyshedLoader() const { return pyshedLoader; }
	GloveRendererPointer GetRenderer() const { return renderer; }
	ScenegraphPtr GetScenegraph() const { return primaryScenegraph; }

	std::string MakeDataPath(const std::string& relPath);

	static inline GloveCorePointer Instance() {
		if (GloveCore::instance) {
			return GloveCore::instance;
		}
		else {
			throw new GloveException("GloveCore has not been initialized");
		}
	}

private:
	typedef std::chrono::steady_clock::time_point TimePoint;

	GloveRendererPtr renderer;
	GlovePythonEnginePtr pythonEngine;
	PyShedLoaderPtr pyshedLoader;
	ScenegraphPtr primaryScenegraph;

	TimePoint initializationTime;

	FrameData frameData;

	std::string executableName;
	std::string executablePath;

	static GloveCorePointer instance;

	unsigned long frameCounter;
	
	void InitializeRenderingContext(int argc, char** argv, int windowWidth, int windowHeight);
	void InitializeScripting();
	void InitializeResourceLoaders();
};

} /* namespace glove */

#endif /* GLOVECORE_H_ */
