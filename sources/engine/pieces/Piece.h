#pragma once

#include <cstdint>
#include <list>
#include <ostream>

class ChessEngine;

class Piece
{
    public:

        enum Type
        {
            UNSET = 0,
            PAWN = 1,
            BISHOP = 2,
            KNIGHT = 3,
            ROOK = 4,
            QUEEN = 5,
            KING = 6,
        };

        enum Color
        {
            BLACK = 0,
            WHITE = 8
        };

        struct pos2d
        {
            uint8_t x;
            uint8_t y;
        };


        Piece(Color c, pos2d p) : color(c), pos(p) {}
        virtual ~Piece() {}

        virtual std::list<pos2d> getMoves(ChessEngine *engine) = 0;
        pos2d   getPos() { return pos; }
        uint8_t getColor() { return color; }
        uint8_t getPieceRepresentation() { return type | color; }

        virtual void    move(pos2d move) { pos = move; }

    protected:
        pos2d   pos;
        Type    type;
        Color   color;
};

bool    operator==(const Piece::pos2d &lhs, const Piece::pos2d &rhs);
std::ostream &operator<<(std::ostream &out, const Piece::pos2d &pos);
