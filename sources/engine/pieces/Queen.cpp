#include "Queen.h"

std::list<Move> Queen::getMoves(ChessEngine *engine)
{
    std::list<Move> moves;
    Piece *target = nullptr;

    for (int8_t xmove : {-1, 1, 0}) {
        for (int8_t ymove : {-1, 1, 0}) {
            for (int8_t inc = 1 ; inc <= 7 ; ++inc) {
                if (isMoveLegal(engine, xmove * inc, ymove * inc)) {
                    target = engine->getPieceFromPos({(int8_t)(pos.x + xmove * inc), (int8_t)(pos.y + ymove * inc)});
                    moves.push_back({
                        this,
                        {
                            (int8_t)(pos.x + xmove * inc),
                            (int8_t)(pos.y + ymove * inc)
                        },
                        target
                    });
                    if (target)
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
