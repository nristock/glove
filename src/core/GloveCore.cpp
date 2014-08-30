/*
 * GloveCore.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "GloveCore.h"

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#elif defined(__unix__) || defined(__unix)
#include <unistd.h>
#include <cstdlib>
#endif

#include "GloveException.h"
#include "rendering/GloveWindow.h"
#include "rendering/GloveRenderer.h"
#include "scripting/GlovePythonEngine.h"

namespace glove {

GloveCore::GloveCore() : renderer(new GloveRenderer()), pythonEngine(new GlovePythonEngine()), frameCounter(0) {

#if defined(_WIN32) || defined(WIN32)
	int bufferSize = 4096;
	wchar_t* moduleName = reinterpret_cast<wchar_t*>(GloveMemAllocN(sizeof(wchar_t) * bufferSize, "GloveCore/ModuleName"));
	GetModuleFileNameW(NULL, moduleName, bufferSize);

	while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		GloveMemFree(moduleName);
		bufferSize += 64;
		moduleName = reinterpret_cast<wchar_t*>(GloveMemAllocN(sizeof(wchar_t) * bufferSize, "GloveCore/ModuleName"));

		GetModuleFileNameW(NULL, moduleName, bufferSize);
	}

	executableName = moduleName;
	GloveMemFree(moduleName);
#elif defined(__unix__) || defined(__unix)
	int bufferSize = 1024;
	char* linkName = reinterpret_cast<char*>(GloveMemAllocN(bufferSize, "GloveCore/SelfLinkName"));
	ssize_t charsWritten = readlink("/proc/self/exe", linkName, bufferSize);

	while(charsWritten == bufferSize) {
		GloveMemFree(linkName);
		bufferSize += 64;
		linkName = reinterpret_cast<char*>(GloveMemAllocN(bufferSize, "GloveCore/SlefLinkName"));
		charsWritten = readlink("/proc/self/exe", linkName, bufferSize);
	}

	OLOG(info, charsWritten);
	linkName[charsWritten] = '\0';

	wchar_t* linkNameWC = reinterpret_cast<wchar_t*>(GloveMemAllocN(sizeof(wchar_t)*(charsWritten + 1), "GloveCore/SelfLinkNameWC"));
	mbstowcs(linkNameWC, linkName, charsWritten + 1);

	GloveMemFree(linkName);
	executableName = linkNameWC;
	GloveMemFree(linkNameWC);
#endif
	executablePath = executableName.substr(0, executableName.find_last_of(L"\\/"));

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
		mainWindow = renderer->Init(windowWidth, windowHeight, 3, 3, argc, argv);
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

void GloveCore::EnterMainLoop() {
	while (!mainWindow->CloseRequested()) {
		Update();
		Render();
	}
}

void GloveCore::Update() {

}

void GloveCore::Render() {
	renderer->RenderScene(mainWindow);
}

} /* namespace glove */
