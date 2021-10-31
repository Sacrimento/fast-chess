#pragma once

#include "Piece.h"

class Queen : public Piece 
{
    public:
        Queen(Color c, pos2d pos) : Piece(c, pos) { type = Type::QUEEN; }
        ~Queen() {}

        virtual int get_moves();
};
