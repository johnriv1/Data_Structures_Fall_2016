#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_

#include <string>
#include <iostream>
#include <list>
#include "team.h"

class Team;

class Superhero {

public:

 friend Team;
 
 friend bool operator==(Superhero const& s, std::string const& guess);
 
 friend bool operator!=(Superhero const& s, std::string const& guess);
 
 friend void operator-(Superhero& s);
 
 Superhero();

 Superhero(std::string name, std::string true_identity, std::string power);
 
 bool isGood() const;
 
 std::string getName() const;
 std::string getPower() const;
 
private:

 std::string name_;
 std::string power_;
 std::string true_identity_;
 bool good_guy_;
 
 std::string getTrueIdentity() const;

};

std::ostream& operator<<(std::ostream& ostr, Superhero const& s);

bool operator==(Superhero const& s, std::string const& guess);

bool operator==(Superhero const& s1, Superhero const& s2);

bool operator!=(Superhero const& s, std::string const& guess);

void operator-(Superhero& s);

bool operator>(Superhero const& s1, Superhero const& s2);

#endif