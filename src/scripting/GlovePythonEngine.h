#ifndef GLOVEPYTHONENGINE_H_
#define GLOVEPYTHONENGINE_H_

#include <string>

#include <boost/python/object.hpp>

#include "core/GloveObject.h"

namespace glove{

class GlovePythonEngine : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GlovePythonEngine")
public:
	GlovePythonEngine();
	virtual ~GlovePythonEngine();

	void Init(const std::string& executableBasePath);
	void Exit();

	void LoadPlugins();
	
	void HandleError();

	boost::python::object GetMainModule();
	boost::python::object GetMainNamespace();

private:
	void LoadPyEnvironmentModule();

	std::string basePath;
};

} // namespace glove

#endif