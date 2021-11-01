#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Bishop : public Piece
{
    public:
        Bishop(Color c, pos2d pos) : Piece(c, pos) { type = Type::BISHOP; }
        ~Bishop() {}

        virtual std::list<pos2d> getMoves(ChessEngine *engine);
};
