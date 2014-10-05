#ifndef GLOVEPYTHONENGINE_H_
#define GLOVEPYTHONENGINE_H_

#include <string>
#include <list>

#include <boost/python/dict.hpp>
#include <boost/python/object.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove{

class GlovePythonEngine : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GlovePythonEngine")
public:
	typedef std::list<PythonPluginPtr> PythonPluginList;

	GlovePythonEngine();
	virtual ~GlovePythonEngine();

	void Init(const std::string& executableBasePath);
	void Exit();

	void LoadPlugins();
	
	void HandleError();

	boost::python::object GetMainModule();
	boost::python::dict GetRootNamespace();
	boost::python::dict GetBuiltins();

private:
	void LoadPyEnvironmentModule();

	std::string basePath;

	boost::python::dict rootNamespace;
	boost::python::dict pluginScopes;
	PythonPluginList plugins;
};

} // namespace glove

#endif