#include "Pawn.h"

bool Pawn::canCapture(Piece *p) {
    if (!Piece::canCapture(p))
        return false;

    return p->getPos().x == pos.x - 1 || p->getPos().x == pos.x + 1;
}

std::list<Piece::pos2d>    Pawn::getMoves(ChessEngine *engine)
{
    std::list<pos2d> moves;
    int8_t direction = color == Color::BLACK ? 1 : -1;

    if (isMoveLegal(engine, 0, direction))
        moves.push_back({pos.x, (int8_t)(pos.y + direction)});
    if (isMoveLegal(engine, 0, direction * 2) && !hasMoved)
        moves.push_back({pos.x, (int8_t)(pos.y + direction * 2)});

    if (isMoveLegal(engine, -1, direction))
        moves.push_back({(int8_t)(pos.x - 1), (int8_t)(pos.y + direction)});
    if (isMoveLegal(engine, 1, direction))
        moves.push_back({(int8_t)(pos.x + 1), (int8_t)(pos.y + direction)});

    return moves;
}

void    Pawn::move(pos2d move)
{
    pos = move;
    hasMoved = true;
}

