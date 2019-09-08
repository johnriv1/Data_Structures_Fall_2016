#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>
#include "Point2D.h"

class Board {
public:
  // CONSTRUCTOR
  Board(int w, int h);
  // ACCESSORS
  int width() const { return width_; }
  int height() const { return height_; }
  char get(int y, int x) const;
  //void printPaths() const;
  // MODIFIER
  void set(int x, int y, int v);
  void addPath(std::vector<Point2D> path);
  
  //OTHER
  bool solved();
  void paint(int x, int y);
  void empty(int x, int y);
  void removePath(std::vector<Point2D> path);
  void printPaths();
  
private:
  // REPRESENTATION
  int height_;
  int width_;
  std::vector<std::vector<char> > board;
  //each index of vector will be a string of the path it took in coordinates
  std::vector<std::vector<Point2D> > paths_;
};

// PRINT FUNCTION
std::ostream& operator<<(std::ostream& ostr, const Board &b);

#endif
