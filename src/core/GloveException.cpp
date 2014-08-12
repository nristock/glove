/*
 * GloveException.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "GloveException.h"

namespace glove {
namespace core {

GloveException::GloveException(std::string message) : message(message) {

}

GloveException::~GloveException() {
}

const char* GloveException::what() const throw () {
	return message.c_str();
}

} /* namespace core */
} /* namespace glove */
