#include "Bishop.h"

std::list<Piece::Move>    Bishop::getMoves(ChessEngine *engine)
{
    std::list<Move> moves;
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
                target = engine->getPieceFromPos({(int8_t)(pos.x + mv.x * inc), (int8_t)(pos.y + mv.y * inc)});
                moves.push_back({this, {(int8_t)(pos.x + mv.x * inc), (int8_t)(pos.y + mv.y * inc)}, target});
                if (target)
                    // Means we will make a capture, so dont check further than this piece
                    break;
            }
            else
                break;
        }
    }

    return moves;
}
