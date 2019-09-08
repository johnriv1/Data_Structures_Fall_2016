#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <ctime>

#include "board.h"
#include "Point2D.h"


//will give all coordinate paths in form of strings in vector
int Stroke(int x, int y, Board board, std::vector<Point2D> final_path, std::vector<std::vector<Point2D> > &final_paths, int count, char value, int width, int  height) { 

	
	//set value it is currently on to 'X'
	//if its correct count is reached the value it is currently on is not the right value, then return 0
	//or, if it has crashed into another number, return 0
	int val_int;
	if ((value <= '9')) {
		val_int = value - '0';
	}
	else {
		val_int = value - '7';
	}
		
	if (((count == (val_int) && (board.get(y, x) != value)) || ((board.get(y, x) != value) && (board.get(y, x) != ' ')) || ((count != 1 && board.get(y, x) == value && count != (val_int))) )) {
		final_path.clear();
		return 0;
	}
	else if (board.get(y, x) == value && count == (val_int)) {
		final_path.push_back(Point2D(x, y));
		final_paths.push_back(final_path);
		final_path.clear();
		return 1;
	}
	else if (x==0 && y!=0 && y != (height-1)) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		if (width > 1) {
			return Stroke(x, y-1,board, final_path, final_paths, count, value, width, height) + Stroke(x, y+1,board, final_path, final_paths, count, value, width, height)+ Stroke(x+1, y,board, final_path, final_paths, count, value, width, height);
		}
		else if (width == 1) {
			return Stroke(x, y-1,board, final_path, final_paths, count, value, width, height) + Stroke(x, y+1,board, final_path, final_paths, count, value, width, height);
		}
	}
	else if (x==0 && y == (height-1)) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		if (width > 1 && height > 1) {
			return Stroke(x, y-1,board, final_path, final_paths, count, value, width, height) + Stroke(x+1, y,board, final_path, final_paths, count, value, width, height);
		}
		else if (width == 1 && height > 1){
			return Stroke(x, y-1,board, final_path, final_paths, count, value, width, height);			
		}
		else if (width > 1 && height == 1){
			return Stroke(x+1, y,board, final_path, final_paths, count, value, width, height);			
		}
	}
	else if (y==0 && x!=0 && x!=(width-1)) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		if (height > 1) {
			return Stroke(x-1, y, board, final_path, final_paths, count, value, width, height) + Stroke(x+1, y, board, final_path, final_paths, count, value, width, height)+ Stroke(x, y+1,board, final_path, final_paths, count, value, width, height);
		}
		else if (height == 1) {
			return Stroke(x-1, y, board, final_path, final_paths, count, value, width, height) + Stroke(x+1, y, board, final_path, final_paths, count, value, width, height);
		}
	}
	else if (y==0 && x!=0 && x==(width-1)) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		if (height > 1) {
			return Stroke(x-1, y,board, final_path, final_paths, count, value, width, height) + Stroke(x, y+1,board, final_path, final_paths, count, value, width, height);
		}
		else if (height == 1) {
			return Stroke(x-1, y,board, final_path, final_paths, count, value, width, height);
		}
	}
	else if (x==(width-1) && y!=0 && y!=(height-1)) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		return Stroke(x-1, y,board, final_path, final_paths, count, value, width, height) + Stroke(x, y+1,board, final_path, final_paths, count, value, width, height)+ Stroke(x, y-1,board, final_path, final_paths, count, value, width, height);
	}
	else if (x==(width-1) && x!=0 && y==(height-1) && y!=0) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		return Stroke(x-1, y,board, final_path, final_paths, count, value, width, height) + Stroke(x, y-1,board, final_path, final_paths, count, value, width, height);
	}
	else if (y==(height-1) && x!=0 && x!=(width-1)) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		return Stroke(x-1, y,board, final_path, final_paths, count, value, width, height) + Stroke(x+1, y, board, final_path, final_paths, count, value, width, height) + Stroke(x, y-1,board, final_path, final_paths, count, value, width, height);
	}
	else if (y==0 && x==0) {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		if (width > 1 && height > 1) {
			return Stroke(x+1, y,board, final_path, final_paths, count, value, width, height) + Stroke(x, y+1,board, final_path, final_paths, count, value, width, height);
		}
		else if (width > 1 && height == 1) {
			return Stroke(x+1, y,board, final_path, final_paths, count, value, width, height);
		}
		else if (width == 1 && height > 1) {
			return Stroke(x, y+1,board, final_path, final_paths, count, value, width, height);
		}
	}
	else {
		final_path.push_back(Point2D(x, y));
		board.paint(x, y);
		count += 1;
		return Stroke(x, y-1,board, final_path, final_paths, count, value, width, height) + Stroke(x, y+1,board, final_path, final_paths, count, value, width, height)+ Stroke(x+1, y,board, final_path, final_paths, count, value, width, height) + Stroke(x-1, y,board, final_path, final_paths, count, value, width, height);
	}
}

