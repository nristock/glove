#include "PyGameComponent.h"

#include <boost/python.hpp>

#include "core/GloveCore.h"
#include "scripting/GlovePythonEngine.h"
#include "graph/GameComponent.h"

namespace glove {
namespace python {

// We have to use a manual wrapper here since boost's wrapper doesn't keep track of reference count correctly
class GameComponentWrapper : public GameComponent {
Profilable();
public:
    GameComponentWrapper(PyObject* self)
            : self(self), EnableProfilable() {
        Py_INCREF(self);
    }

    GameComponentWrapper(PyObject* self, const GameComponent& copy)
            : GameComponent(copy), self(self), EnableProfilable() {
        Py_INCREF(self);
    }

    ~GameComponentWrapper() {
        Py_DECREF(self);
    }

#define VIRT_FUNC(fname_) \
    void fname_() { boost::python::call_method<void>(self, #fname_); } \
    void fname_##_() { GameComponent:: fname_(); }

    VIRT_FUNC(SyncEarlyUpdate)

    VIRT_FUNC(SyncUpdate)

    VIRT_FUNC(AsyncUpdate)

    VIRT_FUNC(SyncLateUpdate)

    VIRT_FUNC(AsyncPrePhysicsUpdate)

    VIRT_FUNC(SyncPhysicsUpdate)

    VIRT_FUNC(AsyncPostPhysicsUpdate)

private:
    PyObject* self;
};

void ExportGameComponent() {
    boost::python::class_<GameComponent, std::shared_ptr<GameComponentWrapper>, boost::python::bases<GloveObject>>("GameComponent")
            .def("SyncEarlyUpdate", &GameComponent::SyncEarlyUpdate, &GameComponentWrapper::SyncEarlyUpdate_)
            .def("SyncUpdate", &GameComponent::SyncUpdate, &GameComponentWrapper::SyncUpdate_)
            .def("AsyncUpdate", &GameComponent::AsyncUpdate, &GameComponentWrapper::AsyncUpdate_)
            .def("SyncLateUpdate", &GameComponent::SyncLateUpdate, &GameComponentWrapper::SyncLateUpdate_)
            .def("AsyncPrePhysicsUpdate", &GameComponent::AsyncPrePhysicsUpdate, &GameComponentWrapper::AsyncPrePhysicsUpdate_)
            .def("SyncPhysicsUpdate", &GameComponent::SyncPhysicsUpdate, &GameComponentWrapper::SyncPhysicsUpdate_)
            .def("AsyncPostPhysicsUpdate", &GameComponent::AsyncPostPhysicsUpdate, &GameComponentWrapper::AsyncPostPhysicsUpdate_)
            .add_property("owner", &GameComponent::GetOwner);

    boost::python::implicitly_convertible<std::shared_ptr<GameComponentWrapper>, std::shared_ptr<GameComponent>>();
}

} // namespace python
} // namespace glove