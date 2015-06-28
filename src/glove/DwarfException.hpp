#pragma once

#include <exception>
#include <string>

#include "glove/BlueDwarfApi.hpp"

/// @brief Creates a DwarfException with the _msg message specified and file and line number information.
#define DWARF_EXCEPTION(_msg) ::BlueDwarf::DwarfException(_msg, __FILE__, __LINE__);

/// @brief Creates an exception of type _type with the provided varargs as well as file and line number information
#define DWARF_THROW(_type, ...) throw _type(__VA_ARGS__, __FILE__, __LINE__);

namespace BlueDwarf {

/** Basic engine exception. Should be used for all exceptions thrown during engine operation. */
class BD_API_EXPORT DwarfException : public std::exception {
  public:
    /** Create an exception with the provided message but without file and line information. */
    DwarfException(std::string message);

    /** Create an exception with the provided message, file name and file line. */
    DwarfException(std::string message, const char* file, int line);

    virtual ~DwarfException();

    virtual const char* what() const throw();

  private:
    std::string message;
    const char* file;
    int line;
};

} /* namespace BlueDwarf */
