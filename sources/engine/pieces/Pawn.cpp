#include "Pawn.h"

std::list<Piece::pos2d>    Pawn::getMoves(ChessEngine *engine)
{
    std::list<pos2d> possibleMoves;
    std::list<pos2d> moves;
    std::list<pos2d> captures;
    int8_t direction = color == Color::BLACK ? 1 : -1;
    Piece *target = nullptr;

    if (isMoveLegal(engine, 0, direction))
        moves.push_back({pos.x, (int8_t)(pos.y + direction)});
    if (isMoveLegal(engine, 0, direction * 2) && !hasMoved)
        moves.push_back({pos.x, (int8_t)(pos.y + direction * 2)});

    if (isMoveLegal(engine, -1, direction))
        captures.push_back({(int8_t)(pos.x - 1), (int8_t)(pos.y + direction)});
    if (isMoveLegal(engine, 1, direction))
        captures.push_back({(int8_t)(pos.x + 1), (int8_t)(pos.y + direction)});

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

