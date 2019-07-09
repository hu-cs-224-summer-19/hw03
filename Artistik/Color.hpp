#pragma once

struct Color
{
  int m_red;
  int m_green;
  int m_blue;
  
  Color() : m_red(255), m_green(255), m_blue(255)
  {}

  Color(int r, int g, int b) : m_red(r), m_green(g), m_blue(b)
  {}
};
