#include "FoodItem.h"


using namespace std;

FoodItem::FoodItem()
{
  
}

FoodItem::FoodItem(string upc, string name, int shelfLife)
{
  this->upc = upc;
  this->name = name;
  this->shelfLife = shelfLife;
}

string FoodItem::getUpc()
{
  return upc;
}

string FoodItem::getName()
{
  return name;
}

int FoodItem::getShelfLife()
{
  return shelfLife;
}

void FoodItem::decrementSL()
{
  shelfLife--;
}

