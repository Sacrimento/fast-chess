#include "Piece.h"
#include "ChessEngine.h"

bool    Piece::isMoveOnBoard(int8_t x, int8_t y) {
    return (
        pos.x + x < 8 && pos.x + x >= 0
        && pos.y + y < 8 && pos.y + y >= 0
    );
}

bool    Piece::canCapture(Piece *p) {
    return p->getColor() != color && p->getType() != Piece::Type::KING;
}

bool    Piece::isMoveLegal(ChessEngine *engine, int8_t x, int8_t y, bool mustCapture, bool canMoveCapture) {
    if (!isMoveOnBoard(x, y))
        return false;

    Piece *p = engine->getPieceFromPos({(int8_t)(pos.x + x), (int8_t)(pos.y + y)});

    if (mustCapture && !p || !canMoveCapture && p)
        return false;

    if (p)
        return canCapture(p);

    return true;
}

std::ostream &operator<<(std::ostream &out, const Piece::pos2d &pos)
{
    out << "pos2d(x = " << (unsigned int)pos.x << ", y = " << (unsigned int)pos.y << ")";
    return out;
}
