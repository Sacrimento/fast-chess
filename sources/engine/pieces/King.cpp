#include "King.h"

std::list<Move>    King::getMoves(ChessEngine *engine)
{
    std::list<Move> moves;
    Piece *target = nullptr;

    for (int8_t xmove : {-1, 1, 0}) {
        for (int8_t ymove : {-1, 1, 0}) {
            if (isMoveLegal(engine, xmove, ymove)) {
                target = engine->getPieceFromPos({(int8_t)(pos.x + xmove), (int8_t)(pos.y + ymove)});
                if (target)
                { /* TODO: Check if capture is possible, king can't take a protected piece */ }
                moves.push_back({
                    this,
                    {
                        (int8_t)(pos.x + xmove),
                        (int8_t)(pos.y + ymove)
                    },
                    target
                });
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

    if (!piece || piece->getType() != Type::ROOK)
        return false;
    if (!static_cast<Rook *>(piece)->canCastle)
        return false;
    if (engine->isPathObstructed(this, (xoffset > 0 ? 1 : -1), 0, std::abs(xoffset) - 1))
        return false;
    // TODO: Check if king goes through check
    return true;
}

void    King::move(pos2d move)
{
    pos = move;
    canCastle = false;
}
