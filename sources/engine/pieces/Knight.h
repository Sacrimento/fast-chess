#pragma once

#include "Piece.h"

class Knight : public Piece 
{
    public:
        Knight(Color c, pos2d pos) : Piece(c, pos) { type = Type::KNIGHT; }
        ~Knight() {}

        virtual int get_moves();
};
