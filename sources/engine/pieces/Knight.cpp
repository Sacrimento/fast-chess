#include "Knight.h"

std::list<Move>    Knight::getMoves(ChessEngine *engine, bool allAttackedSquares)
{
    std::list<Move> moves;
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
        if (isMoveLegal(engine, mv.x, mv.y, allAttackedSquares))
            moves.push_back(
            {
                this, {(int8_t)(pos.x + mv.x), (int8_t)(pos.y + mv.y)},
                engine->getPieceFromPos({(int8_t)(pos.x + mv.x), (int8_t)(pos.y + mv.y)})
            });

    return moves;
}