//removes all duplicates in final_paths before it is added to vector of possible paths
void remove_duplicate_Path(std::vector<std::vector<Point2D> > &final_paths, const std::vector<Point2D> &compare_path){
	//are they equal with same ordering
	bool equal1 = true;
	for (unsigned int i = 0; i<final_paths.size(); i++) {
		equal1 = true;
		if (final_paths[i].size() == compare_path.size()) {
			for (unsigned int j = 0; j<final_paths[i].size(); j++) {
				if ((final_paths[i][j].x() != compare_path[j].x()) || (final_paths[i][j].y() != compare_path[j].y())) {
					equal1 = false;
				}
			}
			if (equal1 == true) {
				final_paths.erase(final_paths.begin() + i);
				i--;
			}
		}
	}
	//are they same vectors but with reverse ordering
	bool equalreverse = true;
	for (unsigned int i = 0; i<final_paths.size(); i++) {
		if (final_paths[i].size() == compare_path.size()) {
			int jr;
			unsigned int j;
			equalreverse = true;
			for (j = 0, jr = (compare_path.size()-1); j<final_paths[i].size(); j++, jr--) {
				if ((final_paths[i][j].x() != compare_path[jr].x()) || (final_paths[i][j].y() != compare_path[jr].y())) {
					equalreverse = false;
				}
			}
			if (equalreverse == true) {
				final_paths.erase(final_paths.begin() + i);
				i--;
			}
		}
	}
}

//collects all possible paths of every coordinate with a number into a vector
std::vector<std::vector<std::vector<Point2D> > > collectPaths(const Board& board) {
	std::vector<Point2D> final_path;
	std::vector<std::vector<Point2D> > final_paths;
	std::vector<std::vector<std::vector<Point2D> > > all_final_paths;
	for (int x = 0; x < board.width(); x++) {
		for (int y = 0; y < board.height(); y++) {
			char value = board.get(y, x);
			if (value != ' ') {
				int count = 1;
				int numsolutions = Stroke(x, y, board, final_path, final_paths, count, value, board.width(), board.height());
				//if any path in final_paths is equal (normal or reverse) to any path in in final_collected_paths, popback path from final_paths. Prevents duplicate paths.
				for (unsigned int i = 0; i < all_final_paths.size(); i++) {
					for (int j = 0; j < all_final_paths[i].size(); j++) {
						remove_duplicate_Path(final_paths, all_final_paths[i][j]);
					}
				}
				if (final_paths.size() > 0) {
					all_final_paths.push_back(final_paths);
					final_paths.clear();
				}
			}
		}
	}
	return all_final_paths;
}

bool valid_path(std::vector<Point2D> path, Board &board) {
	for (unsigned int i = 0; i< path.size(); i++) {
		if (board.get(path[i].y(), path[i].x()) == 'X' ) {
			return false;
		}
	}
	return true;
}

void Fill_in_stroke(std::vector<Point2D> path, Board &board) {
	for (unsigned int i = 0; i< path.size(); i++) {
		board.paint(path[i].x(), path[i].y());
	}
}

void Undo_stroke(std::vector<Point2D> path, Board &board) {
	board.set(path[0].x(), path[0].y(), path.size());
	if (path.size() > 1) {
		for (unsigned int i = 1; i < path.size(); i++) {
			board.empty(path[i].x(), path[i].y());
		}
		board.set(path[path.size()-1].x(), path[path.size()-1].y(), path.size());
	}
}

//have this function within a for loop to change start value
void find_Solutions(const std::vector<std::vector<std::vector<Point2D> > > &collectedPaths, Board &board, std::vector<Board> &all_solved_boards, unsigned int i, bool all_solutions) {
	if (board.solved()) {
		//add solved board to vector
		all_solved_boards.push_back(board);
	}
	//if we are still inside collectedPaths vector
	else if (i < collectedPaths.size()) {
		//for (int i = 0; i < collectedPaths.size(); i++) {
		for (unsigned int j = 0; j < collectedPaths[i].size(); j++) {
			if (valid_path(collectedPaths[i][j], board)) {
				//paint according to current path
				Fill_in_stroke(collectedPaths[i][j], board);
				//add path to board object
				board.addPath(collectedPaths[i][j]);
				find_Solutions(collectedPaths, board, all_solved_boards, i+1, all_solutions);
				if (all_solutions == true) {
					board.removePath(collectedPaths[i][j]);
					Undo_stroke(collectedPaths[i][j], board);
				}
			}
		}
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

  //std::clock_t start;
  //start = std::clock();
	
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
  std::cout << board << std::endl;

  // Now...  solve it!

  std::vector<std::vector<std::vector<Point2D> > > collectedPaths = collectPaths(board);
	std::vector<Board> all_solved_boards;
	for (unsigned int i = 0; i < collectedPaths[0].size(); i++) {
		find_Solutions(collectedPaths, board, all_solved_boards, i, all_solutions);
	}
	for (unsigned int i = 0; i<all_solved_boards.size(); i++) {
		std::cout << "Solution:" << std::endl;
		all_solved_boards[i].printPaths();
		std::cout << all_solved_boards[i] << std::endl;
	}
	
	if (all_solutions == true) {
		std::cout << "Found " << all_solved_boards.size() << " solution(s)" << std::endl;
	}
	
	//std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}



