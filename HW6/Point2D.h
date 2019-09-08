#ifndef Point2D_h_
#define Point2D_h_

class Point2D {

public:
  // constructors
  Point2D() : m_x(0), m_y(0) {}
  Point2D( int x, int y) 
    : m_x(x), m_y(y) {}

  // accessors
  int x() const { return m_x; }
  int y() const { return m_y; }

  // modifier
  int set( int x, int y )
    { m_x = x; m_y = y; }

private:
  // representation
  int m_x, m_y;
};

#endif