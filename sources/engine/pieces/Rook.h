#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Rook : public Piece
{
    public:
        Rook(Color c, pos2d pos) : Piece(c, pos) { type = Type::ROOK; }
        ~Rook() {}

        virtual std::list<Move>    getMoves(ChessEngine *engine);
        void    move(pos2d move) override;

        bool canCastle = false;
};
