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

class ChessEngine
{
    public:
        ChessEngine();
        ChessEngine(const char *fen);
        ~ChessEngine();

        std::list<Piece *> pieces;

        Piece   *getPieceFromPos(Piece::pos2d pos);
        Piece::Move     &getLastMove();

        void    move(Piece *piece, Piece::pos2d pos);

        void    loadFEN(std::string fen);
        static Piece    *create_piece(Piece::Type type, Piece::Color color, Piece::pos2d pos);
    
    private:
        const char *initial_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        Piece::Move    lastMove = {nullptr, {-1, -1}, nullptr};

        void cleanup();


};
