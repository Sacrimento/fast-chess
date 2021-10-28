# pragma once

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
};
