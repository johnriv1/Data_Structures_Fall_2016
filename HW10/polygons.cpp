#include "polygons.h"


Polygon::Polygon(const std::string &inname, const std::vector<Point> &points) {
	name = inname;
	vertices = points;
	//std::cout << &inname << std::endl;
	std::cout << "Polygon: : " << inname << std::endl;
}



//TRIANGLES------------------------------------------------------------------------------------------------------------------------------



Triangle::Triangle(const std::string &inname, const std::vector<Point> &points): Polygon(name, points) {
	if (points.size() != 3) {
		throw 1;
	}	
	std::cout << "Triangle: : " << inname << std::endl;

}

bool Triangle::HasAllEqualSides() {
	
	int i = (EqualSides(DistanceBetween(vertices[0], vertices[1]), DistanceBetween(vertices[1], vertices[2])) &&  
			EqualSides(DistanceBetween(vertices[1], vertices[2]), DistanceBetween(vertices[2], vertices[0])) &&
			EqualSides(DistanceBetween(vertices[2], vertices[0]), DistanceBetween(vertices[0], vertices[1])));
	return (i);
}

bool Triangle::HasAllEqualAngles() {
	return (EqualAngles(Angle(vertices[0], vertices[1], vertices[2]) , Angle(vertices[1], vertices[2], vertices[0])) &&
			EqualAngles(Angle(vertices[1], vertices[2], vertices[0]) , Angle(vertices[2], vertices[0], vertices[1])));
}

bool Triangle::HasARightAngle() {
	return (RightAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			RightAngle(Angle(vertices[1], vertices[2], vertices[0])) ||
			RightAngle(Angle(vertices[2], vertices[0], vertices[1])));
}

bool Triangle::HasAnObtuseAngle() {
	return (ObtuseAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			ObtuseAngle(Angle(vertices[1], vertices[2], vertices[0])) ||
			ObtuseAngle(Angle(vertices[2], vertices[0], vertices[1])));		
}

bool Triangle::HasAnAcuteAngle() {
	return (AcuteAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			AcuteAngle(Angle(vertices[1], vertices[2], vertices[0])) ||
			AcuteAngle(Angle(vertices[2], vertices[0], vertices[1])));
}

bool Triangle::IsConcave() {
	return false;
}
/*
	return (ReflexAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			ReflexAngle(Angle(vertices[1], vertices[2], vertices[0])) ||
			ReflexAngle(Angle(vertices[2], vertices[0], vertices[1])));
*/
bool Triangle::IsConvex() {
	return true;
}

RightTriangle::RightTriangle(const std::string &inname, const std::vector<Point> &points): Triangle(name, points) {
	if (!Triangle::HasARightAngle()) {
		throw 1;
	}
	//	std::cout << inname << std::endl;

}
//At least two sides with equal length
IsoscelesTriangle::IsoscelesTriangle(const std::string &inname, const std::vector<Point> &points):Triangle(name, points) {
	//if not equilateral
	if (!Triangle::HasAllEqualSides()) {
		//if no two sides are equal
		if (!(EqualSides(DistanceBetween(vertices[0], vertices[1]), DistanceBetween(vertices[1], vertices[2])) ||  
			EqualSides(DistanceBetween(vertices[1], vertices[2]), DistanceBetween(vertices[2], vertices[0])) ||
			EqualSides(DistanceBetween(vertices[2], vertices[0]), DistanceBetween(vertices[0], vertices[1])))) {
			
			throw 1;
		}
	}
	//	std::cout << inname << std::endl;

}

ObtuseTriangle::ObtuseTriangle(const std::string &inname, const std::vector<Point> &points) : Triangle(name, points) {
	if (!Triangle::HasAnObtuseAngle()) {
		throw 1;
	}
		//std::cout << inname << std::endl;

}

//Don't need a throw statement because the calls to both parents will decide whether its an Isoceles Right Triangle?
IsoscelesRightTriangle::IsoscelesRightTriangle(const std::string &inname, const std::vector<Point> &points) : Triangle(name, points), RightTriangle(name, points), IsoscelesTriangle(name, points) {
	//std::cout << inname << std::endl;
	//std::cout << name << std::endl;
}

EquilateralTriangle::EquilateralTriangle(const std::string &inname, const std::vector<Point> &points) : Triangle(name, points), IsoscelesTriangle(name, points) {
	if (!Triangle::HasAllEqualSides()) {
		throw 1;
	}
	std::cout << "Polygon: : " << inname << std::endl;
	//std::cout << name << std::endl;
}

//Don't need a throw statement because the calls to both parents will decide whether its an Isosceles Obtuse Triangle?
IsoscelesObtuseTriangle::IsoscelesObtuseTriangle(const std::string &inname, const std::vector<Point> &points) : Triangle(name, points), IsoscelesTriangle(name, points), ObtuseTriangle(name, points) {
	//std::cout << inname << std::endl;
}



//QUADRILATERALS-------------------------------------------------------------------------------------------------------------------------



Quadrilateral::Quadrilateral(const std::string &inname, const std::vector<Point> &points) : Polygon(name, points) {
	if (points.size() != 4) {
		throw 1;
	}
}

bool Quadrilateral::IsIsosceles() {
	return (EqualSides(DistanceBetween(vertices[0], vertices[1]), DistanceBetween(vertices[1], vertices[2])) ||  
		EqualSides(DistanceBetween(vertices[1], vertices[2]), DistanceBetween(vertices[2], vertices[3])) ||
		EqualSides(DistanceBetween(vertices[2], vertices[3]), DistanceBetween(vertices[3], vertices[0])) ||
		EqualSides(DistanceBetween(vertices[3], vertices[0]), DistanceBetween(vertices[0], vertices[1])));
}

