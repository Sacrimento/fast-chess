#include "Rook.h"

std::list<Piece::pos2d>    Rook::getMoves(ChessEngine *engine)
{
    return std::list<Piece::pos2d>{};
}

void    Rook::move(pos2d move)
{
    pos = move;
    canCastle = false;
}

