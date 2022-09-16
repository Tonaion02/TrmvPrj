#include "Data/Level/ChestTile.h"

#include "utils/StringAndFile/MyString.h"





ChestTile::ChestTile(XMLvariab& variab)
	:isOpened(false)
{
	std::vector<std::string> stringIdImages = split(variab.getValue("images"), ",");
	for (std::string s : stringIdImages)
		idImages.push_back(std::stoi(s));

	idItem = std::stoi(variab.getValue("idItem"));
	internalLayer = std::stoi(variab.getValue("internalLayer"));
}