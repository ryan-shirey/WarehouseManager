/*Joey Weidman, Ryan Shirey
  Represents a food item for for Assignment4.

  Contains it's UPC, name, and shelf life
*/

#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

class FoodItem
{
 public:
  FoodItem();
  FoodItem(std::string upc, std::string name, int shelfLife);
  std::string getUpc();
  std::string getName();
  int requests;
  int getShelfLife();
  void decrementSL();
 private:
  std::string upc;
  std::string name;
  int shelfLife;
};

#endif
