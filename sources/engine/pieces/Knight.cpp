#include "Knight.h"

std::list<Piece::pos2d>    Knight::getMoves(ChessEngine *engine)
{
    std::list<pos2d> moves;
    std::list<pos2d> possibleMoves = {
        {-1, 2},
        {1, 2},
        {-2, 1},
        {2, 1},
        {-1, -2},
        {1, -2},
        {-2, -1},
        {2, -1},
    };

    for (auto mv: possibleMoves)
        if (isMoveLegal(engine, mv.x, mv.y))
            moves.push_back({pos.x + mv.x, pos.y + mv.y});

    return moves;
}
