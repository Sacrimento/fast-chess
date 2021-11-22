#pragma once

#include <cstdint>
#include <list>
#include <ostream>

class ChessEngine;
struct Move;

class Piece
{
    public:

        enum Type
        {
            PAWN,
            BISHOP,
            KNIGHT,
            ROOK,
            QUEEN,
            KING,
        };

        enum Color
        {
            BLACK = 0,
            WHITE = 8
        };

        struct pos2d
        {
            int8_t x;
            int8_t y;
        };

        Piece(Color c, pos2d p) : color(c), pos(p) {}
        virtual ~Piece() {}

        virtual std::list<Move> getMoves(ChessEngine *engine, bool allAttackedSquares = false) = 0;
        pos2d   getPos() { return pos; }
        Color   getColor() { return color; }
        Type    getType() { return type; }
        uint8_t getPieceRepresentation() { return type | color; }


        virtual void    move(pos2d move) { pos = move; }

    protected:
        pos2d   pos;
        Type    type;
        Color   color;
        bool    ray = false;

        bool    isRay();
        bool    canStopCheck(ChessEngine *engine, Piece *checkingPiece, int8_t x, int8_t y);
        bool    isMoveOnBoard(int8_t x, int8_t y);
        bool    canCapture(Piece *p, bool allowOwnPieceAttack);
        bool    isMoveLegal(ChessEngine *engine, int8_t x, int8_t y, bool allowOwnPieceAttack, bool mustCatpure = false, bool canMoveCapture = true);
};

bool    operator==(const Piece::pos2d &lhs, const Piece::pos2d &rhs);
std::ostream &operator<<(std::ostream &out, const Piece::pos2d &pos);
