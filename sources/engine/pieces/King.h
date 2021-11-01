#pragma once

#include "Piece.h"

class King : public Piece
{
    public:
        King(Color c, pos2d pos) : Piece(c, pos) { type = Type::KING; }
        ~King() {}

        virtual std::list<pos2d> getMoves(ChessEngine *engine);
        void    move(pos2d move) override;

        bool    canCastle = true;
};
