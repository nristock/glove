#pragma once

#include <exception>
#include <string>

#include "pitamem/MemoryProfile.h"

/// @brief Creates a GloveException with the _msg message specified and file and line number information.
#define GLOVE_EXCEPTION(_msg) ::glove::GloveException(_msg, __FILE__, __LINE__);

/// @brief Creates an exception of type _type with the provided varargs as well as file and line number information
#define GLOVE_THROW(_type, ...) throw _type(__VA_ARGS__, __FILE__, __LINE__);

namespace glove {

/** Basic engine exception. Should be used for all exceptions thrown during engine operation. */
class GloveException : public std::exception {
    Profilable();

  public:
    /** Create an exception with the provided message but without file and line information. */
    GloveException(std::string message);

    /** Create an exception with the provided message, file name and file line. */
    GloveException(std::string message, const char* file, int line);

    virtual ~GloveException();

    virtual const char* what() const throw();

  private:
    std::string message;
    const char* file;
    int line;
};

} /* namespace glove */
