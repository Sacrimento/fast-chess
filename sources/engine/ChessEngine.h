#pragma once

#include <string>
#include <list>
#include <algorithm>
#include <utility>
#include <iostream>

#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

#include "fen.h"

struct Move {
    enum Flag {
        Unset,
        Castle,
        Promotion,
    };

    Piece           *moving;
    Piece::pos2d    pos;
    Piece           *captured = nullptr;
    Flag            flag = Unset;
};

class ChessEngine
{
    public:

        enum State {
            INGAME,
            PAUSED,
            DRAW,
            W_WIN,
            B_WIN,
        };

        enum MoveType {
            CANCELLED,
            REGULAR,
            CHECK,
            CAPTURE,
        };

        ChessEngine();
        ChessEngine(const char *fen);
        ~ChessEngine();

        std::list<Piece *> pieces;

        void    setPromotionType(Piece::Type t);

        Piece           *getPieceFromPos(Piece::pos2d pos);
        Move            &getLastMove();
        State           getState() { return state; }
        Piece::Color    getTurn();
        std::list<Piece *>  &getCheckingPieces();
        std::map<Piece *, std::list<Piece::pos2d>>  &getAttackedSquares();

        MoveType    move(Piece *piece, Piece::pos2d pos);
        bool        isPathObstructed(Piece *piece, int8_t incx, int8_t incy, uint8_t iterations);
        bool        isSquareAttacked(Piece::pos2d &pos);

        void        loadFEN(std::string fen);
        static Piece    *createPiece(Piece::Type type, Piece::Color color, Piece::pos2d pos);

    private:
        const char      *initial_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        std::map<Piece *, std::list<Piece::pos2d>> attackedSquares;
        std::list<Piece *>  checkingPieces;
        Move            lastMove = {nullptr, {-1, -1}, nullptr};
        Piece::Type     promotionType = Piece::Type::QUEEN;
        Piece::Color    turn;
        State           state = INGAME;
        uint8_t         fmCounter; //"fifty-move"

        void handleRookAfterCastle(const Move &m);
        void updateEnemyKingStatus();

        void computeAttackedSquares();

        void cleanup();

};
