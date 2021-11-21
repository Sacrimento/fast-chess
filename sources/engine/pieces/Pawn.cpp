#include "Pawn.h"

std::list<Move>    Pawn::getMoves(ChessEngine *engine, bool allAttackedSquares)
{
    std::list<Move> moves;
    int8_t direction = (color == Color::BLACK ? 1 : -1);
    Move::Flag  promotion = (pos.y + direction == (direction == 1 ? 7 : 0) ? Move::Flag::Promotion : Move::Flag::Unset);

    if (!allAttackedSquares && isMoveLegal(engine, 0, direction, allAttackedSquares, false, false))
        moves.push_back({this, {pos.x, (int8_t)(pos.y + direction)}, engine->getPieceFromPos({pos.x, (int8_t)(pos.y + direction)}), promotion});
    if (!hasMoved && !allAttackedSquares && isMoveLegal(engine, 0, direction * 2, allAttackedSquares, false, false) && !engine->isPathObstructed(this, 0, direction, 2))
        moves.push_back({this, {pos.x, (int8_t)(pos.y + direction * 2)}, engine->getPieceFromPos({pos.x, (int8_t)(pos.y + direction * 2)})});
    if (!allAttackedSquares && checkEnPassant(engine) && isMoveLegal(engine, engine->getLastMove().pos.x - pos.x, direction, allAttackedSquares, false, false))
        moves.push_back(
        {
            this, {engine->getLastMove().pos.x, (int8_t)(pos.y + direction)},
            engine->getPieceFromPos(engine->getLastMove().pos)
        });

    //Reverse allAttackedSquares to get mustCapture arg, for move generation purposes
    if (isMoveLegal(engine, -1, direction, allAttackedSquares, !allAttackedSquares))
        moves.push_back({this, {(int8_t)(pos.x - 1), (int8_t)(pos.y + direction)}, engine->getPieceFromPos({(int8_t)(pos.x - 1), (int8_t)(pos.y + direction)}), promotion});
    if (isMoveLegal(engine, 1, direction, allAttackedSquares, !allAttackedSquares))
        moves.push_back({this, {(int8_t)(pos.x + 1), (int8_t)(pos.y + direction)}, engine->getPieceFromPos({(int8_t)(pos.x + 1), (int8_t)(pos.y + direction)}), promotion});

    return moves;
}

bool    Pawn::checkEnPassant(ChessEngine *engine)
{
    auto lastMove = engine->getLastMove();

    if (!lastMove.moving || lastMove.moving == this)
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
