// A simple "caller ID" program
#include <map>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(std::map<int, std::string> &phonebook, int number, string const& name) {
	phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(std::map<int,std::string> &phonebook, int number) {
	std::map<int, std::string>::iterator tmp = phonebook.find(number);
	if (tmp == phonebook.end()) {
		cout << "unknown caller!" << endl;
	}
	else {
		cout << tmp -> second << " is calling" << endl;
	}
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  //vector<string> phonebook(10000, "UNASSIGNED");
  std::map<int, std::string> phonebook;

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 3333);
  identify(phonebook, 4444);
  identify(phonebook, 1000000);
  
}
