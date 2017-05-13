#include <iostream>

#include "GameEngine.h"

using namespace std;

GameEngine* GameEngine::pinstance = NULL;
bool GameEngine::quit = false;
GameEngine* GameEngine::Instance()
{
    if (pinstance == NULL)  // is it the first call?
    {
        pinstance = new GameEngine(); // create sole instance
    }
    return pinstance; // address of sole instance
}

GameEngine::GameEngine()
{
    mousex = 0;
	mousey = 0;
}

GameEngine::~GameEngine()
{
    cout << "Terminating Game Engine\n";
    cout.flush();
}

void GameEngine::HandleInput()
{
    while( SDL_PollEvent( &event ) )
    {
        if( event.type == SDL_QUIT )
        {
            keys["SDLQUIT"] = true;
            SetQuit();
        }
        if ( event.type == SDL_KEYDOWN )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_a:
                    keys["a"] = true;
                    break;
                case SDLK_b:
                    keys["b"] = true;
                    break;
                case SDLK_c:
                    keys["c"] = true;
                    break;
                case SDLK_d:
                    keys["d"] = true;
                    break;
                case SDLK_e:
                    keys["e"] = true;
                    break;
                case SDLK_f:
                    keys["f"] = true;
                    break;
                case SDLK_g:
                    keys["g"] = true;
                    break;
                case SDLK_h:
                    keys["h"] = true;
                    break;
                case SDLK_i:
                    keys["i"] = true;
                    break;
                case SDLK_j:
                    keys["j"] = true;
                    break;
                case SDLK_k:
                    keys["k"] = true;
                    break;
                case SDLK_l:
                    keys["l"] = true;
                    break;
                case SDLK_m:
                    keys["m"] = true;
                    break;
                case SDLK_n:
                    keys["n"] = true;
                    break;
                case SDLK_o:
                    keys["o"] = true;
                    break;
                case SDLK_p:
                    keys["p"] = true;
                    break;
                case SDLK_q:
                    keys["q"] = true;
                    break;
                case SDLK_r:
                    keys["r"] = true;
                    break;
                case SDLK_s:
                    keys["s"] = true;
                    break;
                case SDLK_t:
                    keys["t"] = true;
                    break;
                case SDLK_u:
                    keys["u"] = true;
                    break;
                case SDLK_v:
                    keys["v"] = true;
                    break;
                case SDLK_w:
                    keys["w"] = true;
                    break;
                case SDLK_x:
                    keys["x"] = true;
                    break;
                case SDLK_y:
                    keys["y"] = true;
                    break;
                case SDLK_z:
                    keys["z"] = true;
                    break;
                case SDLK_0:
                    keys["0"] = true;
                    break;
                case SDLK_1:
                    keys["1"] = true;
                    break;
                case SDLK_2:
                    keys["2"] = true;
                    break;
                case SDLK_3:
                    keys["3"] = true;
                    break;
                case SDLK_4:
                    keys["4"] = true;
                    break;
                case SDLK_5:
                    keys["5"] = true;
                    break;
                case SDLK_6:
                    keys["6"] = true;
                    break;
                case SDLK_7:
                    keys["7"] = true;
                    break;
                case SDLK_8:
                    keys["8"] = true;
                    break;
                case SDLK_9:
                    keys["9"] = true;
                    break;
                case SDLK_UP:
                    keys["up"] = true;
                    break;
                case SDLK_DOWN:
                    keys["down"] = true;
                    break;
                case SDLK_LEFT:
                    keys["left"] = true;
                    break;
                case SDLK_RIGHT:
                    keys["right"] = true;
                    break;
                case SDLK_RETURN:
                    keys["return"] = true;
                    //Action();
                    break;
                case SDLK_SPACE:
                    keys["space"] = true;
                    break;
                case SDLK_BACKSPACE:
                    keys["backspace"] = true;
                    break;
                case SDLK_LSHIFT:
                    keys["lshift"] = true;
                    break;
                case SDLK_RSHIFT:
                    keys["rshift"] = true;
                    break;
                case SDLK_LALT:
                    keys["lalt"] = true;
                    break;
                case SDLK_RALT:
                    keys["ralt"] = true;
                    break;
                case SDLK_LCTRL:
                    keys["lctrl"] = true;
                    break;
                case SDLK_RCTRL:
                    keys["rctrl"] = true;
                    break;
                case SDLK_F1:
                    keys["F1"] = true;
                    break;
                case SDLK_F2:
                    keys["F2"] = true;
                    break;
                case SDLK_F3:
                    keys["F3"] = true;
                    break;
                case SDLK_F4:
                    keys["F4"] = true;
                    //renderer->ToggleFullScreen();
                    break;
                case SDLK_F5:
                    keys["F5"] = true;
                    break;
                case SDLK_F6:
                    keys["F6"] = true;
                    break;
                case SDLK_F7:
                    keys["F7"] = true;
                    break;
                case SDLK_F8:
                    keys["F8"] = true;
                    break;
                case SDLK_F9:
                    keys["F9"] = true;
                    break;
                case SDLK_F10:
                    keys["F10"] = true;
                    break;
                case SDLK_F11:
                    keys["F11"] = true;
                    break;
                case SDLK_F12:
                    keys["F12"] = true;
                    break;
                case SDLK_ESCAPE:
                    keys["esc"] = true;
                    break;
                default:
                    break;
            }
        }
        if ( event.type == SDL_KEYUP )
        {
            switch( event.key.keysym.sym )
            {
                case SDLK_a:
                    keys["a"] = false;
                    break;
                case SDLK_b:
                    keys["b"] = false;
                    break;
                case SDLK_c:
                    keys["c"] = false;
                    break;
                case SDLK_d:
                    keys["d"] = false;
                    break;
                case SDLK_e:
                    keys["e"] = false;
                    break;
                case SDLK_f:
                    keys["f"] = false;
                    break;
                case SDLK_g:
                    keys["g"] = false;
                    break;
                case SDLK_h:
                    keys["h"] = false;
                    break;
                case SDLK_i:
                    keys["i"] = false;
                    break;
                case SDLK_j:
                    keys["j"] = false;
                    break;
                case SDLK_k:
                    keys["k"] = false;
                    break;
                case SDLK_l:
                    keys["l"] = false;
                    break;
                case SDLK_m:
                    keys["m"] = false;
                    break;
                case SDLK_n:
                    keys["n"] = false;
                    break;
                case SDLK_o:
                    keys["o"] = false;
                    break;
                case SDLK_p:
                    keys["p"] = false;
                    break;
                case SDLK_q:
                    keys["q"] = false;
                    break;
                case SDLK_r:
                    keys["r"] = false;
                    break;
                case SDLK_s:
                    keys["s"] = false;
                    break;
                case SDLK_t:
                    keys["t"] = false;
                    break;
                case SDLK_u:
                    keys["u"] = false;
                    break;
                case SDLK_v:
                    keys["v"] = false;
                    break;
                case SDLK_w:
                    keys["w"] = false;
                    break;
                case SDLK_x:
                    keys["x"] = false;
                    break;
                case SDLK_y:
                    keys["y"] = false;
                    break;
                case SDLK_z:
                    keys["z"] = false;
                    break;
                case SDLK_0:
                    keys["0"] = false;
                    break;
                case SDLK_1:
                    keys["1"] = false;
                    break;
                case SDLK_2:
                    keys["2"] = false;
                    break;
                case SDLK_3:
                    keys["3"] = false;
                    break;
                case SDLK_4:
                    keys["4"] = false;
                    break;
                case SDLK_5:
                    keys["5"] = false;
                    break;
                case SDLK_6:
                    keys["6"] = false;
                    break;
                case SDLK_7:
                    keys["7"] = false;
                    break;
                case SDLK_8:
                    keys["8"] = false;
                    break;
                case SDLK_9:
                    keys["9"] = false;
                    break;
                case SDLK_UP:
                    keys["up"] = false;
                    break;
                case SDLK_DOWN:
                    keys["down"] = false;
                    break;
                case SDLK_LEFT:
                    keys["left"] = false;
                    break;
                case SDLK_RIGHT:
                    keys["right"] = false;
                    break;
                case SDLK_RETURN:
                    keys["return"] = false;
                    break;
                case SDLK_SPACE:
                    keys["space"] = false;
                    break;
                case SDLK_BACKSPACE:
                    keys["backspace"] = false;
                    break;
                case SDLK_LSHIFT:
                    keys["lshift"] = false;
                    break;
                case SDLK_RSHIFT:
                    keys["rshift"] = false;
                    break;
                case SDLK_LALT:
                    keys["lalt"] = false;
                    break;
                case SDLK_RALT:
                    keys["ralt"] = false;
                    break;
                case SDLK_LCTRL:
                    keys["lctrl"] = false;
                    break;
                case SDLK_RCTRL:
                    keys["rctrl"] = false;
                    break;
                case SDLK_F1:
                    keys["F1"] = false;
                    break;
                case SDLK_F2:
                    keys["F2"] = false;
                    break;
                case SDLK_F3:
                    keys["F3"] = false;
                    break;
                case SDLK_F4:
                    keys["F4"] = false;
                    //renderer->ToggleFullScreen();
                    break;
                case SDLK_F5:
                    keys["F5"] = false;
                    break;
                case SDLK_F6:
                    keys["F6"] = false;
                    break;
                case SDLK_F7:
                    keys["F7"] = false;
                    break;
                case SDLK_F8:
                    keys["F8"] = false;
                    break;
                case SDLK_F9:
                    keys["F9"] = false;
                    break;
                case SDLK_F10:
                    keys["F10"] = false;
                    break;
                case SDLK_F11:
                    keys["F11"] = false;
                    break;
                case SDLK_F12:
                    keys["F12"] = false;
                    break;
                case SDLK_ESCAPE:
                    keys["esc"] = false;
                    break;
                default:
                    break;
            }
        }
        if( event.type == SDL_MOUSEBUTTONUP )
        {
            switch( event.button.button )
            {
                case SDL_BUTTON_LEFT:
                    keys["mouseLeft"] = false;
                    break;
                case SDL_BUTTON_RIGHT:
                    keys["mouseRight"] = false;
                    break;
				case SDL_BUTTON_MIDDLE:
					keys["mouseMiddle"] = false;
                    break;
                case SDL_BUTTON_WHEELUP:
					keys["mouseWheelUp"] = false;
                    break;
                case SDL_BUTTON_WHEELDOWN:
                    keys["mouseWheelDown"] = false;
                    break;
                default:
                    break;
            }
        }
        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            mousex = event.button.x;
            mousey = event.button.y;
            switch( event.button.button )
            {
                case SDL_BUTTON_LEFT:
                    keys["mouseLeft"] = true;
                    break;
                case SDL_BUTTON_RIGHT:
                    keys["mouseRight"] = true;
                    break;
                case SDL_BUTTON_MIDDLE:
					keys["mouseMiddle"] = true;
                    break;
                case SDL_BUTTON_WHEELUP:
					keys["mouseWheelUp"] = true;
                    break;
                case SDL_BUTTON_WHEELDOWN:
                    keys["mouseWheelDown"] = true;
                    break;
                default:
                    break;
            }
        }
        if( event.type == SDL_MOUSEMOTION )
        {
            SDL_GetMouseState(&mousex, &mousey);

        }
    }
}

bool GameEngine::KeyDown( std::string key )
{
    iter = keys.find( key );
    if( iter != keys.end() )
    {
        return iter->second;
    }else{
        return false;
    }
}

bool GameEngine::KeyUp( std::string key )
{
    iter = keys.find( key );
    if( iter != keys.end() )
    {
        return !iter->second;
    }else{
        return true;
    }
}

void GameEngine::SetQuit()
{
    quit = true;
}

bool GameEngine::Quit()
{
    return quit;
}
