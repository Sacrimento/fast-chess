#include "Piece.h"
#include "ChessEngine.h"

bool    Piece::isMoveOnBoard(int8_t x, int8_t y) {
    return (
        pos.x + x < 8 && pos.x + x >= 0
        && pos.y + y < 8 && pos.y + y >= 0
    );
}

bool    Piece::canCapture(Piece *p) {
    return p->getType() != Piece::Type::KING && p->getColor() != color;
}

bool    Piece::isMoveLegal(ChessEngine *engine, int8_t x, int8_t y) {
    if (!isMoveOnBoard(x, y))
        return false;

    Piece *p = engine->getPieceFromPos({(int8_t)(pos.x + x), (int8_t)(pos.y + y)});
    if (p)
        return canCapture(p);

    return true;
}
