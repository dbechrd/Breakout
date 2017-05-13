#include "Object.h"
#include "RenderEngine.h"

/**
* Constructor (Overloaded)
*
* @param nx, ny
* Position
*
* @param ntex (std::string)
* Texture filename
*/
Object::Object( int nx, int ny, std::string ntex )
{
    x = nx;
    y = ny;

    xVel = 0;
    yVel = 0;
    maxXVel = 0;
    maxYVel = 0;

    tex = RenderEngine::Instance()->LoadSurface( ntex );

    w = tex->w;
    h = tex->h;
}

/**
* Constructor (Overloaded)
*
* @param nx, ny
* Position
*
* @param ntex (SDL_Surface*)
* Texture
*/
Object::Object( int nx, int ny, SDL_Surface *ntex )
{
    x = nx;
    y = ny;

    xVel = 0;
    yVel = 0;
    maxXVel = 0;
    maxYVel = 0;

    tex = ntex;

    w = tex->w;
    h = tex->h;
}

/**
* Destructor
*/
Object::~Object()
{
    //unload texture
    //tex = NULL
}

/**
* Change Texture
*
* @param texFile (std::string)
* Texture filename
*
* @return bool
* Change successful
*/
bool Object::SetTexture( SDL_Surface *newTex )
{
    if( newTex != NULL ){
        tex = newTex;
    }else{
        return false;
    }

    return true;
}

/**
* Update Object
*/
void Object::Update()
{
    if( xVel != 0 && maxXVel != 0 ){
        if( xVel > maxXVel )
            xVel = maxXVel;
        else if( xVel < -maxXVel )
            xVel = -maxXVel;
    }

    if( yVel != 0 && maxYVel != 0 ){
        if( yVel > maxYVel )
            yVel = maxYVel;
        else if( yVel < -maxYVel )
            yVel = -maxYVel;
    }

    x += xVel;
    y += yVel;
}

/**
* Draw Object
*/
void Object::Render()
{
    RenderEngine::Instance()->Draw( (int)x, (int)y, tex );
}
