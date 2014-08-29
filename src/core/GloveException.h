/*
 * GloveException.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef GLOVEEXCEPTION_H_
#define GLOVEEXCEPTION_H_

#include <exception>
#include <string>

#include "memory/GloveMemory.h"

namespace glove {

class GloveException : public std::exception {
	GLOVE_MEM_ALLOC_FUNCS("GloveException");
public:
	GloveException(std::string message);
	virtual ~GloveException();

	const char* what() const throw();

private:
	std::string message;
};

} /* namespace glove */

#endif /* GLOVEEXCEPTION_H_ */
