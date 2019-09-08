// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <iostream>
#include <cassert>
#include <cmath>
#include "playing_card.h"
#include "node.h"
#include "deck.h"

// ==================================================================================

int DeckSize(Node* top) {
	Node* tmp = top;
	int Count = 0;
	while (tmp != NULL) {
		Count ++;
		tmp = tmp -> after;
	}
	return Count;
}

Node* CopyDeck(Node* old_head) {
	Node* new_head;
	Node* tmpNew;
	Node* tmpOld = old_head;
	Node* prev;
	if (tmpOld == NULL) {
		new_head = NULL;
	}
	else {
		if (tmpOld->before == NULL) {
			new_head = new Node(tmpOld->getCard());
			tmpNew = new_head;
			prev = NULL;
		}
		while (tmpOld->after != NULL) {
			tmpNew->after = new Node((tmpOld->after)->getCard());
			tmpNew->before = prev;
			prev = tmpNew;
			tmpNew = tmpNew->after;
			tmpOld = tmpOld->after; 
		}
		tmpNew -> after = NULL;
		tmpNew -> before = prev;
	}
	return new_head;
}

void CutDeck(Node* deck, Node*& top, Node*& bottom, std::string shuffletype){
	if (shuffletype == "perfect") {
		//first half will be bigger if deck is odd
		int First_Half_Size = (int) (ceil(DeckSize(deck)/2.0));
		int firstCount = 0;
		//beginning of top half is beginning of original deck
		top = deck;
		//will move toptmp
		Node* toptmp = top;
		//if deck is empty, so are the bottom and top half.
		if (deck == NULL) {
			top = NULL;
			bottom = NULL;
		}
		else {
			//will end up pointing to one node beond half
			while (firstCount < First_Half_Size) {
				firstCount++;
				toptmp = toptmp -> after;
			}
			toptmp -> before -> after = NULL;
			bottom = toptmp;
			bottom -> before = NULL;
		}
	}
}

Node* Shuffle(Node* top,Node* bottom, std::string shuffletype){
	Node* Head = top;
	Node* Tmp = top;
	Node* prev = NULL;
	Node* nextTop = top;
	Node* nextBot = bottom;
	while (Tmp != NULL) {
		Tmp->before = prev;
		nextTop = Tmp->after;
		Tmp->after = nextBot;
		prev = Tmp;
		Tmp = Tmp -> after; 
		Tmp -> before = prev;
		nextBot = Tmp->after;
		Tmp -> after = nextTop;
		prev = Tmp;
		Tmp = Tmp->after;
	}
	return Head;
}

bool SamePrimaryOrder(Node* deck1, Node* deck2){
	//if sizes are different, they don't have the same primary order.
	if (DeckSize(deck1) != DeckSize(deck2)) {
		return false;
	}
	Node* d1tmp = deck1;
	Node* d2tmp = deck2;
	//if both lists are empty, they have the same primary order
	if (d1tmp == NULL) {
		return true;
	}
	//return false if any element in list is not equal to corresponding element in other list
	while (d2tmp -> after != NULL) {
		if (d1tmp->getCard() != d2tmp->getCard()) {
			return false;
		}
		d1tmp = d1tmp->after;
		d2tmp = d2tmp->after;
	}
	//checks if last elements arent equal
	if (d1tmp->getCard() != d2tmp->getCard()) {
		return false;
	}
	//all were equal, return true;
	return true;
}

bool ReversePrimaryOrder(Node* deck1, Node* deck2){
	//if sizes are different, they don't have the reverse primary order.
	if (DeckSize(deck1) != DeckSize(deck2)) {
		return false;
	}
	Node* d1tmp = deck1;
	Node* d2tmp = deck2;
	//if both lists are empty, they have reverse primary order
	if (d1tmp == NULL) {
		return true;
	}
	
	while (d2tmp->after != NULL) {
		d2tmp = d2tmp -> after;
	}
	
	while (d1tmp -> after != NULL) {
		if (d1tmp -> getCard() != d2tmp -> getCard()) {
			return false;
		}
		d1tmp = d1tmp -> after;
		d2tmp = d2tmp -> before; 
	}
	if (d1tmp->getCard() != d2tmp->getCard()) {
		return false;
	}
	return true;
}

void DeleteAllCards(Node* deck) {
  Node* curr = deck;
  while (curr != NULL) {
	Node* p = curr;
	curr = curr->after;
	delete p;
	}
}

void Deal(Node*& deck, Node** hands, int size, std::string type, int cards_per_player){
	Node* deckTmp = deck;
	Node* prev;
	for (int i = 0; i<size; i++) {
		hands[i] = NULL;
	}
	for (int i = 0; i < cards_per_player; i++) {
		for (int n = 0; n<size; n++) {
			if (hands[n] == NULL) {
				hands[n] = deckTmp;
				hands[n] -> before = NULL;
				deckTmp = deckTmp -> after;
				deck = deckTmp;
				hands[n] -> after = NULL;
			}
			else {
				Node* lastCard = hands[n];
				while (lastCard->after != NULL) {
					lastCard = lastCard->after;
				}
				deckTmp -> before = lastCard;
				deckTmp -> before -> after = deckTmp;
				prev = deckTmp;
				deckTmp = deckTmp -> after;
				deck = deckTmp;
				prev -> after = NULL;
			}
		}		
	}
	if (deck != NULL) {
		deck -> before = NULL;
	}
}

Node* SortHand(Node*& deck) {
	//Node* deck = CopyDeck(deck1);
	Node* sortedHead = deck;
	Node* tmpCurr = deck;
	Node* tmpBackward = tmpCurr;
	Node* sortedTail = deck;
	while (tmpCurr -> after != NULL) {	
		//first element being added
		if (tmpCurr -> before == NULL) {
			tmpCurr -> sorted_prev = NULL;
			tmpCurr -> sorted_next = NULL;
			sortedHead = tmpCurr;
			sortedTail = tmpCurr;
		}
		tmpCurr = tmpCurr -> after;
		tmpBackward = tmpCurr;
		//make backwards go to value that will be after in sorted order of current value
		while ((tmpBackward -> before != NULL) && (tmpCurr->getCard() < (tmpBackward->before)->getCard())) {
			tmpBackward = tmpBackward -> before;
		}
		//if current value isn't supposed to be before anything previously on list
		if (tmpBackward == tmpCurr){
			tmpCurr -> sorted_prev = sortedTail;
			tmpCurr -> sorted_next = NULL;
			tmpCurr -> sorted_prev -> sorted_next = tmpCurr;
			sortedTail = tmpCurr;
		}
		//if we must insert in beginning of list
		else if (tmpBackward -> before == NULL && tmpBackward -> sorted_prev == NULL) {
			tmpCurr -> sorted_next = tmpBackward;
			tmpCurr -> sorted_prev = NULL;
			tmpCurr -> sorted_next -> sorted_prev = tmpCurr;
			sortedHead = tmpCurr;
		}
		//if we must insert somewhere in the middle
		else {
			tmpCurr -> sorted_next = tmpBackward;
			tmpCurr -> sorted_prev = tmpBackward->sorted_prev;
			tmpBackward -> sorted_prev -> sorted_next = tmpCurr;
			tmpBackward -> sorted_prev = tmpCurr;
		}
	}
	return sortedHead;
}

void PrintDeckSorted(const std::string &description, Node* deck) {
  std::cout << description;
  Node *tmp = deck;
  while (tmp != NULL) {
    std::cout << " " << tmp->getCard().getString();
    tmp = tmp->sorted_next;
  }
  std::cout << std::endl;
}



