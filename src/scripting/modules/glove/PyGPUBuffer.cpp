#include "PyGPUBuffer.h"

#include <boost/python.hpp>

#include "buffers/GPUBuffer.h"

namespace glove {
namespace python {

void ExportGPUBuffer() {
	boost::python::enum_<BufferUsage>("BufferUsage")
		.value("STATIC", BU_STATIC)
		.value("DYNAMIC", BU_DYNAMIC);

	boost::python::class_<GPUBuffer, std::shared_ptr<GPUBuffer>, boost::noncopyable>("GPUBuffer", boost::python::no_init)
		.def("Bind", &GPUBuffer::Bind)
		.def("Unbind", &GPUBuffer::Unbind)
		.def("WriteData", &GPUBuffer::WriteData);
}

} // namespace python
} // namespace glove