#pragma once

#include <string>
#include <list>

#include <boost/python/dict.hpp>
#include <boost/python/object.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class GlovePythonEngine : public GloveObject {
Profilable()
public:
    typedef std::list<PythonPluginPtr> PythonPluginList;

    GlovePythonEngine(const std::string& executableBasePath);

    virtual ~GlovePythonEngine();

    void HandleError();

    boost::python::object GetMainModule();

    boost::python::dict GetRootNamespace();

    boost::python::dict GetBuiltins();

    virtual void AnnouncePlugin(const PythonPluginPtr& pythonPlugin);

private:
    void LoadPyEnvironmentModule();

    std::string basePath;

    boost::python::dict rootNamespace;
    boost::python::dict pluginScopes;
    PythonPluginList plugins;
};

} // namespace glove