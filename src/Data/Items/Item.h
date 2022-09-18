#pragma once





#define MAX_ITEMS 30

enum CategoryItem
{
	NoneTypeItem = -1,
	NoneEffects, //like money, only for counting
	Consumable, //you can use only one time
	Tool,
	max //Last CategoryItem-value used tracked the number of categories of Items
};

#define MAX_CATEGORIES CategoryItem::max



class Item
{
public:
	Item(CategoryItem category);

	CategoryItem getTypeItem() const;
	unsigned int getIdItem() const;

private:
	short int categoryItem;
	unsigned int idItem;
};