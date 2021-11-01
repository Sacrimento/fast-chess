#include "Pawn.h"

bool Pawn::isMoveLegal(int tx, int ty)
{
    int target = pos.x + tx;
    if (target > 7 || target < 0)
        return false;
    target = pos.y + ty;
    if (target > 7 || target < 0)
        return false;
    return true;
}

std::list<Piece::pos2d>    Pawn::getMoves(ChessEngine *engine)
{
    std::list<pos2d> possibleMoves;
    std::list<pos2d> moves;
    std::list<pos2d> captures;
    int8_t direction = color == Color::BLACK ? 1 : -1;
    Piece *target = nullptr;

    if (isMoveLegal(0, direction))
        moves.push_back({pos.x, (uint8_t)((int)pos.y + direction)});
    if (isMoveLegal(0, direction * 2) && !hasMoved)
        moves.push_back({pos.x, (uint8_t)((int)pos.y + direction * 2)});

    if (isMoveLegal(-1, direction))
        captures.push_back({(uint8_t)((int)pos.x - 1), (uint8_t)((int)pos.y + direction)});
    if (isMoveLegal(1, direction))
        captures.push_back({(uint8_t)((int)pos.x + 1), (uint8_t)((int)pos.y + direction)});

    for (auto mv : moves)
        if (!engine->getPieceFromPos(mv))
            possibleMoves.push_back(mv);

    for (auto mv : captures) {
        if ((target = engine->getPieceFromPos(mv)))
        {
            // TODO: Check for pins
            if (target->getColor() != color)
                possibleMoves.push_back(mv);
        }
    }

    return possibleMoves;
}

void    Pawn::move(pos2d move)
{
    pos = move;
    hasMoved = true;
}

