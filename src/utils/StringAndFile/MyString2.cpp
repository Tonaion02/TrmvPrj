#include <fstream>

#include "utils/StringAndFile/MyString.h"





std::vector<std::string> getLines(const std::string& filePath)
{
	std::vector<std::string> lines;
	std::string line;

	std::ifstream file(filePath.c_str());

	while (getline(file, line))
		lines.push_back(line);

	file.close();

	return lines;
}