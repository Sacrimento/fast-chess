#pragma once

#include <string>
#include <list>
#include <algorithm>
#include <utility>

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
        ChessEngine();
        ChessEngine(const char *fen);
        ~ChessEngine();

        std::list<Piece *> pieces;

        void    setPromotionType(Piece::Type t);

        Piece   *getPieceFromPos(Piece::pos2d pos);
        Move    &getLastMove();

        void    move(Piece *piece, Piece::pos2d pos);
        bool    isPathObstructed(Piece *piece, int8_t incx, int8_t incy, uint8_t iterations);

        void    loadFEN(std::string fen);
        static Piece    *createPiece(Piece::Type type, Piece::Color color, Piece::pos2d pos);

    private:
        const char  *initial_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        Move        lastMove = {nullptr, {-1, -1}, nullptr};
        Piece::Type promotionType = Piece::Type::QUEEN;

        void handleRookAfterCastle(const Move &m);

        void cleanup();


};
