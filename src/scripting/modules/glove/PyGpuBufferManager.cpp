#include "PyGpuBufferManager.h"

#include <boost/python.hpp>

#include "core/GpuBufferManager.h"

namespace glove {
namespace python {

void ExportGpuBufferManager() {
	boost::python::class_<glove::GpuBufferManager, std::shared_ptr<GpuBufferManager>>("GpuBufferManager", boost::python::no_init)
		.def("CreateVertexBuffer", &GpuBufferManager::CreateVertexBuffer)
		.def("CreateIndexBuffer", &GpuBufferManager::CreateIndexBuffer);
}

} // namespace python
} // namespace glove