#include "Piece.h"
#include "ChessEngine.h"

bool    Piece::isMoveOnBoard(int8_t x, int8_t y) {
    return (
        pos.x + x < 8 && pos.x + x >= 0
        && pos.y + y < 8 && pos.y + y >= 0
    );
}

bool    Piece::isMoveLegal(ChessEngine *engine, int8_t x, int8_t y) {
    if (!isMoveOnBoard(x, y))
        return false;

    Piece *p = engine->getPieceFromPos({pos.x + x, pos.y + y});
    if (p)
        return p->getType() != Piece::Type::KING;

    return true;
}
