#include "PyGPUBuffer.h"

#include <boost/python.hpp>

#include "buffers/IGpuBuffer.h"

namespace glove {
namespace python {

void ExportGPUBuffer() {
	boost::python::enum_<BufferUsage>("BufferUsage")
		.value("STATIC", BU_STATIC)
		.value("DYNAMIC", BU_DYNAMIC);

	boost::python::class_<IGpuBuffer, std::shared_ptr<IGpuBuffer>, boost::noncopyable>("IGpuBuffer", boost::python::no_init)
		.def("Bind", &IGpuBuffer::Bind)
		.def("Unbind", &IGpuBuffer::Unbind)
		.def("WriteData", &IGpuBuffer::WriteData);
}

} // namespace python
} // namespace glove