#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Queen : public Piece
{
    public:
        Queen(Color c, pos2d pos) : Piece(c, pos) { type = Type::QUEEN; ray = true;}
        ~Queen() {}

        virtual std::list<Move> getMoves(ChessEngine *engine, bool allAttackedSquares = false);
};
