#include "Data/Items/Item.h"

#include "Data/Items/ItemsInfoCenter.h"





//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Item
//-----------------------------------------------------------------------------------------------------------------------------------------
Item::Item(CategoryItem category)
	:categoryItem(static_cast<short int>(category)), idItem(ItemInfoCenter::get().assignNewIdItem())
{
	ItemInfoCenter::get().trackCategory(category);
}



CategoryItem Item::getTypeItem() const 
{ 
	return static_cast<CategoryItem>(categoryItem); 
}



unsigned int Item::getIdItem() const
{
	return idItem;
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//Class Item
//-----------------------------------------------------------------------------------------------------------------------------------------