#include "King.h"

std::list<Move>    King::getMoves(ChessEngine *engine, bool allAttackedSquares)
{
    std::list<Move> moves;
    Piece *target = nullptr;
    auto attacked = engine->getAttackedSquares();
    pos2d targetSquare;

    for (int8_t xmove : {-1, 1, 0}) {
        for (int8_t ymove : {-1, 1, 0}) {
            if (xmove == 0 && ymove == 0)
                continue;
            targetSquare = { (int8_t)(pos.x + xmove), (int8_t)(pos.y + ymove) };
            if (isMoveLegal(engine, xmove, ymove, allAttackedSquares) && !engine->isSquareAttacked(targetSquare))
            {
                target = engine->getPieceFromPos({(int8_t)(pos.x + xmove), (int8_t)(pos.y + ymove)});
                moves.push_back({this, targetSquare, target});
            }
        }
    }

    if (canCastle)
    {
        for (auto rookOffset : {-4, 3})
            if (checkCastle(engine, rookOffset))
                moves.push_back({
                    this,
                    {
                        (int8_t)(pos.x + (rookOffset > 0 ? 2 : -2)),
                        pos.y
                    },
                    nullptr,
                    Move::Flag::Castle
                });
    }

    return moves;
}

bool    King::checkCastle(ChessEngine *engine, int8_t xoffset)
{
    auto piece = engine->getPieceFromPos({(int8_t)(pos.x + xoffset), pos.y});
    pos2d p;

    if (!piece || piece->getType() != Type::ROOK)
        return false;
    if (!static_cast<Rook *>(piece)->canCastle)
        return false;
    if (engine->isPathObstructed(this, (xoffset > 0 ? 1 : -1), 0, std::abs(xoffset) - 1))
        return false;
    for (int8_t i = (xoffset > 0 ? 1 : -1); i < std::abs(xoffset); (xoffset > 0 ? ++i : --i))
    {
        p = {(int8_t)(pos.x + i), pos.y};
        if (engine->isSquareAttacked(p))
            return false;
    }
    return true;
}

void    King::move(pos2d move)
{
    pos = move;
    canCastle = false;
}
