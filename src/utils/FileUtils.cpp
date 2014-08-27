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


namespace glove {
std::string ReadFileToString(std::string filePath)
{
        std::ifstream file(filePath.c_str());
        if(!file.is_open())
        {
                std::cout << "Unable to open file " << filePath << std::endl;
        }

        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();

        return fileData.str();
}
}


