#ifndef PERSONCLASS
#define PERSONCLASS

#include <string>

class PersonClass {
public:
	//CONSTRUCTOR
	PersonClass(std::string fname, std::string lname);
	std::string get_lname() const;
	std::string get_fname() const;
	
private:
	std::string fname_;
	std::string lname_;
}
;

bool operator< (const PersonClass& p1, const PersonClass& p2);
bool operator== (const PersonClass& p1, const PersonClass& p2);


#endif