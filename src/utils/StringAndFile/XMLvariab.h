#pragma once

#include <string>
#include <unordered_map>





struct XMLvariab
{
public:
	XMLvariab() :name("")
	{
		values.clear();
		rawData.clear();
	}
	XMLvariab(const std::string& line);

	std::string getValue(const std::string& key);
	void createValue(const std::string& name, const std::string& value);

	//Da aggiungere in futuro(possibilità di ottenere a partire da un unordered_map e un nome una linea da inserire in un testo)
	//std::string getLineFromValues(const std::string& name);

public:

	bool withRawData = false;
	std::vector<std::string> rawData;

	std::string name;
	std::unordered_map<std::string, std::string> values;
};



std::vector<XMLvariab> getXMLvariables(const std::vector<std::string>& lines);