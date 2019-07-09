/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
  and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, math, and strings
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

#include "Rect.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
  //Initialization mouseClicked
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
      printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
  else
    {
      //Set texture filtering to linear
      if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
	  printf( "Warning: Linear texture filtering not enabled!" );
	}

      //Create window
      gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
	{
	  printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	  success = false;
	}
      else
	{
	  //Create renderer for window
	  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	  if( gRenderer == NULL )
	    {
	      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	      success = false;
	    }
	  else
	    {
	      //Initialize renderer color
	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	      //Initialize PNG loading
	      int imgFlags = IMG_INIT_PNG;
	      if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
		  printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		  success = false;
		}
	    }
	}
    }

  return success;
}

bool loadMedia()
{
  //Loading success mouseClicked
  bool success = true;

  //Nothing to load
  return success;
}

void close()
{
  //Destroy window
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
  //The final texture
  SDL_Texture* newTexture = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface == NULL )
    {
      printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
  else
    {
      //Create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
      if( newTexture == NULL )
	{
	  printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

      //Get rid of old loaded surface
      SDL_FreeSurface( loadedSurface );
    }

  return newTexture;
}

int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if( !init() )
    {
      printf( "Failed to initialize!\n" );
    }
  else
    {

      if( !loadMedia() )  //Load media
	{
	  printf( "Failed to load media!\n" );
	}
      else
	{
	  bool quit = false;  //Main loop controller

	  SDL_Event e;        //Event handler that takes care of all events
	  
	  bool mouseClicked = false;
	  SDL_Rect fillRect;
	  int oldx = 0;
	  int oldy = 0;
	  
	  Rect* rect = NULL;

	  //While application is running
	  while( !quit )
	    {
	      //Handle events on queue
	      while( SDL_PollEvent( &e ) != 0 )
		{
		  //User requests quit
		  if( e.type == SDL_QUIT )
		    {
		      quit = true;
		    }
		  
		  if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                    {
		      //Get mouse position
		      int x, y;
		      SDL_GetMouseState( &x, &y );
		      
		      if(e.type ==  SDL_MOUSEMOTION)
                        {
			  if(mouseClicked == true)
			    fillRect = { oldx , oldy , x - oldx, y - oldy };
                        }
		      
		      if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
			  if(mouseClicked == false)
                            {
			      mouseClicked = true;
			      oldx = x;
			      oldy = y;
                            }
			  
                        }
		      
		      if(e.type == SDL_MOUSEBUTTONUP)
                        {
			  mouseClicked = false;
			  rect = new Rect(&fillRect);
                        }
		      
                    }
		}
	      //Clear screen

	      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	      SDL_RenderClear( gRenderer );

	      if (rect != NULL)
                {
		  SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
		  rect->draw(gRenderer, &fillRect);
                }

	      //Update screen
	      SDL_RenderPresent( gRenderer );
	    }
	}
    }

  //Free resources and close SDL
  close();

  return 0;
}
