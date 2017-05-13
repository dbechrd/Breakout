#ifndef RENDERENGINE_H_INCLUDED
#define RENDERENGINE_H_INCLUDED

#include <string>
#include <map>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class RenderEngine{
    private:

        //Singleton Instance
        static RenderEngine* pinstance;

        //Fullscreen status
        bool fullScreen;

        //Surface map and interator for that map
        std::map<std::string, SDL_Surface*> surfaces;
        std::map<std::string, SDL_Surface*>::iterator iter;

		//Background image
		SDL_Surface *back;

    protected:

        //Protected constructors (for singleton)
        RenderEngine();
        RenderEngine(const RenderEngine&);
        RenderEngine& operator= (const RenderEngine&);

    public:

        //Instance (one-time constructor) & Destructor
        static RenderEngine* Instance();
        ~RenderEngine();

        //Change fullscreen status
        void ToggleFullScreen();

        //Load a new image
        SDL_Surface *LoadSurface( std::string filename );

        //Retrieve image rect
        SDL_Rect GetSurfaceRect( std::string surface );

        //Free an image
        void UnloadSurface( std::string surface );

        //Draw an image
        void Draw( int x, int y, SDL_Surface *surfacesource, SDL_Surface *surfacedest = NULL, SDL_Rect* clip = NULL );

        //Update a surface
        void Update( SDL_Surface *surface = NULL );

};

#endif // RENDERENGINE_H_INCLUDED
