#include "Piece.h"
#include "ChessEngine.h"

bool    Piece::isRay()
{
    return ray;
}

bool    Piece::isMoveOnBoard(int8_t x, int8_t y) {
    return (
        pos.x + x < 8 && pos.x + x >= 0
        && pos.y + y < 8 && pos.y + y >= 0
    );
}

bool    Piece::canCapture(Piece *p, bool allowOwnPieceAttack) {
    return (allowOwnPieceAttack || p->getColor() != color);
}

bool    Piece::canStopCheck(ChessEngine *engine, Piece *checkingPiece, int8_t x, int8_t y)
{
    // Can capture the piece ?
    if (type == Type::KING || checkingPiece->getPos() == pos2d{(int8_t)(pos.x + x), (int8_t)(pos.y + y)})
        return true;

    // You can't block if the piece is not a rook/queen/bishop
    if (!checkingPiece->isRay())
        return false;

    // Check if moving to the square would block the check to our king
    Piece *king = *std::find_if(engine->pieces.begin(), engine->pieces.end(), [this] (Piece *p) { return p->getPieceRepresentation() == (Piece::Type::KING | color);});
    // Check if our move is on the segment checkingPiece -> king, and would block the check
    auto x1 = checkingPiece->getPos().x, x2 = king->getPos().x, x3 = (int8_t)(pos.x + x);
    auto y1 = checkingPiece->getPos().y, y2 = king->getPos().y, y3 = (int8_t)(pos.y + y);

    if (x1 == x2)
        return (x3 == x2 && (std::min(y1, y2) < y3 && y3 < std::max(y1, y2)));

    auto slope = ((y2 - y1) / (x2 - x1));
    bool isAligned = ((y3 - y1) == slope * (x3 - x1));
    bool isBetween = ((std::min(x1, x2) < x3 && x3 < std::max(x1, x2)) && (std::min(y1, y2) < y3 && y3 < std::max(y1, y2)));

    return isAligned && isBetween;
}

bool    Piece::isMoveLegal(ChessEngine *engine, int8_t x, int8_t y, bool allowOwnPieceAttack, bool mustCapture, bool canMoveCapture) {
    // allowOwnPieceAttack => Useful for attackedSquares generations and king movement, to check if a piece is protected
    // mustCapture => Useful for pawns movement, target square must not be empty and must be captured
    // canCapture => Useful for pawns movement, allow capture on the target square

    auto checkingPieces = engine->getCheckingPieces();

    // If king is checked by more than one piece, it *needs* to move out
    if (checkingPieces.size() > 1 && type != Type::KING)
        return false;

    if (!isMoveOnBoard(x, y))
        return false;

    Piece *p = engine->getPieceFromPos({(int8_t)(pos.x + x), (int8_t)(pos.y + y)});

    if (mustCapture && !p || !canMoveCapture && p)
        return false;

    if (p && !canCapture(p, allowOwnPieceAttack))
        return false;

    if (!checkingPieces.empty())
        return canStopCheck(engine, checkingPieces.front(), x, y);

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
