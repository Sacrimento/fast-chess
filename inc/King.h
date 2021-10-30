#pragma once

#include "Piece.h"

class King : public Piece 
{
    public:
        King(Color c, pos2d pos) : Piece(c, pos) { type = Type::KING; }
        ~King() {}

        virtual int get_moves();
};