bool Quadrilateral::HasAllEqualSides() {
	return (EqualSides(DistanceBetween(vertices[0], vertices[1]), DistanceBetween(vertices[1], vertices[2])) &&  
			EqualSides(DistanceBetween(vertices[1], vertices[2]), DistanceBetween(vertices[2], vertices[3])) &&
			EqualSides(DistanceBetween(vertices[2], vertices[3]), DistanceBetween(vertices[3], vertices[0])) &&
			EqualSides(DistanceBetween(vertices[3], vertices[0]), DistanceBetween(vertices[0], vertices[1])));
}

bool Quadrilateral::HasAllEqualAngles() {
	return (EqualAngles(Angle(vertices[0], vertices[1], vertices[2]) , Angle(vertices[1], vertices[2], vertices[3])) &&
			EqualAngles(Angle(vertices[1], vertices[2], vertices[3]) , Angle(vertices[2], vertices[3], vertices[0])) && 
			EqualAngles(Angle(vertices[2], vertices[3], vertices[0]) , Angle(vertices[3], vertices[0], vertices[1])));
}

bool Quadrilateral::HasARightAngle() {
	return (RightAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			RightAngle(Angle(vertices[1], vertices[2], vertices[3])) ||
			RightAngle(Angle(vertices[2], vertices[3], vertices[0])) ||
			RightAngle(Angle(vertices[3], vertices[0], vertices[1])));
}

bool Quadrilateral::HasAnObtuseAngle() {
	return (ObtuseAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			ObtuseAngle(Angle(vertices[1], vertices[2], vertices[3])) ||
			ObtuseAngle(Angle(vertices[2], vertices[3], vertices[0])) ||
			ObtuseAngle(Angle(vertices[3], vertices[0], vertices[1])));		
}

bool Quadrilateral::HasAnAcuteAngle() {
	return (AcuteAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			AcuteAngle(Angle(vertices[1], vertices[2], vertices[3])) ||
			AcuteAngle(Angle(vertices[2], vertices[3], vertices[0])) ||
			AcuteAngle(Angle(vertices[3], vertices[0], vertices[1])));	
}

bool Quadrilateral::IsConcave() {
	return (ReflexAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			ReflexAngle(Angle(vertices[1], vertices[2], vertices[3])) ||
			ReflexAngle(Angle(vertices[2], vertices[3], vertices[0])) ||
			ReflexAngle(Angle(vertices[3], vertices[0], vertices[1])));	
}

bool Quadrilateral::IsConvex() {
	return (!(ReflexAngle(Angle(vertices[0], vertices[1], vertices[2])) || 
			ReflexAngle(Angle(vertices[1], vertices[2], vertices[3])) ||
			ReflexAngle(Angle(vertices[2], vertices[3], vertices[0])) ||
			ReflexAngle(Angle(vertices[3], vertices[0], vertices[1]))));	
}
//Arrows must be concave and isosceles
Arrow::Arrow(const std::string &inname, const std::vector<Point> &points) : Quadrilateral(name, points) {
	if (!Quadrilateral::IsConcave()) {
		throw 1;
	}
	if (!IsIsosceles()) {
		throw 1;
	}
}
//must be at least isosceles, diagonals bisect each other perpendicularly
Kite::Kite(const std::string &inname, const std::vector<Point> &points) : Quadrilateral(name, points) {
	/*if (!Quadrilateral::HasARightAngle()) {
		throw 1;
	}
	*/
	if (!IsIsosceles()) {
		throw 1;
	}
	
	
}
//At least 2 sides are parallel
Trapezoid::Trapezoid(const std::string &inname, const std::vector<Point> &points) : Quadrilateral(name, points) {
	Vector V1(points[0], points[1]);
	Vector V2(points[1], points[2]);
	Vector V3(points[2], points[3]);
	Vector V4(points[3], points[0]);
	if (!(Parallel(V1, V3) || Parallel(V2, V4))) {
		throw 1;
	}
}
//Must have 2 pairs of parallel sides
Parallelogram::Parallelogram(const std::string &inname, const std::vector<Point> &points) : Quadrilateral(name, points), Trapezoid(name, points) {
	Vector V1(points[0], points[1]);
	Vector V2(points[1], points[2]);
	Vector V3(points[2], points[3]);
	Vector V4(points[3], points[0]);
	if (!(Parallel(V1, V3) && Parallel(V2, V4))) {
		throw 1;
	}
}
//Must also be isosceles
IsoscelesTrapezoid::IsoscelesTrapezoid(const std::string &inname, const std::vector<Point> &points): Quadrilateral(name, points), Trapezoid(name, points) {
	if (!(IsIsosceles())) {
		throw 1;
	}
}
//diagonals must bisect the angles
Rhombus::Rhombus(const std::string &inname, const std::vector<Point> &points): Quadrilateral(name, points), Trapezoid(name, points), Kite(name, points), Parallelogram(name, points) {
	
}
Rectangle::Rectangle(const std::string &inname, const std::vector<Point> &points) : Quadrilateral(name, points), Trapezoid(name, points), Parallelogram(name, points), IsoscelesTrapezoid(name, points){
	if (!Quadrilateral::HasAllEqualAngles()) {
		throw 1;
	}
}

Square::Square(const std::string &inname, const std::vector<Point> &points) : Quadrilateral(name, points), Trapezoid(name, points), Parallelogram(name, points), Rhombus(name, points), Rectangle(name, points) {
	if (!Quadrilateral::HasAllEqualSides()) {
		throw 1;
	}
}



















