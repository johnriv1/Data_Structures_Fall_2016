#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#include "board.h"


//will give all coordinate paths in form of strings in vector
(int x, int y, int x_initial, int y_initial, Board& board, std::string final_string,  int count, char val, int width, int  height) { 
	//if stroke is successfully completed
	if (board.get(x, y) == value && count == (int) atof(value)) {
		
		//reset count for next stroke call
		count = 0;
		string tmp= "(" + to_string(x) + "," + to_string(y) + ") ";
		final_string += tmp;
		board.addpath(final_string);
		
		if (!board.solved()) {
			for (int j = 0; j < height, j++) {
				for (int i = 0; i < width; i++) {
					if (board.get(i, j) != 'X' && board.get(i, j) != ' ') {
						Stoke(i, j, i, j, board, final_string, count, value, width, height);
					}
				}
			}
		}
		Stroke()
		return 1;
	}
	//set value it is currently on to 'X'
	board.set(x, y, 'X');
	//if its correct count is reached the value it is currently on is not the right value, then return 0
	//or, if it has crashed into another number, return 0
	//or, if path tries to go through itself or through another stroke, return 0
	else if (((count == (int) atof(value)) && (board.get(x, y) != value)) || ((board.get(x, y) != value) && (board.get(x, y) != ' ')) || (board.get(x, y) == 'X') {
		return 0;
	}
	else if (x==0 && y!=0 && y != (height-1) {
		string tmp= "(" + to_string(x) + "," + to_string(y) + ") ";
		final_string += tmp;
		count += 1;
		return Stroke(x, y-1,blocked_grid, final_string);
		return Stroke(x, y+1,blocked_grid, final_string);
		return Stroke(x+1, y,blocked_grid, final_string);
	}
	else if (x==0 && y == (height-1) {
		string tmp = "(" + to_string(x) + "," + to_string(y) + ") ";
		final_string += tmp;
		count += 1;
		return Stroke(x, y-1,blocked_grid, final_string) 
		return Stroke(x+1, y,blocked_grid, final_string);
	}
	else if (y==0 && x!=0 && x!=(width-1)) {
		string tmp = "(" + to_string(x) + "," + to_string(y) + ") ";
		final_string += tmp;
		count += 1;
		return Stroke(x-1, y,blocked_grid, final_string); 
		return Stroke(x+1,blocked_grid, final_string);
		return Stroke(x, y+1,blocked_grid, final_string);
	}
	else if (y==0 && x==(width-1)) {
		string tmp = "(" + to_string(x) + "," + to_string(y) + ") ";
		final_string += tmp;
		count += 1;
		return Stroke(x-1, y,blocked_grid, final_string); 
		return Stroke(x, y+1,blocked_grid, final_string);
	}
	else if (y==0 && x==0) {
		string tmp = "(" + to_string(x) + "," + to_string(y) + ") ";
		final_string += tmp;
		count += 1;
		return Stroke(x+1, y,blocked_grid, final_string); 
		return Stroke(x, y+1,blocked_grid, final_string);
	}
	else {
		count += 1;
		return Stroke(x, y-1,blocked_grid, final_string); 
		return Stroke(x, y+1,blocked_grid, final_string);
		return Stroke(x+1, y,blocked_grid, final_string); 
		return Stroke(x-1, y,blocked_grid, final_string);
	}
	final_string += "(" + to_string(x) + "," + to_string(y) + ") ";
}

//will initially hold single initial board
void boardsMaker(allboards) {
	for (int i = 0; i<allboards.size(); i++) {
		if (x < boards[i].width)
			stroke(x, y)
		boardsMaker
	}
}



int main(int argc, char* argv[]) {

  // parse the arguments
  if (argc < 2) {
    std::cerr << "USAGE:  " << argv[0] << " <puzzlefile>" << std::endl;
    std::cerr << "        " << argv[0] << " <puzzlefile> find_all_solutions" << std::endl;
    exit(0);
  }
  bool all_solutions = false;
  if (argc > 2) {
    assert (argc == 3);
    assert (std::string(argv[2]) == std::string("find_all_solutions"));
    all_solutions = true;
  }

  // open the file
  std::ifstream istr(argv[1]);
  if (!istr.good()) {
    std::cerr << "ERROR!  cannot open " << argv[1] << std::endl;
    exit(0);
  }

  // read the file
  std::string token;
  istr >> token;
  assert (token == "width");
  int width,height;
  istr >> width;
  istr >> token;
  assert (token == "height");
  istr >> height;
  assert (width > 0);
  assert (height > 0);
  int x,y,v;

  // create the board
  Board board(width,height);
  while (istr >> x >> y >> v) {
    assert (x >= 0 && x < width);
    assert (y >= 0 && y < height);
    board.set(x,y,v);
  }

  // print the original puzzle board
  std::cout << board;

  // Now...  solve it!
  for (unsigned int )
  }

}



