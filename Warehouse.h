#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <string>
#include <map>
#include <vector>
#include "FoodItem.h"

class Warehouse
{
 public:
  Warehouse();

  void add(FoodItem food, int amount);
  void remove(FoodItem food, int amount);
  void update();
  //Below is for debugging
  void printFoodInWarehouse();
  bool hasProduct(FoodItem food);
  
    
 private:
  std::map< std::string, std::vector<FoodItem> > inventory;
  
};

#endif
