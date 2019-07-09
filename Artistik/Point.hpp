#pragma once

struct Point
{
  int m_x;
  int m_y;
  
  Point() : m_x(0), m_y(0)
  {}
  
  Point(int x, int y) : m_x(x), m_y(y)
  {}
  
  Point(const Point& other) : Point(other.m_x, other.m_y)
  {}
};
