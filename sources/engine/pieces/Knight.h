#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Knight : public Piece
{
    public:
        Knight(Color c, pos2d pos) : Piece(c, pos) { type = Type::KNIGHT; }
        ~Knight() {}

        virtual std::list<Move> getMoves(ChessEngine *engine, bool allAttackedSquares = false);
};
