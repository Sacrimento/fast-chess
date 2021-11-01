#include "Queen.h"

std::list<Piece::pos2d> Queen::getMoves(ChessEngine *engine)
{
    std::list<pos2d> moves;
    Piece *target = nullptr;

    for (int8_t xmove : {-1, 1, 0}) {
        for (int8_t ymove : {-1, 1, 0}) {
            for (int8_t inc = 1 ; inc < 7 ; ++inc) {
                if (isMoveLegal(engine, xmove * inc, ymove * inc)) {
                    if ((target = engine->getPieceFromPos({pos.x + xmove*inc, pos.y + ymove*inc}))) {
                        if (target->getColor() != color)
                            moves.push_back({pos.x + xmove * inc, pos.y + ymove * inc});
                        else
                            break;
                    }
                    else
                        moves.push_back({pos.x + xmove * inc, pos.y + ymove * inc});
                }
                else {
                    break;
                }
            }
        }
    }

    return moves;
}
