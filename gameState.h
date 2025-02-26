#ifndef GAMESTATE_H
#define GAMESTATE_H

enum class GameState
{
    Ready,              // The game is ready to be started
    Playing,            // The game is currently processing
    Paused,             // The game is paused to change something or to wait for user input
    Finished            // the game has finished sorting
};

#endif // GAMESTATE_H
