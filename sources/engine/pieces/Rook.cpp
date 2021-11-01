#include "Rook.h"

std::list<Piece::pos2d>    Rook::getMoves(ChessEngine *engine)
{

    std::list<Piece::pos2d> moves;
    Piece *target = nullptr;

    for (int8_t xmove: {-1, 1}) {
        for (int8_t inc = 1 ; inc < 7 ; ++inc) {
            if (isMoveLegal(engine, xmove * inc, 0)) {
                moves.push_back({(int8_t)(pos.x + xmove * inc), pos.y});
                if ((target = engine->getPieceFromPos({(int8_t)(pos.x + xmove * inc), pos.y})))
                    // Means we will make a capture, so dont check further than this piece
                    break;
            }
        }
    }

    for (int8_t ymove: {-1, 1}) {
        for (int8_t inc = 1 ; inc < 7 ; ++inc) {
            if (isMoveLegal(engine, 0, ymove * inc)) {
                moves.push_back({pos.x, (int8_t)(pos.y + ymove * inc)});
                if ((target = engine->getPieceFromPos({pos.x, (int8_t)(pos.y + ymove * inc)})))
                    // Means we will make a capture, so dont check further than this piece
                    break;
            }
        }
    }

    return moves;
}

void    Rook::move(pos2d move)
{
    pos = move;
    canCastle = false;
}

