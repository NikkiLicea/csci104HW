#include "move.h"


// Complete
Move::Move(Board* board)
{
    m.first = Vehicle::INVALID_ID;
    m.second = 0;
    b = board;
    g = 0;
    h = 0;
    prev = NULL;
}

// To be completed - DONE
Move::Move(const Board::MovePair& move, Board* board,  Move *parent){
    m.first = move.first;
    m.second = move.second;
    b = board;
    g = parent->g + 1;
    h = 0;
    prev = parent;
}

// To be completed
Move::~Move()
{
    delete b;
}

// To be completed - DONE
bool Move::operator<(const Move& rhs) const{
    // Replace this
    // different f-scores
    if((this->g + this->h) < (rhs.g + rhs.h)){
        return true;
    }
    // equal f-scores but move1 has a smaller h-score
    if(this->h < rhs.h){
        return true;
    }
    // equal f-scores and equal h-scores and move1’s Board is less-than move2’s Board, we consider move1 < move2 to be true
    MoveBoardComp c;
    if(c(this, &rhs)){
        return true;
    }
    return false;
}

// To be completed - DONE
void Move::score(Heuristic *heur) {
    this->h = heur->compute(*(this->b));
}
