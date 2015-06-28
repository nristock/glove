#include <boost/format.hpp>

#include "glove/filesystem/exceptions/FileNotFoundException.hpp"

namespace BlueDwarf {

FileNotFoundException::FileNotFoundException(const File& file, char const* source, int line) : DwarfException((boost::format("Couldn't filnd file %1%") % file.GetPath().ToString()).str(), source, line) {

}
}