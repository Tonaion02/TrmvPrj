#include "utils/StringAndFile/XMLvariab.h"

#include "utils/StringAndFile/MyString.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class XMLvariab
//-----------------------------------------------------------------------------------------------------------------------------------------
XMLvariab::XMLvariab(const std::string& line)
{
	std::string newline = removeFrontSpace(line);
	std::vector<std::string> infoAboutLine = split(newline, " ");

	//Take name from element
	name = remove(infoAboutLine[0], "<");
	//Take name from element

	//Eliminate "<nameElement" from infoAboutLine
	infoAboutLine.erase(infoAboutLine.begin());
	//Eliminate "<nameElement" from infoAboutLine

	if (infoAboutLine.size() > 0)
	{
		//Eliminate "/>" from last element
		if (isInString(infoAboutLine[infoAboutLine.size() - 1], ">"))
		{
			infoAboutLine[infoAboutLine.size() - 1] = remove(infoAboutLine[infoAboutLine.size() - 1], ">");
		}

		if (isInString(infoAboutLine[infoAboutLine.size() - 1], "/"))
		{
			infoAboutLine[infoAboutLine.size() - 1] = remove(infoAboutLine[infoAboutLine.size() - 1], "/");
		}
		//Eliminate "/>" from last element

		//Take the value and the key(name) from the line
		std::string value;
		std::string key;
		for (auto info : infoAboutLine)
		{
			value = removeQuotationMarks(stride(info, "="));
			key = stride(info, 0, findInString(info, "="));
			values[key] = value;
		}
		//Take the value and the key(name) from the line
	}
}



//XMLvariab(const std::vector<std::string>& lines)
//{
//
//}



std::string XMLvariab::getValue(const std::string& key)
{
	//AGGIUNGERE ASSERT
	if (values.find(key) == values.end())
		return "nothing";

	return values[key];
}



void XMLvariab::createValue(const std::string& name, const std::string& value)
{
	values[name] = value;
}



std::vector<XMLvariab> getXMLvariables(const std::vector<std::string>& lines)
{
	std::vector<XMLvariab> xmlVariables;

	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines[i];

		if (isInString(line, "?>"))
		{
			//For now
			continue;
		}
		else if (isInString(line, "/>"))
		{
			xmlVariables.push_back(XMLvariab(line));
		}
		else
		{
			std::vector<std::string> collector;
			std::string firstLine = line;

			std::string terminator = removeFrontSpace(line);
			terminator = terminator.substr(0, terminator.find(" "));
			terminator.insert(terminator.begin() + terminator.find("<") + 1, '/');
			terminator = terminator + ">";

			i++;
			line = removeFrontSpace(lines[i]);

			while (i < lines.size() && line != terminator)
			{
				collector.push_back(line);

				i++;
				line = removeFrontSpace(lines[i]);
			}

			XMLvariab var = XMLvariab(firstLine);
			var.withRawData = true;
			var.rawData = collector;
			xmlVariables.push_back(var);
		}
	}

	return xmlVariables;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class XMLvariab
//-----------------------------------------------------------------------------------------------------------------------------------------