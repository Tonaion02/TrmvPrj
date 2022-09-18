#include "Data/Items/CreationItemFunctions.h"

//Including some Data info
#include "Data/Items/Item.h"
#include "Data/Items/ConsumableItem.h"
//Including some Data info





Item* createPotion(const XMLvariab& itemInfo)
{
	return static_cast<Item*>(new Potion(itemInfo));
}