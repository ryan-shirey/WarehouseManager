/*Joey Weidman, Ryan Shirey
  Represents a warehouse that stores food.

  The inventory is represented by a map that
  maps food names to a just of all the food items with that name.

  All of the logic for adding and removing food is done inside 
  of this warehouse class. The manager calls these functions.
 */

#include "FoodItem.h"
#include "Warehouse.h"
#include <iostream>
#include <map>

using namespace std;

Warehouse::Warehouse()
{
  
}

void Warehouse::add(FoodItem food, int amount)
{
  for(int i = 0; i < amount; i++)
  {
    inventory[food.getName()].push_back(food);
    //cout << inventory[food.getName()].getShelfLife() << endl;
  }
}

void Warehouse::remove(FoodItem food, int amount)
{
  //cout << "hit1" << endl;
  if(inventory.find(food.getName()) == inventory.end() )
  {
    return;
  }
  else
  {
    vector<FoodItem> *foodItems = &inventory[food.getName()];
    if(foodItems->size() <= amount)
      inventory.erase(food.getName());
    else
    {
      foodItems->erase(foodItems->begin(), foodItems->begin() + amount);
    }
  }
}

void Warehouse::update()
{
  //cout << "hit" << endl;
  vector <string> emptyFood;
  map<string, vector<FoodItem> >::iterator it = inventory.begin();
  while(it != inventory.end())
  {
    string foodName = it->first;
    vector<FoodItem> *foodItems = &(it->second);
    
    for(int i = 0; i < foodItems->size(); i++)
    {
      foodItems[0][i].decrementSL();
    }
    int j = foodItems->size();
    //cout << foodName<< endl;
    for(int i = 0; i < j; i++)
    {
      if(foodItems[0][0].getShelfLife() == 0)
	foodItems->erase(foodItems->begin(), foodItems->begin() + 1);
      else
	break;    
    }
    if(foodItems->size() == 0)
    {
      emptyFood.push_back(foodName);
    }  
    it++;
  }
  for(int i = 0; i<emptyFood.size(); i++)
  {
    inventory.erase(emptyFood[i]);
  }
 
  
}

void Warehouse::printFoodInWarehouse()
{
  cout << "Inventory in warehouse: " << endl;
  
  map<string, vector<FoodItem> >::iterator it = inventory.begin();
  while(it != inventory.end())
  {
    string foodName = it->first;
    vector<FoodItem> food = it->second;

    cout << foodName << food.size() << endl;
    it++;
  }
}

bool Warehouse::hasProduct(FoodItem food)
{
  if(inventory.find(food.getName()) == inventory.end())
  {
    return false;
  }
  else
  {
    return true;
  }
}


