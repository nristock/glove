/*
 * GloveCore.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "GloveCore.h"

#ifdef WIN32
#include <Windows.h>
#elif UNIX
//TODO
#endif

#include "GloveException.h"
#include "rendering/GloveRenderer.h"
#include "scripting/GlovePythonEngine.h"

namespace glove {

GloveCore::GloveCore() : renderer(new GloveRenderer()), pythonEngine(new GlovePythonEngine()) {

#ifdef WIN32
	int bufferSize = 4096;
	wchar_t* moduleName = reinterpret_cast<wchar_t*>(malloc(sizeof(wchar_t) * bufferSize));
	GetModuleFileNameW(NULL, moduleName, bufferSize);

	while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		free(moduleName);
		bufferSize += 64;
		moduleName = reinterpret_cast<wchar_t*>(malloc(sizeof(wchar_t) * bufferSize));

		GetModuleFileNameW(NULL, moduleName, bufferSize);
	}

	executableName = moduleName;
	free(moduleName);
	executablePath = executableName.substr(0, executableName.find_last_of(L"\\/"));
#elif UNIX
	//TODO
#endif

	OLOG(info, "Running from " << executablePath);
	OLOG(info, "GloveCore created");

}

GloveCore::~GloveCore() {
}

void GloveCore::Init(int argc, char** argv) {
	InitializeRenderingContext(argc, argv, 800, 600);
	InitializeScripting();
}

void GloveCore::InitializeRenderingContext(int argc, char** argv, int windowWidth, int windowHeight) {
	try {
		renderer->Init(windowWidth, windowHeight, 3, 3, argc, argv);
	}
	catch (GloveException& e) {
		OLOG(error, "Exception while initializing rendering subsystem:" << std::endl << e.what());
	}

}

void GloveCore::InitializeScripting() {
	pythonEngine->Init(executablePath);
}

void GloveCore::Exit() {
	pythonEngine->Exit();
}

} /* namespace glove */
