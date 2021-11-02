#include "King.h"

std::list<Piece::Move>    King::getMoves(ChessEngine *engine)
{
    return std::list<Move>{};
}

void    King::move(pos2d move)
{
    pos = move;
    canCastle = false;
}
