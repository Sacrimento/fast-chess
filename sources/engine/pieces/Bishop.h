#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Bishop : public Piece
{
    public:
        Bishop(Color c, pos2d pos) : Piece(c, pos) { type = Type::BISHOP; ray = true; }
        ~Bishop() {}

        virtual std::list<Move> getMoves(ChessEngine *engine, bool allAttackedSquares = false);
};
