#pragma once

#include "Piece.h"

class Rook : public Piece 
{
    public:
        Rook(Color c, pos2d pos) : Piece(c, pos) { type = Type::ROOK; }
        ~Rook() {}

        virtual int get_moves();
};
