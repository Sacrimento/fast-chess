#include "Piece.h"
#include "ChessEngine.h"

bool    Piece::isMoveOnBoard(int8_t x, int8_t y) {
    return (
        pos.x + x < 8 && pos.x + x >= 0
        && pos.y + y < 8 && pos.y + y >= 0
    );
}

bool    Piece::canCapture(Piece *p, bool allowOwnPieceAttack) {
    return (allowOwnPieceAttack || p->getColor() != color);
}

bool    Piece::isMoveLegal(ChessEngine *engine, int8_t x, int8_t y, bool allowOwnPieceAttack, bool mustCapture, bool canMoveCapture) {
    // allowOwnPieceAttack => Useful for attackedSquares generations and king movement, to check if a piece is protected
    // mustCapture => Useful for pawns movement, target square must not be empty and must be captured
    // canCapture => Useful for pawns movement, allow capture on the target square

    if (!isMoveOnBoard(x, y))
        return false;

    Piece *p = engine->getPieceFromPos({(int8_t)(pos.x + x), (int8_t)(pos.y + y)});

    if (mustCapture && !p || !canMoveCapture && p)
        return false;

    if (p)
        return canCapture(p, allowOwnPieceAttack);

    return true;
}

std::ostream &operator<<(std::ostream &out, const Piece::pos2d &pos)
{
    out << "pos2d(x = " << (int)pos.x << ", y = " << (int)pos.y << ")";
    return out;
}

bool    operator==(const Piece::pos2d &lhs, const Piece::pos2d &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
