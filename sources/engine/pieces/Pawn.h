#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Pawn : public Piece
{
    public:
        Pawn(Color c, pos2d pos) : Piece(c, pos) { type = Type::PAWN; }
        ~Pawn() {}

        virtual std::list<pos2d> getMoves(ChessEngine *engine);
        bool    isMoveLegal(int tx, int ty);
        void    move(pos2d move);
    
    private:
        bool    hasMoved = false;
};
