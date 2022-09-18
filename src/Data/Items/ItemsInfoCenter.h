#pragma once

#include <array>
#include <vector>

#include "utils/StringAndFile/XMLvariab.h"

#include "Item.h"





class ItemInfoCenter
{
public:
	static ItemInfoCenter& get()
	{
		static ItemInfoCenter instance;
		return instance;
	}

	void addItemPrototype(class Item* item);
	class Item* getItemPrototype(unsigned int idItem);

	unsigned int assignNewIdItem();
	void trackCategory(CategoryItem category);

	unsigned int maxItems() const;

	class Item* createItem(XMLvariab& infoItem);

protected:
	ItemInfoCenter();

protected:
	//Counters of the number of items for all categories
	std::array<unsigned int, MAX_CATEGORIES> pagingCategories;
	//Array of all the prototypes of Items
	std::array<class Item*, MAX_ITEMS> itemPrototypes;
};



void loadItems(const std::string& path);