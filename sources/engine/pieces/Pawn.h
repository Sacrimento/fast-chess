#pragma once

#include "Piece.h"

class Pawn : public Piece 
{
    public:
        Pawn(Color c, pos2d pos) : Piece(c, pos) { type = Type::PAWN; }
        ~Pawn() {}

        virtual int get_moves();
};
