#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Pawn : public Piece
{
    public:
        Pawn(Color c, pos2d pos) : Piece(c, pos) { type = Type::PAWN; }
        ~Pawn() {}

        virtual std::list<Move> getMoves(ChessEngine *engine, bool allAttackedSquares = false);
        void    move(pos2d move);

    private:
        bool    hasMoved = false;
        bool    justJumped = false;

        bool    checkEnPassant(ChessEngine *engine);
};
