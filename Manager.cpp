/*Joey Weidman, Ryan Shirey

  The main class for assignment 4.
  Adds and removes items from the warehouses accordingly.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <stdlib.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "FoodItem.h"
#include "Warehouse.h"

using namespace std;
using namespace boost::gregorian;

map<string, FoodItem> foodList; //Map UPC's to Food Items
map<string, Warehouse> warehouseList; //Map Locations to Warehouses
map<int, string> popularSort;
vector<string> wellStocked;
vector<string> notStocked;

//Debugging functions below
void printFood()
{
  cout << "Food Items: " << endl;

  map<string, FoodItem>::iterator it = foodList.begin();
  while(it != foodList.end())
  {
    string upc = it->first;
    FoodItem food = it->second;
    cout << upc << " : " << food.getName() << endl;
    it++;
  }
}

void printWarehouses()
{
  cout << "Warehouses: " << endl;

  map<string, Warehouse>::iterator it = warehouseList.begin();
  while(it != warehouseList.end())
  {
    string location = it->first;
    Warehouse warehouse = it->second;
    cout << location  << endl;
    it++;
  }
}

int main(int argc, char* argv[])
{
  if(argc != 2) //Check if the user enters more than one argument
  {
    cout << "Invalid amount of arguments." << endl;
    return 0;
  }

  ifstream  inFile(argv[1]); //Set the file to the argument entered

  string fullLine;
  while(getline(inFile, fullLine)) //Read the file one line at a time
  {
    string buf;
    stringstream ss(fullLine);
    vector<string> tokens;
    while(ss >> buf)
      tokens.push_back(buf);
    
    if(tokens[0] == "FoodItem")
    {
      string upc = tokens[4]; //Get the upc
      int shelfLife = atoi(tokens[7].c_str()); //Get the shelf life
      
      string foodName;
      for(int i = 9; i < tokens.size(); i++) //Get the full name of the item
      {
        foodName += tokens[i];
        foodName += ' ';
      }
      
      FoodItem food(upc, foodName, shelfLife);
      foodList[upc] = food;
      //cout << upc << ' ' << shelfLife << ' ' << foodName << endl;
    }
    if(tokens[0] == "Warehouse")
    {
      string location = tokens[2];

      Warehouse warehouse;
      warehouseList[location] = warehouse;
      //cout << location << endl;
    }
    if(tokens[0] == "Start")
    {
      string year;
      string day;
      string month;
      string myDate;
      string s = tokens[2];
      
      year = s.substr(6, 4);
      day = s.substr(3, 2);
      month = s.substr(0, 2);

      myDate += string(year) + string(day) + string(month);
      date d(from_undelimited_string(myDate));
      
      //cout << myDate << endl;
    }
    if(tokens[0] == "Receive:")
    {
      string upc = tokens[1];
      int amount = atoi(tokens[2].c_str());
      string location = tokens[3];

      //cout << "Adding " << foodList[upc].getName() << "to " << location << endl;
      warehouseList[location].add(foodList[upc], amount);
      //cout << upc << ' ' << amount << ' ' << location << endl;
    }
    if(tokens[0] == "Request:")
    {
      string upc = tokens[1];
      int amount = atoi(tokens[2].c_str());
      string location = tokens[3];
      foodList[upc].requests = foodList[upc].requests + amount;
      warehouseList[location].remove(foodList[upc], amount);
      //cout << upc << ' ' << amount << ' ' << location << endl;
    }
    if(tokens[0] == "Next")
    {
      map<string, Warehouse >::iterator it = warehouseList.begin();
      while(it != warehouseList.end() )
      {
	//cout << it->first << endl;
	Warehouse *h = &(it->second);
	h->update();
	it++;
      }
    }
    if(tokens[0] == "End")
    {
     
      //each fooditem
      map<string, FoodItem>::iterator itFood = foodList.begin();
      
      while(itFood!= foodList.end())
	{
	  popularSort.insert(pair<int, string> (foodList[itFood->first].requests, itFood-> first));
	  //cout<<itFood->first<<endl;
	  map<string, Warehouse>::iterator itHouse = warehouseList.begin();
	  int stockCount = 0;
	  while(itHouse!=warehouseList.end()&&stockCount<2)
	    {
	      if(itHouse->second.hasProduct(itFood->second))
		{
		  stockCount++;
		}
	      itHouse++;
	    }
	  if(stockCount>=2)
	    {
	      //cout<< itFood -> first<< " well stocked"<<endl;
	      wellStocked.push_back(itFood->first);
	    }
	  if(stockCount == 0)
	    {
	      // cout<< itFood -> first<< " not stocked"<<endl;
	      notStocked.push_back(itFood->first);
	    }
	  itFood++;
	}
      
      
    }
  }
  //Print To Console
  cout<<"Report by Joey Weidman and Ryan Shirey"<<endl;
  cout<<endl;
  cout<<"Unstocked Products:"<<endl;
  for(int i = 0; i< notStocked.size(); i++){
    cout<< notStocked[i]<< " "<< foodList[notStocked[i]].getName()<<endl;
  }
  cout<<endl;
  cout<<"Well-Stocked Products:"<<endl;
  for(int i =0; i< wellStocked.size(); i++){
    cout<< wellStocked[i]<< " "<<foodList[wellStocked[i]].getName()<<endl;
  }
  cout<<endl;
  cout<<"Most Popular Products:"<<endl;
  map<int, string>::iterator itPop = popularSort.end();
  int j = popularSort.size();
  for(int i = 0; i<3; i++)
    {
      if(j>0){
      itPop--;
      cout<< itPop->second<< " "<<foodList[itPop->second].getName()<<endl;
      j--;
      }
    }
  }
