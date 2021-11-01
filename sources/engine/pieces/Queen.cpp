#include "Queen.h"

std::list<Piece::pos2d> Queen::getMoves(ChessEngine *engine)
{
    std::list<pos2d> moves;
    Piece *target = nullptr;

    for (int8_t xmove : {-1, 1, 0}) {
        for (int8_t ymove : {-1, 1, 0}) {
            for (int8_t inc = 1 ; inc < 7 ; ++inc) {
                if (isMoveLegal(engine, xmove * inc, ymove * inc)) {

                    moves.push_back({
                        (int8_t)(pos.x + xmove * inc),
                        (int8_t)(pos.y + ymove * inc)
                    });
                    if ((target = engine->getPieceFromPos({(int8_t)(pos.x + xmove * inc), (int8_t)(pos.y + ymove * inc)})))
                        // Means we will make a capture, so dont check further than this piece
                        break;
                }
                else
                    break;
            }
        }
    }

    return moves;
}
