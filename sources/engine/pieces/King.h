#pragma once

#include "Piece.h"
#include "ChessEngine.h"

class King : public Piece
{
    public:
        King(Color c, pos2d pos) : Piece(c, pos) { type = Type::KING; }
        ~King() {}

        virtual std::list<Move> getMoves(ChessEngine *engine, bool allAttackedSquares = false);
        void    move(pos2d move) override;

        bool    canCastle = false;

    private:
        bool    checkCastle(ChessEngine *engine, int8_t xoffset);
};
