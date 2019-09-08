#include <cassert>
#include <iostream>

#include "board.h"


// CONSTRUCTOR
Board::Board(int w, int h) {
  height_ = h;
  width_ = w;
  board = std::vector<std::vector<char> >(h,std::vector<char>(w,' '));
}

// ACCESSOR
char Board::get(int y, int x) const { 
  assert (y >= 0 && board.size());
  assert (x >= 0 && board[y].size());
  return board[y][x]; 
}

// helper function for set
char IntToChar(int v) {
  assert (v >= 1 && v <= 30);
  if (v <= 9) {
    return char('0' + v);
  } else {
    // A = 10
    // B = 11
    // C = 12
    // etc
    return char('A' + (v-10));
  }
}

// MODIFIER
void Board::set(int x, int y, int v) {
  assert (x < width_);
  assert (y < height_);
  //assert(board[y][x] == ' ');
  board[y][x] = IntToChar(v);
}

void Board::empty(int x, int y) {
	board[y][x] = ' ';
}

void Board::paint(int x, int y) {
	board[y][x] = 'X';
}

void Board::addPath(std::vector<Point2D> path) {
	paths_.push_back(path);
}

void Board::removePath(std::vector<Point2D> path) {
	for (unsigned int i = 0; i < paths_.size(); i++) {
		bool equal1 = true;
		if (paths_[i].size() == path.size()) {
			for (unsigned int j = 0; j<path.size(); j++) {
				if ((paths_[i][j].x() != path[j].x()) || (paths_[i][j].y() != path[j].y())) {
					equal1 = false;
				}
			}
			if (equal1 == true) {
				paths_.erase(paths_.begin() + i);
			}
		}
	}
}

bool Board::solved() {
	bool sbool = true;
	for (int x = 0; x < width_; x++) {
		for (int y = 0; y < height_; y++) {
			if (board[y][x] != ' ' && board[y][x] != 'X') {
				sbool = false;
			}
		}
	}
	return sbool;
}

void Board::printPaths() {
	for (unsigned int i = 0; i < paths_.size(); i++) {
		for (unsigned int j = 0; j < paths_[i].size(); j++) {
			std::cout << "(" << paths_[i][j].x() << ", " << paths_[i][j].y() << ") "; 
		}
		std::cout << std::endl;
	}
}
 
// PRINT FUNCTION
std::ostream& operator<<(std::ostream& ostr, const Board &b) {
  // top frame
  ostr << "+" << std::string(b.width(),'-') << "+" << std::endl;
  for (int y = b.height()-1; y >= 0; y--) {
    ostr << "|";
    // each row
    for (int x = 0; x < b.width(); x++) {
      ostr << b.get(y,x);
    }
    ostr << "|" << std::endl;
  }
  // bottom frame
  ostr << "+" << std::string(b.width(),'-') << "+" << std::endl;
  return ostr;
}
