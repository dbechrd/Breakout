#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <string>

#include "SDL\SDL.h"
#include "SDL\SDL_image.h"

class Object{
    private:

        //Texture
        SDL_Surface *tex;

		//Position & Size
        float x;
        float y;
        int w;
        int h;

        //Velocity
        float xVel;
        float yVel;
        float maxXVel;
        float maxYVel;

    public:

        //Constructor and Destructor
        Object( int nx, int ny, std::string ntex );
        Object( int nx, int ny, SDL_Surface *ntex );
        ~Object();

        //Change Texture
        bool SetTexture( SDL_Surface *newTex );

		//Position & Size Get Accessors
		float X(){ return x; }
		float Y(){ return y; }
		int W(){ return w; }
		int H(){ return h; }

		//Position Set Accessors
		void X(float nx){ x = nx; }
		void Y(float ny){ y = ny; }

		//Velocity Get Accessors
		float XVel(){ return xVel; }
		float YVel(){ return yVel; }
		float MaxXVel(){ return maxXVel; }
		float MaxYVel(){ return maxYVel; }

		//Velocity Set Accessors
		void XVel(float nxVel){ if(nxVel <= maxXVel) xVel = nxVel; }
		void YVel(float nyVel){ if(nyVel <= maxYVel) yVel = nyVel; }
		void MaxXVel(float nmaxXVel){ maxXVel = nmaxXVel; }
		void MaxYVel(float nmaxYVel){ maxYVel = nmaxYVel; }

        //Update
        void Update();

        //Render
        void Render();

};

#endif // OBJECT_H_INCLUDED
