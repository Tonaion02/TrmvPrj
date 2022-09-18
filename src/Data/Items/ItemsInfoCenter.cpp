#include "Data/Items/ItemsInfoCenter.h"

//Including some info about Data
#include "Data/Items/NoneEffectsItem.h"
#include "Data/Items/ConsumableItem.h"
#include "Data/Items/ToolItem.h"
//Including some info about Data

//Including some utils
#include "utils/PersonalAssert.h"

#include "utils/StringAndFile/MyString.h"
//Including some utils





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ItemInfoCenter
//-----------------------------------------------------------------------------------------------------------------------------------------
ItemInfoCenter::ItemInfoCenter()
{
	pagingCategories.fill(0);
	itemPrototypes.fill(nullptr);
}



void ItemInfoCenter::addItemPrototype(class Item* item)
{
	itemPrototypes[item->getIdItem()] = item;
}



Item* ItemInfoCenter::getItemPrototype(unsigned int idItem)
{
	return itemPrototypes[idItem];
}



unsigned int ItemInfoCenter::assignNewIdItem()
{
	static unsigned int nextIdItem = 0;
	ASSERT(nextIdItem == MAX_ITEMS);
	return nextIdItem++;
}



void ItemInfoCenter::trackCategory(CategoryItem category)
{
	int index = static_cast<int>(category) + 1;
	if (index < MAX_CATEGORIES)
		pagingCategories[index]++;
}



Item* ItemInfoCenter::createItem(XMLvariab& infoItem)
{
	//Distinguish from name of XMLvariab what prototype of items is
	if (infoItem.name == "Potion")
		return static_cast<Item*>(new Potion(infoItem));
	else if (infoItem.name == "Medpotion")
		return static_cast<Item*>(new Medpotion(infoItem));
	else if (infoItem.name == "Bigpotion")
		return static_cast<Item*>(new Bigpotion(infoItem));
	else if (infoItem.name == "AttackUp")
		return static_cast<Item*>(new AttackUp(infoItem));
	else if (infoItem.name == "DefUp")
		return static_cast<Item*>(new DefUp(infoItem));
	else if (infoItem.name == "HealthUp")
		return static_cast<Item*>(new HealthUp(infoItem));
	//Distinguish from name of XMLvariab what prototype of items is

	//Error case
	__debugbreak();
	return nullptr;
	//Error case
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class ItemInfoCenter
//-----------------------------------------------------------------------------------------------------------------------------------------



void loadItems(const std::string& path)
{
	//Take all the lines of the files
	std::vector<std::string> lines = getLines(path);
	//Take all the lines of the files

	//Delete the first two lines and last lines of the files
	lines.erase(lines.begin());
	lines.erase(lines.begin());
	lines.pop_back();
	//Delete the first two lines and last lines of the files

	//Extract the XMLvariables from the lines of the files
	std::vector<XMLvariab> itemsInfo = getXMLvariables(lines);
	//Extract the XMLvariables from the lines of the files

	//From XMLvariab create the Item
	for (XMLvariab& itemInfo : itemsInfo)
		ItemInfoCenter::get().addItemPrototype(ItemInfoCenter::get().createItem(itemInfo));
	//From XMLvariab create the Item
}