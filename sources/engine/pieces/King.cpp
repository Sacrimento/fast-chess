#include "King.h"

std::list<Piece::pos2d>    King::getMoves(ChessEngine *engine)
{
    return std::list<Piece::pos2d>{};
}

void    King::move(pos2d move)
{
    pos = move;
    canCastle = false;
}
