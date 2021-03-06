#include "Rook.h"

std::list<Move>    Rook::getMoves(ChessEngine *engine, bool allAttackedSquares)
{
    std::list<Move> moves;
    Piece *target = nullptr;

    for (int8_t xmove: {-1, 1}) {
        for (int8_t inc = 1 ; inc <= 7 ; ++inc) {
            if (isMoveLegal(engine, xmove * inc, 0, allAttackedSquares)) {
                target = engine->getPieceFromPos({(int8_t)(pos.x + xmove * inc), pos.y});
                moves.push_back({this, {(int8_t)(pos.x + xmove * inc), pos.y}, target});
                if (target && !(allAttackedSquares && target->getType() == Type::KING))
                    // Means we will make a capture, so dont check further than this piece
                    break;
            }
            else
                break;
        }
    }

    for (int8_t ymove: {-1, 1}) {
        for (int8_t inc = 1 ; inc <= 7 ; ++inc) {
            if (isMoveLegal(engine, 0, ymove * inc, allAttackedSquares)) {
                target = engine->getPieceFromPos({pos.x, (int8_t)(pos.y + ymove * inc)});
                moves.push_back({this, {pos.x, (int8_t)(pos.y + ymove * inc)}, target});
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

void    Rook::move(pos2d move)
{
    pos = move;
    canCastle = false;
}

