#pragma once

#include <exception>
#include <string>

#include "memory/GloveMemory.h"

#define GLOVE_EXCEPTION(_msg) GloveException(_msg, __FILE__, __LINE__);

namespace glove {

class GloveException : public std::exception {
	GLOVE_MEM_ALLOC_FUNCS("GloveException");
public:
	GloveException(std::string message);
	GloveException(std::string message, const char* file, int line);
	virtual ~GloveException();

	virtual const char* what() const throw();

private:
	std::string message;
	const char* file;
	int line;
};

} /* namespace glove */
