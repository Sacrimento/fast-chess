#pragma once

#include "Piece.h"

class Bishop : public Piece 
{
    public:
        Bishop(Color c, pos2d pos) : Piece(c, pos) { type = Type::BISHOP; }
        ~Bishop() {}

        virtual int get_moves();
};
