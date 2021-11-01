#include "Bishop.h"

std::list<Piece::pos2d>    Bishop::getMoves(ChessEngine *engine)
{
    std::list<Piece::pos2d> moves;
    std::list<pos2d> possibleMoves = {
        {-1, 1},
        {-1, -1},
        {1, 1},
        {1, -1},
    };
    Piece *target = nullptr;

    for (auto mv : possibleMoves) {
        for (int8_t inc = 1 ; inc <= 7 ; ++inc) {
            if (isMoveLegal(engine, mv.x * inc, mv.y * inc)) {
                moves.push_back({(int8_t)(pos.x + mv.x * inc), (int8_t)(pos.y + mv.y * inc)});

                if ((target = engine->getPieceFromPos({(int8_t)(pos.x + mv.x * inc), (int8_t)(pos.y + mv.y * inc)})))
                    // Means we will make a capture, so dont check further than this piece
                    break;
            }
        }
    }

    return moves;
}
