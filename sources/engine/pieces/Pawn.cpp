#include "Pawn.h"

std::list<Piece::Move>    Pawn::getMoves(ChessEngine *engine)
{
    std::list<Move> moves;
    int8_t direction = color == Color::BLACK ? 1 : -1;

    if (isMoveLegal(engine, 0, direction, false, false))
        moves.push_back({this, {pos.x, (int8_t)(pos.y + direction)}, engine->getPieceFromPos({pos.x, (int8_t)(pos.y + direction)})});
    if (isMoveLegal(engine, 0, direction * 2, false, false) && !hasMoved)
        moves.push_back({this, {pos.x, (int8_t)(pos.y + direction * 2)}, engine->getPieceFromPos({pos.x, (int8_t)(pos.y + direction * 2)})});
    if (
        checkEnPassant(engine) &&
        isMoveLegal(engine, engine->getLastMove().pos.x, pos.y + direction, false, false)
    )
    {
        moves.push_back(
        {
            this, {engine->getLastMove().pos.x, (int8_t)(pos.y + direction)},
            engine->getPieceFromPos({engine->getLastMove().pos.x, engine->getLastMove().pos.y})
        });
    }

    if (isMoveLegal(engine, -1, direction, true))
        moves.push_back({this, {(int8_t)(pos.x - 1), (int8_t)(pos.y + direction)}, engine->getPieceFromPos({(int8_t)(pos.x - 1), (int8_t)(pos.y + direction)})});
    if (isMoveLegal(engine, 1, direction, true))
        moves.push_back({this, {(int8_t)(pos.x + 1), (int8_t)(pos.y + direction)}, engine->getPieceFromPos({(int8_t)(pos.x + 1), (int8_t)(pos.y + direction)})});

    //TODO: Check for promotion aswell ?

    return moves;
}

bool    Pawn::checkEnPassant(ChessEngine *engine)
{
    auto lastMove = engine->getLastMove();

    if (!lastMove.moving)
        return false;
    if (lastMove.moving->getType() != Type::PAWN ||
        !(static_cast<Pawn *>(lastMove.moving)->justJumped))
        return false;
    if (lastMove.pos.y != pos.y || std::abs(lastMove.pos.x - pos.x) > 1)
        return false;
    return true;
}

void    Pawn::move(pos2d move)
{
    justJumped = std::abs(move.y - pos.y) > 1;
    hasMoved = true;
    pos = move;
}
