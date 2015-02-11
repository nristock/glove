#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#elif defined(__unix__) || defined(__unix)
#include <unistd.h>
#include <cstdlib>
#endif

#include "glove/utils/RuntimePathInfo.hpp"

namespace glove {

void GetExecutionPathInfo(std::string& executablePath, std::string& executableName) {
#if defined(_WIN32) || defined(WIN32)
	int bufferSize = 1024;
	char* moduleName = new char[bufferSize];
	GetModuleFileName(NULL, moduleName, bufferSize);

	while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		delete[] moduleName;
		bufferSize += 64;
		moduleName = new char[bufferSize];

		GetModuleFileName(NULL, moduleName, bufferSize);
	}

	executableName = moduleName;
	delete[] moduleName;
#elif defined(__unix__) || defined(__unix)
    std::size_t bufferSize = 1024;
    char* linkName = new char[bufferSize];

    ssize_t charsWritten = readlink("/proc/self/exe", linkName, bufferSize);

    while (charsWritten == bufferSize) {
        delete[] linkName;
        bufferSize += 64;
        linkName = new char[bufferSize];
        charsWritten = readlink("/proc/self/exe", linkName, bufferSize);
    }

    linkName[charsWritten] = '\0';

    executableName = linkName;
    delete[] linkName;
#endif

    executablePath = executableName.substr(0, executableName.find_last_of("\\/"));
}

}