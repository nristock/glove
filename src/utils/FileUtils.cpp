#include "FileUtils.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/format.hpp>

#include "log/Log.h"

namespace glove {
// TODO: wchar_t support
std::string ReadFileToString(std::string filePath)
{
        std::ifstream file(filePath.c_str());
        if(!file.is_open())
        {
                LOG(logging::globalLogger, error, (boost::format("Unable to open file %1%") % filePath).str());
				return "";
        }

        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();

        return fileData.str();
} // namespace glove
}


