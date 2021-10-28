# pragma once

class Piece
{
    public:

        enum Type
        {
            PAWN = 0,
            BISHOP = 1,
            KNIGHT = 2,
            ROOK = 3,
            QUEEN = 4,
            KING = 5,
        };

        enum Color
        {
            BLACK = 0,
            WHITE = 8
        };
};
