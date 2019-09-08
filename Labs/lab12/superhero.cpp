#include "superhero.h"

Superhero::Superhero() {
	name_ = "";
	power_= "";
	true_identity_ = "";
	good_guy_ = true;
}

Superhero::Superhero(std::string name, std::string true_identity, std::string power) {
	name_ = name;
	power_ = power;
	true_identity_ = true_identity;
	good_guy_ = true;
}


std::string Superhero::getName() const {
	return name_;
}

std::string Superhero::getPower() const {
	return power_;
}

std::string Superhero::getTrueIdentity() const {
	return true_identity_;
}

bool Superhero::isGood() const {
	return good_guy_;
}

std::ostream& operator<<(std::ostream& ostr, Superhero const& s) {
	if (s.isGood()) {
		ostr << "Superhero " << s.getName() << " has power " << s.getPower() << "\n";
	}
	else if (!s.isGood()) {
		ostr << "Supervillain " << s.getName() << " has power " << s.getPower() << "\n";
	}
	return ostr;
}

bool operator==(Superhero const& s, std::string const& guess) {
	return (s.getTrueIdentity() == guess);
}

bool operator!=(Superhero const& s, std::string const& guess) {
	return (s.getTrueIdentity() != guess);
}

void operator-(Superhero & s) {
	if (s.good_guy_ == false) {
		s.good_guy_ = true;
	}
	else {
		s.good_guy_ = false;
	}
}

bool operator>(Superhero const& s1, Superhero const& s2) {
	
	if (s1.getPower() == "Fire" && s2.getPower() == "Wood") {
		return true;
	}
    else if (s1.getPower() == "Wood" && s2.getPower() == "Water") {
		return true;
	}
	else if (s1.getPower() == "Water" && s2.getPower() == "Fire") {
		return true;
	}
	
	else if (s1.getPower() == "Speed" && s2.getPower() == "Laser") {
		return true;
	}
	else if (s1.getPower() == "Laser" && s2.getPower() == "Flying") {
		return true;
	}
	else if (s1.getPower() == "Flying" && s2.getPower() == "Speed") {
		return true;
	}
	
	return false;
}

bool operator==(Superhero const& s1, Superhero const& s2) {
	return (s1.getPower() == s2.getPower() && s1.getName() == s2.getName());
}
