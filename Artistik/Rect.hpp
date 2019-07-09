#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Point.hpp"

class Rect
{
private:
  SDL_Rect* m_fill_rect;
  //Color m_color;
  Point m_top_left;
  Point m_bottom_right;
  
public:
  Rect(SDL_Rect*);
  //Rect(const Point& topLeft, const Point& bottomRight, const Color&);

  // Draw the rectangle.
  void draw(SDL_Renderer*, SDL_Rect*);
};

