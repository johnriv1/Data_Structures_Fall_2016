#include <cassert>
#include "superhero.h"
#include "team.h"

bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

void Team::operator+=(const Superhero &a){
	superheroes.push_back(a);
}

void Team::operator-=(const Superhero &a){
	superheroes.remove(a);
}

Team operator+(const Superhero &a, const Superhero &b){
	Team answer;
	answer+=(a);
	answer+=(b);
	return answer;
}

Team operator+(const Team &a, const Team &b){
	Team answer;
	std::list<Superhero>::const_iterator aitr;
	for (aitr = (a.superheroes).begin(); aitr != (a.superheroes).end(); aitr++) {
		answer+=(*aitr);
	}
	std::list<Superhero>::const_iterator bitr;
	for (bitr = (b.superheroes).begin(); bitr != (b.superheroes).end(); bitr++) {
		answer+=(*bitr);
	}
	return answer;
}

Team operator+(const Team &a, const Superhero &b) {
	Team answer;
	std::list<Superhero>::const_iterator aitr;
	for (aitr = (a.superheroes).begin(); aitr != (a.superheroes).end(); aitr++) {
		answer+=(*aitr);
	}
	answer+=(b);
	return answer;
}

std::string Team::getName() const {
  if (superheroes.size() == 0) 
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

