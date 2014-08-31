#ifndef GLOVEPYTHONENGINE_H_
#define GLOVEPYTHONENGINE_H_

#include <string>

#include "core/GloveObject.h"

namespace glove{

class GlovePythonEngine : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GlovePythonEngine")
public:
	GlovePythonEngine();
	virtual ~GlovePythonEngine();

	void Init(const std::wstring& executableBasePath);
	void Exit();

	void HandleError();
};

} // namespace glove

#endif