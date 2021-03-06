#include "Bishop.h"

std::list<Move>    Bishop::getMoves(ChessEngine *engine, bool allAttackedSquares)
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
            if (isMoveLegal(engine, mv.x * inc, mv.y * inc, allAttackedSquares)) {
                target = engine->getPieceFromPos({(int8_t)(pos.x + mv.x * inc), (int8_t)(pos.y + mv.y * inc)});
                moves.push_back({this, {(int8_t)(pos.x + mv.x * inc), (int8_t)(pos.y + mv.y * inc)}, target});
                if (target && !(allAttackedSquares && target->getType() == Type::KING))
                    // Means we will make a capture, so dont check further than this piece
                    break;
            }
            else
                break;
        }
    }

    return moves;
}
