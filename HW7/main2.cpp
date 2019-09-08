#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <list>

#include "PersonClass.h"

typedef std::map<std::string, int> COSTUME_SHOP_TYPE;
typedef std::map<PersonClass, std::string> PEOPLE_TYPE;
typedef std::map<std::string, int>::iterator COSTUME_SHOP_ITER;
typedef std::map<PersonClass, std::string>::iterator PEOPLE_ITER;
typedef std::map<std::string, std::list<PersonClass> > COSTUME_PEOPLE_TYPE;

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people, COSTUME_PEOPLE_TYPE& rented_costumes);
void lookup(COSTUME_SHOP_TYPE& costume_shop, COSTUME_PEOPLE_TYPE& rented_costumes);
void printPeople(PEOPLE_TYPE& people);

int main() {
  // two data structures store all of the information for efficiency
  COSTUME_SHOP_TYPE costume_shop;
  PEOPLE_TYPE people;
  COSTUME_PEOPLE_TYPE rented_costumes;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addCostume(costume_shop);
    } else if (c == 'r') {
      rentCostume(costume_shop,people,rented_costumes);
    } else if (c == 'l') {
      lookup(costume_shop, rented_costumes);
    } else if (c == 'p') {
      printPeople(people);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
  std::string costume_name;
  int num;
  std::cin >> costume_name >> num;
  costume_shop[costume_name] += num;
  if (num > 1) {
	std::cout << "Added " << num << " " << costume_name << " costumes." << std::endl; 
  }
  else if (num == 1){
	std::cout << "Added 1 " << costume_name << " costume." << std::endl; 
  }
}


void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people, COSTUME_PEOPLE_TYPE& rented_costumes) {
  std::string first_name;  
  std::string last_name;
  std::string costume_name;
  std::cin >> first_name >> last_name >> costume_name;
  PersonClass curr_person(first_name, last_name);
  COSTUME_SHOP_ITER find_costume_iter = costume_shop.find(costume_name);
  PEOPLE_ITER find_person_iter = people.find(curr_person);
  
  //if shop doesnt have costume
  if (find_costume_iter == costume_shop.end()) {
	std::cout << "The shop doesn't carry " << costume_name << " costumes." << std::endl;
	people.insert(std::make_pair(curr_person, ""));
  }
  //if shop has costume but no more are available
  else if (costume_shop[costume_name] == 0) {
	std::cout << "No " << costume_name << " costumes available." << std::endl;
	people.insert(std::make_pair(curr_person, ""));
  }
  //if shop has costume and more are available but the person already is renting same costume
  else if (find_person_iter != people.end() && people[curr_person] == costume_name) {
	  std::cout << first_name << " " << last_name << " already has a " << costume_name << " costume." << std::endl;
  }
  //if person is new to the shop
  else if (find_person_iter == people.end() || (find_person_iter != people.end() && people[curr_person] == "" )) {
	//decrement amount of desired costume in shop
	costume_shop[costume_name] -= 1;
	//add costume onto the rented costume and push_back the person renting it.
	rented_costumes[costume_name].push_back(curr_person);
	//add person onto the map as key with their rented costume as the value
	people[curr_person] = costume_name;
	
	std::cout << first_name << " " << last_name << " rents a " << costume_name << " costume." << std::endl;
  }
  //person already renting a different costume, so return that costume and rent the new one
  else {
	std::string prevCostume = people[curr_person];
	//increment costume person was perviously holding in shop b/c costume is returned to shop;
	costume_shop[prevCostume] += 1;
	//remove the person from the list corresponding to the previous costume they were renting.
	rented_costumes[prevCostume].remove(curr_person);
	//make the rented costume the new value for the person in the map
	people[curr_person] = costume_name;
	//go to costume in rented and push_back the person renting it.
	//or create costume in rented and push_back the person renting it.
	rented_costumes[costume_name].push_back(curr_person);
	//decrement amount of desired costume in shop
	costume_shop[costume_name] -=1;
	std::cout << first_name << " " << last_name << " returns a " << prevCostume << " costume before renting a " << costume_name << " costume." << std::endl;
  }
}


void lookup(COSTUME_SHOP_TYPE& costume_shop, COSTUME_PEOPLE_TYPE& rented_costumes) {
  std::string costume_name;
  std::cin >> costume_name;

  if (costume_shop.find(costume_name) == costume_shop.end()) {
	  std::cout << "The shop doesn't carry " << costume_name << " costumes." << std::endl;
  }
  else {
	  std::cout << "Shop info for " << costume_name << " costumes:" << std::endl;
	  if (costume_shop[costume_name] == 1) {
		  std::cout << "  1 copy available" << std::endl;
	  }
	  else if (costume_shop[costume_name] > 1) {
		  std::cout << "  " << costume_shop[costume_name] << " copies available" << std::endl;
	  }
	  if (rented_costumes[costume_name].size() > 0) {
		  if (rented_costumes[costume_name].size() == 1) {
			  std::cout << "  1 copy rented by:" << std::endl;
		  }
		  else if (rented_costumes[costume_name].size() > 1) {
			  std::cout << "  " << rented_costumes[costume_name].size() << " copies rented by:" <<std::endl;
		  }
		  for (std::list<PersonClass>::iterator itr = rented_costumes[costume_name].begin() ; itr != rented_costumes[costume_name].end(); itr++) {
			  std::cout << "    " << itr->get_fname() << " " << itr->get_lname() << std::endl;
		  }
	  }
  }
}


void printPeople(PEOPLE_TYPE& people) {
	if (people.size() == 1) {
		std::cout << "Costume info for the 1 party attendee:" << std::endl; 
	}
	else if (people.size() > 1) {
		std::cout << "Costume info for the " << people.size() <<  " party attendees:" << std::endl; 		
	}
	for (PEOPLE_ITER itr = people.begin() ; itr != people.end(); itr++) {
		if (itr->second != "") {
			std::cout << "  " << (itr -> first).get_fname() << " " << (itr -> first).get_lname() << " is wearing a " << (itr->second)  << " costume." << std::endl;
		}
		else {
			std::cout << "  " << (itr -> first).get_fname() << " " << (itr -> first).get_lname() << " does not have a costume." << std::endl;
		}
	}
}
