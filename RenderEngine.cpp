#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#include "SDL/SDL_ttf.h"
#include "RenderEngine.h"

using namespace std;

/**
* Singleton intializer and accessor
*/
RenderEngine* RenderEngine::pinstance = NULL;
RenderEngine* RenderEngine::Instance()
{
    //Create new instance if first call
    if (pinstance == NULL)
    {
        pinstance = new RenderEngine;
    }

    //Return pointer to new instance
    return pinstance;
}

/**
* Constructor
*/
RenderEngine::RenderEngine()
{
    //Initialize class variables
    fullScreen = true;

    //Initialize SDL systems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        cout << "SDL_Init Error\n";
    }

    /*
    if( TTF_Init() == -1 )
    {
        //return false;
        cout << "TTF_Init Error\n";
    }
    */

    //Temporary screen surface
    SDL_Surface *screen = NULL;

    if (fullScreen == false){
        screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT );// | SDL_FULLSCREEN);
    }else{
        screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT | SDL_FULLSCREEN);
    }

    //SDL_SetVideoMode error check
    if( screen == NULL )
    {
        cout << "SDL_SetVideoMode Error\n";
    }

    //Add screen surface to surfaces map
    surfaces["screen"] = screen;

    //Window Title
    SDL_WM_SetCaption( "Breakout - Dan Bechard", NULL );

	//Load Background Image
	back = LoadSurface( "back1.png" );
}

/**
* Destructor
*/
RenderEngine::~RenderEngine()
{
    for( iter = surfaces.begin(); iter != surfaces.end(); iter++ )
    {
        SDL_FreeSurface( iter->second );
    }
    surfaces.clear();

    cout << "Terminating Render Engine\n";
}

/**
* Toggle Full Screen Mode
*/
void RenderEngine::ToggleFullScreen()
{
    if (fullScreen == false){
        SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT | SDL_FULLSCREEN );
    }else{
        SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_ANYFORMAT );
    }

    fullScreen = !fullScreen;
}

/**
* Load surface if not already loaded
*
* @return SDL_Surface
* Requested surface
*/
SDL_Surface *RenderEngine::LoadSurface( std::string filename )
{
    //Search for it in loaded surfaces
    for( iter = surfaces.begin(); iter != surfaces.end(); iter++ )
    {
        //Surface already loaded!
        if( filename == iter->first )
        {
            std::cout << "Existing Surface - Not loaded again (Yay Success!)\n";
            return iter->second;
        }
    }

    //Raw image
    SDL_Surface* loadedImage = NULL;

    //Final image
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    cout << "Loading: " << filename << "\n";
    loadedImage = IMG_Load( filename.c_str() );

    //Image was loaded
    if( loadedImage != NULL )
    {
        //Optimize the image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );

        //Surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface (sets transparent color)
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF ) );
        }
    //IMG_Load error
    }else{
        cout << "loadedImage is NULL\n";
        return NULL;
    }

    //Add optimized surface to surfaces map
    surfaces[filename] = optimizedImage;

    //Return surface
    return optimizedImage;
}

/**
* Free surface
*/
void RenderEngine::UnloadSurface( std::string surface )
{
    //Find in map, free memory, delete pointer
    iter = surfaces.find( surface );
    SDL_FreeSurface( iter->second );
    surfaces.erase( iter );
}

/**
* Retrieves data of a surface
*
* @return SDL_Rect
*/
SDL_Rect RenderEngine::GetSurfaceRect( std::string surface )
{
    return surfaces[surface]->clip_rect;
}

/**
* Draw a surface
*
* @param x (int)
* Draw location x coordinate in pixels
*
* @param y (int)
* Draw location y coordinate in pixels
*
* @param surfacesource (SDL_Surface*)
* Surface to draw
*
* @param surfacedest (SDL_Surface*)
* @def screen
* Surface to draw on
*
* @param clip (SDL_Rect*)
* @def entire source surface
* Rectangle from source to draw
*/
void RenderEngine::Draw( int x, int y, SDL_Surface *surfacesource, SDL_Surface *surfacedest, SDL_Rect* clip )
{
    //SDL_SetAlpha(source, SDL_SRCALPHA, alpha);

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //If no destination provided, draw to screen
    if( surfacedest == NULL )
    {
        SDL_BlitSurface( surfacesource, clip, surfaces["screen"], &offset );
    }else{
        SDL_BlitSurface( surfacesource, clip, surfacedest, &offset );
    }
}

/**
* Update a surface
*
* @param surface (SDL_Surface*)
* @def update screen
* Surface to update
*/
void RenderEngine::Update( SDL_Surface *surface )
{
    //If no surface specified, update screen
    if( surface == NULL )
    {
        SDL_Flip(surfaces["screen"]);
		SDL_FillRect( SDL_GetVideoSurface(), NULL, SDL_MapRGB( surfaces["screen"]->format, 0x21, 0x21, 0x21 ) );
    }else{
        SDL_Flip(surface);
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
    }
}
