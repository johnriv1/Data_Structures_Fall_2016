#include "playing_card.h"
#include "node.h"

// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================

bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================

int DeckSize(Node* top);
Node* CopyDeck(Node* old_head);
void CutDeck(Node* deck, Node*& top, Node*& bottom, std::string shuffletype);
Node* Shuffle(Node* top,Node* bottom, std::string shuffletype);
bool SamePrimaryOrder(Node* deck1, Node* deck2);
bool ReversePrimaryOrder(Node* deck1, Node* deck2);
void DeleteAllCards(Node* deck);
void Deal(Node*& deck, Node** hands, int size, std::string type, int cards_per_player);
Node* SortHand(Node*& deck);
void PrintDeckSorted(const std::string &description, Node* deck);