#include "PersonClass.h"

PersonClass::PersonClass(std::string fname, std::string lname) {
	fname_ = fname;
	lname_ = lname;
}

std::string PersonClass::get_lname() const{
	return lname_;
}

std::string PersonClass::get_fname() const{
	return fname_;
}

bool operator< (const PersonClass& p1, const PersonClass& p2) {
	return p1.get_lname() < p2.get_lname() ||
		(p1.get_lname() == p2.get_lname() && p1.get_fname() < p2.get_fname());
}

bool operator== (const PersonClass& p1, const PersonClass& p2){
	return ((p1.get_lname() == p2.get_lname()) && (p1.get_fname() == p2.get_fname()));
}