#include "PyGpuBufferManager.h"

#include <boost/python.hpp>

#include "core/GpuBufferManager.h"

namespace glove {
namespace python {

void ExportGpuBufferManager() {
	boost::python::class_<glove::GpuBufferManager, boost::python::bases<GloveObject>, std::shared_ptr<GpuBufferManager>>("GpuBufferManager")
		.def("CreateVertexBuffer", &GpuBufferManager::CreateVertexBuffer)
		.def("CreateIndexBuffer", &GpuBufferManager::CreateIndexBuffer);
}

} // namespace python
} // namespace glove