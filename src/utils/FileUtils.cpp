/*
 * FileUtils.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: monofraps
 */
#include "FileUtils.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "log/Log.h"

namespace glove {
// TODO: wchar_t support
std::string ReadFileToString(std::string filePath)
{
        std::ifstream file(filePath.c_str());
        if(!file.is_open())
        {
                LOG(logging::globalLogger, error, "Unable to open file " << filePath);
				return "";
        }

        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();

        return fileData.str();
} // namespace glove
}


