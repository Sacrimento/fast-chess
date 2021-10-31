#pragma once

#include <string>
#include <list>

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
    private:
        const char *initial_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

        void cleanup();

    public:
        ChessEngine();
        ChessEngine(const char *fen);
        ~ChessEngine();

        std::list<Piece *> pieces;

        void load_FEN(std::string fen);
        static Piece *create_piece(Piece::Type type, Piece::Color color, Piece::pos2d pos);
};