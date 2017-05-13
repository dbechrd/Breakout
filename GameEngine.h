#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <string>
#include <map>

#include "SDL/SDL.h"

class GameEngine{
    private:

        //Singleton Instance
        static GameEngine* pinstance;

        //Termination state
        static bool quit;

        //Engine events
        SDL_Event event;

        //Key states
        std::map<std::string, bool> keys;
        std::map<std::string, bool>::iterator iter;

    protected:

        //Protected constructors (for singleton)
        GameEngine();
        GameEngine(const GameEngine&);
        GameEngine& operator= (const GameEngine&);

    public:

        //Mouse coords
        int mousex;
        int mousey;

        static void SetQuit();
        static bool Quit();

        //Instance (one-time constructor) & Destructor
        static GameEngine* Instance();
        ~GameEngine();

        //Input handling and checking
        void HandleInput();
        bool KeyDown( std::string key );
        bool KeyUp( std::string key );
};

#endif // GAMEENGINE_H_INCLUDED
