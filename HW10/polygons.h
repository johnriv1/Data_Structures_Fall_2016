#include "utilities.h"
#include <vector>


class Polygon {
public:

	Polygon(const std::string &inname, const std::vector<Point> &points);
	virtual ~Polygon() {}
	
	const std::string getName() { return name; }
	
	virtual bool HasAllEqualSides() {return false;}
	virtual bool HasAllEqualAngles() {return false;}
	virtual bool HasARightAngle() {return false;}
	virtual bool HasAnObtuseAngle() {return false;}
	virtual bool HasAnAcuteAngle() {return false;}
	virtual bool IsConvex() {return false;}
	virtual bool IsConcave() {return false;}
	
protected:

	std::string name;
	std::vector<Point> vertices;

};



//TRIANGLES------------------------------------------------------------------------------------------------------------------------------



class Triangle : public Polygon {
public:

	Triangle(const std::string &inname, const std::vector<Point> &points);
	
	//getName() { return name; }
	
	virtual bool HasAllEqualSides();
	virtual bool HasAllEqualAngles();
	virtual bool HasARightAngle();
	virtual bool HasAnObtuseAngle();
	virtual bool HasAnAcuteAngle();
	virtual bool IsConvex();
	virtual bool IsConcave();
	
};

class RightTriangle : virtual public Triangle {
public:

	RightTriangle(const std::string &inname, const std::vector<Point> &points);

	bool HasARightAngle() { return true; }
};

class IsoscelesTriangle : virtual public Triangle {
public:

	IsoscelesTriangle(const std::string &inname, const std::vector<Point> &points);
	
};

class ObtuseTriangle : virtual public Triangle {
public:

	ObtuseTriangle(const std::string &inname, const std::vector<Point> &points);

	bool HasAnObtuseAngle() { return true; }
};

class IsoscelesRightTriangle : public RightTriangle, public IsoscelesTriangle {
public:

	IsoscelesRightTriangle(const std::string &inname, const std::vector<Point> &points);
	
};

class EquilateralTriangle : public IsoscelesTriangle {
public:

	EquilateralTriangle(const std::string &inname, const std::vector<Point> &points);

	bool HasAllEqualSides() { return true; }
	
};

class IsoscelesObtuseTriangle : public IsoscelesTriangle, public ObtuseTriangle {
public:

	IsoscelesObtuseTriangle(const std::string &inname, const std::vector<Point> &points);
	
	//const std::string getName();

};



//QUADRILATERALS-------------------------------------------------------------------------------------------------------------------------



class Quadrilateral : public Polygon {
public:

	Quadrilateral(const std::string &inname, const std::vector<Point> &points);
	
	bool IsIsosceles();
	virtual bool HasAllEqualSides(); 
	virtual bool HasAllEqualAngles();
	virtual bool HasARightAngle();
	virtual bool HasAnObtuseAngle();
	virtual bool HasAnAcuteAngle();
	virtual bool IsConvex();
	virtual bool IsConcave();

};

class Arrow : public Quadrilateral {
public:

	Arrow(const std::string &inname, const std::vector<Point> &points);

	bool IsConcave() { return true; }
};

class Kite : virtual public Quadrilateral {
public:

	Kite(const std::string &inname, const std::vector<Point> &points);
	
	//bool HasARightAngle() { return true; }
	
};

class Trapezoid : virtual public Quadrilateral {
public:

	Trapezoid(const std::string &inname, const std::vector<Point> &points);
	
};
//**
class Parallelogram : virtual public Trapezoid {
public:

	Parallelogram(const std::string &inname, const std::vector<Point> &points);
	
};

class IsoscelesTrapezoid : virtual public Trapezoid {
public:

	IsoscelesTrapezoid(const std::string &inname, const std::vector<Point> &points);
	
};

class Rhombus : virtual public Parallelogram, public Kite {
public:

	Rhombus(const std::string &inname, const std::vector<Point> &points);
	
};

class Rectangle : virtual public Parallelogram, public IsoscelesTrapezoid {
public:

	Rectangle(const std::string &inname, const std::vector<Point> &points);
	
};

class Square : public Rhombus, public Rectangle {
public:

	Square(const std::string &inname, const std::vector<Point> &points);
	
	bool HasAllEqualSides() { return true; }
	
};
