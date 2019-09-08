#include "Rectangle.h"
#include "Point2D.h"
#include <iostream>

int main() {
	
	Point2D pt(3,5);
	
	//initialize first rectangle
	Point2D x1(1,1);
	Point2D y1(5,5);
	Rectangle r1(x1,y1);
	print_rectangle(r1);  //Rectangle.cpp print_rectangle prints lower left corner.y() twice //
	
	//initialize second rectangle
	Point2D x2(3,3);
	Point2D y2(6,6);
	Rectangle r2(x2,y2);
	print_rectangle(r2);  //Rectangle.cpp print_rectangle prints lower left corner.y() twice //

	//points to add
	//t1 should only be added to r1
	//t2 should be added to both
	//t3 should only be added to r2
	Point2D t1(2,2);
	Point2D t2(4,4);
	Point2D t3(5,6);

	//attempt to add points to r1
	std::cout << "is t1 in r1: " << r1.is_point_within(t1) << std::endl;
	std::cout << "is t2 in r1: " << r1.is_point_within(t2) << std::endl;
	std::cout << "is t3 in r1: " << r1.is_point_within(t3) << std::endl; //should return 0 but it doesn't, but it is still not added to rectangle, // 
	r1.add_point(t1);                                                    //which means problem is in only the is_point_within function. || should be &&. //
	r1.add_point(t2);
	r1.add_point(t3);
	
	//print new contents of r1
	print_rectangle(r1);
	
	//attempt to add points to r2
	std::cout << "is t1 in r2: " << r2.is_point_within(t1) << std::endl;
	std::cout << "is t2 in r2: " << r2.is_point_within(t2) << std::endl;
	std::cout << "is t3 in r2: " << r2.is_point_within(t3) << std::endl;
	r2.add_point(t1);
	r2.add_point(t2);
	r2.add_point(t3);
	
	pt.set(4,2);

	//print new contents of r2
	print_rectangle(r2);
	
	//print what is in both
	std::vector<Point2D> common = points_in_both(r1, r2);
	std::cout << "Points in common:" << std::endl;
	for (unsigned int i = 0; i < common.size(); i++) {
		std::cout << "(" << common[i].x() <<", " << common[i].y() << ")" << std::endl;
	}
		
}