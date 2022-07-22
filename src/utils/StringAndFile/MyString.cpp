#include <fstream>
#include <algorithm>

#include "utils/StringAndFile/MyString.h"





//Mehtod on String
std::vector<std::string> getLines(const std::string& fileName)
{
	std::vector<std::string> lines;
	std::string line;

	std::ifstream file(fileName.c_str());

	while (getline(file, line))
	{
		lines.push_back(line);
	}

	file.close();

	return lines;
}

void savelines(const std::string& fileName, const std::vector<std::string>& lines)
{
	std::ofstream file(fileName);
	for (int i = 0; i < lines.size(); i++)
	{
		file.write(lines[i].c_str(), lines[i].size());
	}

	file.close();
}

std::string stride(const std::string& origin, const std::string& x)
{
	return origin.substr(origin.find(x) + strlen(x.c_str()), origin.size());
}

std::string stride(const std::string& origin, int start, int end)
{
	return origin.substr(start, end);
}

std::string remove(const std::string& origin, const std::string& x)
{
	int index;
	std::string copy = origin;
	while (true)
	{
		index = copy.find(x);
		if (index >= 0)
			for (int i = index; i < index + x.size(); i++)
			{
				copy.erase(i, 1);
			}
		else
			break;
	}
	return copy;
}

std::vector<std::string> split(const std::string& origin, const std::string& x)
{
	std::string copy = origin;
	std::vector<std::string> r;

	while (true)
	{
		int index = copy.find(x);
		if (index >= 0)
		{
			r.push_back(copy.substr(0, index));
			copy = copy.substr(index + x.size(), copy.size());
		}
		else
		{
			if (copy.size() > 0)
				r.push_back(copy);
			break;
		}
	}

	/*
	for (int i = 0; i < copy.size(); i++)
	{
		int index = copy.find(x, i);
		if (index >= 0)
		{
			r.push_back(copy.substr(i, index - i));
			copy = copy.substr(index - i + x.size() -1, copy.size());
		}
		else
		{
			//if(index < copy.size() - 1)
				//r.push_back(copy.substr())
			break;
		}

	}
	*/

	return r;
}

bool isCommentLine(const std::string& origin)
{
	return (origin.find("//") != -1);
}

bool isInString(const std::string& origin, const std::string& x)
{
	bool sem = origin.find(x) != -1;
	return origin.find(x) != -1;
}

std::string removeFrontSpace(const std::string& origin)
{
	std::string space = " ";
	std::string copy = origin;
	while (true)
	{
		if (copy[0] == space[0])
		{
			copy = copy.substr(1, copy.size());
		}
		else
		{
			break;
		}
	}

	return copy;
}

std::string removeQuotationMarks(const std::string& origin)
{
	int index;
	std::string copy = origin;
	
	copy.erase(std::remove(copy.begin(), copy.end(), '\"'), copy.end());

	return copy;
}

int findInString(const std::string& origin, const std::string& x)
{
	return origin.find(x);
}

bool fromStringToBool(const std::string& origin)
{
	//AUMENTARE VERSATILITA E SOPRATUTTO AGGIUNGERE ASSERT NEL CASO NON SIA UGUALE A NESSUNO DEI DUE
	if (origin == "false")
	{
		return false;
	}
	else if (origin == "true")
	{
		return true;
	}
}
//Mehtod on String