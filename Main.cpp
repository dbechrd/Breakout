/**
* Breakout Clone
*
* @date October 13, 2009
* @author Dan Bechard (dandymcgee123@yahoo.com)
*/

#ifdef _WIN32
	#pragma comment(lib, "SDL.lib")
	#pragma comment(lib, "SDLmain.lib")
	#pragma comment(lib, "SDL_image.lib")
#endif

#include <iostream>
#include <vector>
#include <math.h>

#include "SDL\SDL.h"
#include "SDL\SDL_image.h"

#include "RenderEngine.h"
#include "GameEngine.h"
#include "Object.h"

//Application States
enum GameState{ APP_MENU, APP_PLAY, APP_QUIT };

//Controller Enumeration
enum Controllers{ CON_KEYBOARD, CON_MOUSE };

int main( int argc, char *argv[] )
{
    //Framerate Limiter
    const int FRAMERATE = 500;
    int oldTime = SDL_GetTicks();

    //Application State
    GameState gameState = APP_PLAY;

    //Input method
    Controllers controller = CON_MOUSE;
    //Controllers controller = CON_KEYBOARD;

    //RenderEngine (singleton) instance
    RenderEngine *renderer = RenderEngine::Instance();

    //Game Engine
    GameEngine *engine = GameEngine::Instance();

    //Hide mouse cursor
    SDL_ShowCursor(SDL_DISABLE);

    //Bricks
    std::vector<Object*> bricks;
    std::vector<Object*>::iterator bricksIter;

    //Create paddle and ball
    Object paddle( 640/2 - 32, 480 - 40, renderer->LoadSurface( "paddle.png" ) );
    Object ball( 150, 300, renderer->LoadSurface( "ball.png" ) );

    //Dock the ball
    ball.X((paddle.X() + paddle.W()*0.5) - ball.W()*0.5);
    ball.Y(paddle.Y() - ball.H());
    ball.MaxXVel(1.5);
    ball.MaxYVel(1.5);
    bool dockedBall = true;

	//Load the brick images
    SDL_Surface *brick1 = renderer->LoadSurface( "brick1.png" );
    SDL_Surface *brick2 = renderer->LoadSurface( "brick2.png" );
	SDL_Surface *brick3 = renderer->LoadSurface( "brick3.png" );
	SDL_Surface *brick4 = renderer->LoadSurface( "brick4.png" );
	SDL_Surface *brick5 = renderer->LoadSurface( "brick5.png" );
	SDL_Surface *brick6 = renderer->LoadSurface( "brick6.png" );
	SDL_Surface *brick7 = renderer->LoadSurface( "brick7.png" );

	//Create the brick objects (used for collision)
    int color = 0;
	for( int y = 2; y < 8; y++ )
    {
        for( int x = 1; x < 9; x++ )
        {
            Object *temp;
			switch( color )
			{
				case 0:
					temp = new Object( x * 64, y * 26, brick1 );
					break;
				case 1:
					temp = new Object( x * 64, y * 26, brick2 );
					break;
				case 2:
					temp = new Object( x * 64, y * 26, brick3 );
					break;
				case 3:
					temp = new Object( x * 64, y * 26, brick4 );
					break;
				case 4:
					temp = new Object( x * 64, y * 26, brick5 );
					break;
				case 5:
					temp = new Object( x * 64, y * 26, brick6 );
					break;
				case 6:
					temp = new Object( x * 64, y * 26, brick7 );
					break;
				default:
					break;
            }
			if( color == 6 )
			{
				color = 0;
			}else{
				color++;
			}
            temp->Render();
            bricks.push_back( temp );
        }
    }

    //Previous key states for paddle acceleration
    bool keyLeft = false;
    bool keyRight = false;

    //Main state loop
    while( gameState != APP_QUIT )
    {
		int newTime = SDL_GetTicks();
        int deltaTime = newTime - oldTime;
        bool collisionDone = false;

        engine->HandleInput();

		//Check for user exiting
        if( engine->KeyDown("esc") || engine->KeyDown("SDLQUIT") )
        {
            gameState = APP_QUIT;
        }

        switch( gameState ) {

            //Menu state
            case APP_MENU:
                //menu stuff here
                //gameState = APP_QUIT;

                renderer->Update();
                if( GameEngine::Quit() ) {
                    gameState = APP_QUIT;
				}
                break;
            //Game state
            case APP_PLAY:

                //Input
                //KEYBOARD CONTROLS
                if( controller == CON_KEYBOARD ){

                    //Undocking the ball
                    if( engine->KeyDown("space") ){
                        if( dockedBall ){
                            ball.YVel(-1.5);
                            dockedBall = false;
                        }
                    }

                    //Paddle Movement
                    if( engine->KeyDown("left") ){
                        //Accelerates paddle if user holds down the key
                        if( !keyLeft ){
                            paddle.XVel(-2.5);
                            keyRight = false;
                            keyLeft = true;
                        }else{
							paddle.XVel(paddle.XVel() - 0.01);
                        }
                    }else if( engine->KeyDown("right") ){
                        //Accelerates paddle if user holds down the key
                        if( !keyRight ){
                            paddle.XVel(2.5);
                            keyLeft = false;
                            keyRight = true;
                        }else{
                            paddle.XVel(paddle.XVel() + 0.01);
                        }
                    }else if( paddle.XVel() != 0 ){
                        keyLeft = false;
                        keyRight = false;
                        if( paddle.XVel() >= 0.12 ){
                            paddle.XVel(paddle.XVel() - 0.12);
                        }else if( paddle.XVel() <= -0.12 ){
                            paddle.XVel(paddle.XVel() + 0.12);
                        }else if( paddle.XVel() > -0.12 && paddle.XVel() < 0.12 ){
                            paddle.XVel(0);
                        }
                    }else{
                        keyLeft = false;
                        keyRight = false;
                    }

                    //Collision fix
					if( paddle.X() + paddle.XVel() < 0 || paddle.X() + paddle.XVel() > 640 - paddle.W() ){
                        if( paddle.X() < 0 ){
                            paddle.X(0);
                        }else if( paddle.X() > 640 - paddle.W() ){
                            paddle.X(640 - paddle.W());
                        }
                        paddle.XVel(0);
                    }

                //MOUSE CONTROLS
                }else if( controller == CON_MOUSE ){

                    //Undocking the ball
                    if( engine->KeyDown("mouseLeft") ){
                        if( dockedBall ){
                            ball.YVel(-1.5);
                            dockedBall = false;
                        }
                    }

                    //Paddle Movement
                    if( engine->mousex - 32 < 0 ){
                        paddle.X(0);
                    }else if( engine->mousex - 32 > 640 - paddle.W() ){
						paddle.X(640 - paddle.W());
                    }else{
                        paddle.X(engine->mousex - 32);
                        /*Smooth sliding paddle
                        if( paddle.X() < engine->mousex - 32 ){
                            paddle.XVel(15);
                        }else if( paddle.X() > engine->mousex - 32 ){
                            paddle.XVel(-15);
                        }else{
                            paddle.XVel(0);
                        }
                        */
                    }

                }

                //Collision detection (if ball is docked skip collision detection)
                if( !dockedBall ){

                    //Collision with bricks
                    for( bricksIter = bricks.begin(); bricksIter != bricks.end(); ++bricksIter )
                    {
                        if( (ball.X() + ball.XVel() + ball.W() > (*bricksIter)->X()) && (ball.X() + ball.XVel() < (*bricksIter)->X() + (*bricksIter)->W()) && (ball.Y() + ball.YVel() + ball.H() > (*bricksIter)->Y()) && (ball.Y() + ball.YVel() < (*bricksIter)->Y() + (*bricksIter)->H()) )
						{
                            //Determine overlap for each axis
                            float xDist = abs((ball.X() + ball.XVel() + (ball.W()*0.5)) - ((*bricksIter)->X() + ((*bricksIter)->W()*0.5)));
                            float yDist = abs((ball.Y() + ball.YVel() + (ball.H()*0.5)) - ((*bricksIter)->Y() + ((*bricksIter)->H()*0.5)));

                            //minimal amount of distance that the two can be apart and not collide
                            float xMinDist = (ball.W()*0.5) + ((*bricksIter)->W()*0.5);
                            float yMinDist = (ball.H()*0.5) + ((*bricksIter)->H()*0.5);

                            if(!(xDist >= xMinDist || yDist >= yMinDist)) //either axis is colliding
                            {
                                float xOverlap = (xMinDist - xDist)/xMinDist;
                                float yOverlap = (yMinDist - yDist)/yMinDist;

                                if(xOverlap < yOverlap){
                                    ball.XVel(-ball.XVel());
                                }else{
                                    ball.YVel(-ball.YVel());
                                }
                            }

                            delete (*bricksIter);
                            bricks.erase( bricksIter );

                            break;
                        }
                    }

                    //Collision with paddle
                    if( (ball.X() + ball.XVel() + ball.W() > paddle.X() + paddle.XVel()) && (ball.X() + ball.XVel() < paddle.X() + paddle.XVel() + paddle.W()) && (ball.Y() + ball.YVel() + ball.H() > paddle.Y() + paddle.YVel()) && (ball.Y() + ball.YVel() < paddle.Y() + paddle.YVel() + paddle.H()) && ball.Y() + ball.H() <= paddle.Y() )
					{
                        //Determine overlap for each axis
                        float xDist = (ball.X() + (ball.W()*0.5)) - (paddle.X() + (paddle.W()*0.5));
                        float yDist = (ball.Y() + (ball.H()*0.5)) - (paddle.Y() + (paddle.H()*0.5));

                        //minimal amount of distance that the two can be apart and not collide
                        float xMinDist = (ball.W()*0.5) + (paddle.W()*0.5);
                        float yMinDist = (ball.H()*0.5) + (paddle.H()*0.5);

                        if(!(xDist >= xMinDist || yDist >= yMinDist)) //either axis is not colliding
                        {
                            float xOverlap = (xMinDist - abs(xDist))/xMinDist;
                            float yOverlap = (yMinDist - abs(yDist))/yMinDist;

                            std::cout << xOverlap;

                            if(xOverlap < yOverlap){
                                ball.XVel(-ball.XVel());
                            }else{
                                if( xDist > 0 )
                                    ball.XVel(ball.XVel() + 2-xOverlap*2);
                                else
                                    ball.XVel(ball.XVel() - 2-xOverlap*2);
                                ball.YVel(-ball.YVel());
                            }
                            ball.X(ball.X() + ball.XVel());
                            ball.Y(ball.Y() + ball.YVel());
                        }
                    }else if( ball.X() + ball.XVel() < 0 || ball.X() + ball.W() + ball.XVel() > 640){
                        ball.XVel(-ball.XVel());
                    }else if( ball.Y() + ball.YVel() < 0 ){
                        ball.YVel(-ball.YVel());
                    }else if( ball.Y() + ball.H() + ball.YVel() > 480 ){
                        ball.X((paddle.X() + paddle.W()*0.5) - ball.W()*0.5 - 1);
                        ball.Y(paddle.Y() - ball.H());
                        ball.XVel(0);
                        ball.YVel(0);
                        dockedBall = true;
                    }

                //Ball is docked on paddle
                }else{
                    if( controller == CON_KEYBOARD ){
                        ball.XVel(paddle.XVel());
                    }else if( controller == CON_MOUSE ){
                        ball.X((paddle.X() + paddle.W()*0.5) - ball.W()*0.5 - 1);
                    }
                }

                //Update
                paddle.Update();
                ball.Update();
                for( int i = bricks.size() - 1; i >= 0; i-- )
                {
                    bricks[i]->Update();
                }

                //Render
                paddle.Render();
                ball.Render();
                for( int i = bricks.size() - 1; i >= 0; i-- )
                {
                    bricks[i]->Render();
                }
                renderer->Update();

                //Limit Framerate
                if( deltaTime < 1000 / FRAMERATE )
                {
                    SDL_Delay( (1000 / FRAMERATE) - deltaTime );
                }
                oldTime = SDL_GetTicks();

                break;
			//Clean up
            case APP_QUIT:
				delete renderer;
				delete engine;
                for( int i = bricks.size() - 1; i >= 0; i-- )
                {
                    delete bricks[i];
                }
                break;
        }
    }

    //Wait a minute!
    //SDL_Delay(2000);

    //Clean up SDL
    SDL_Quit();

    return 0;
}

/*
bool Collision(Rect rect1, Rect rect2) {
    //Determine overlap for each axis
    float xDist = abs(rect1.x - rect2.x);
    float yDist = abs(rect1.y - rect2.y);

    //minimal amount of distance that the two can be apart and not collide
    float xMinDist = rect1.width*0.5 + rect2.width*0.5;
    float yMinDist = rect1.height*0.5 + rect2.height*0.5;

    if(xDist >= xMinDist || yDist >= yMinDist) return false; //neither axis is colliding

    float xOverlap = xDist - xMinDist;
    float yOverlap = yDist - yMinDist;

    if(xOverlap < yOverlap) xvel = -xvel;
    else yvel = -yvel;

    return true;
}
*/
