#ifndef OBSERVER_H
#define OBSERVER_H

#include "GameState.h"

// The observer interface
class Observer
{
public:
    // virtual method to be implemented by concrete observer to update the GameState
    virtual void updateState(GameState newState) = 0;
    // virtual method to be implemented by concrete observer to update the move x from y status
    virtual void updateMoves(int turns) = 0;
};

#endif // OBSERVER_H
