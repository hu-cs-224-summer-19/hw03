#include"Rect.hpp"

Rect::Rect(SDL_Rect* rect) : m_fill_rect(rect)
{}

void Rect::draw(SDL_Renderer* gRenderer, SDL_Rect* fillRect)
{
  SDL_RenderFillRect( gRenderer, fillRect );
}

