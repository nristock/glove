#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/format.hpp>

#include "glove/utils/FileUtils.hpp"
#include "glove/log/Log.hpp"

namespace BlueDwarf {
// TODO: wchar_t support
std::string ReadFileToString(std::string filePath)
{
        std::ifstream file(filePath.c_str());
        if(!file.is_open())
        {
                L_ERROR(fmt::format("Unable to open file {0}", filePath));
				return "";
        }

        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();

        return fileData.str();
} // namespace BlueDwarf
}


