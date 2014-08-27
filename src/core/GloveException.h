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

namespace glove {

class GloveException: public std::exception {
public:
	GloveException(std::string message);
	virtual ~GloveException();

	const char* what() const throw();

private:
	std::string message;
};

} /* namespace glove */

#endif /* GLOVEEXCEPTION_H_ */
