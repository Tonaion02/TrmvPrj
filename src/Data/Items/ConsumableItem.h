#pragma once

#include "ECS/Entity.h"

#include "Data/Items/Item.h"

#include "utils/StringAndFile/XMLvariab.h"





class ConsumableItem : public Item
{
public:
	ConsumableItem() : Item(CategoryItem::Consumable) {}

	virtual void consume(Entity e) = 0;
};



class ModifierStatsItem : public ConsumableItem
{
public:
	ModifierStatsItem(XMLvariab& infoItem);

	int getAttackHeal() const;
	int getDefHeal() const;
	int getHealthHeal() const;

protected:
	int attackHeal;
	int defHeal;
	int healthHeal;
};



class HealingItem : public ModifierStatsItem
{
public:
	HealingItem(XMLvariab& infoItem) : ModifierStatsItem(infoItem) {}

	virtual void consume(Entity e) override;
};



class BuffItem : public ModifierStatsItem
{
public:
	BuffItem(XMLvariab& infoItem) : ModifierStatsItem(infoItem) {}

	virtual void consume(Entity e) override;
};



class Potion : public HealingItem
{
public:
	Potion(XMLvariab& infoItem);
};



class Medpotion : public HealingItem
{
public:
	Medpotion(XMLvariab& infoItem);
};



class Bigpotion : public HealingItem
{
public:
	Bigpotion(XMLvariab& infoItem);
};



class AttackUp : public BuffItem
{
public:
	AttackUp(XMLvariab& infoItem);
};



class DefUp : public BuffItem
{
public:
	DefUp(XMLvariab& infoItem);
};



class HealthUp : public BuffItem
{
public:
	HealthUp(XMLvariab& infoItem);
};