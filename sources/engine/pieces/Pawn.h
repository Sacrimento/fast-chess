#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class Pawn : public Piece
{
    public:
        Pawn(Color c, pos2d pos) : Piece(c, pos) { type = Type::PAWN; }
        ~Pawn() {}

        virtual bool canCapture(Piece *p) override;
        virtual std::list<Move> getMoves(ChessEngine *engine);
        void    move(pos2d move);

    private:
        bool    hasMoved = false;
        bool    justJumped = false;

        bool    checkEnPassant(ChessEngine *engine);
};
