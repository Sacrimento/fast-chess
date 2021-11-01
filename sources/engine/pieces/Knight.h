#pragma once

#include "Piece.h"

class Knight : public Piece
{
    public:
        Knight(Color c, pos2d pos) : Piece(c, pos) { type = Type::KNIGHT; }
        ~Knight() {}

        virtual std::list<pos2d> getMoves(ChessEngine *engine);
};
