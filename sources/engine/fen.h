#pragma once

#include <string>
#include <cctype>
#include <map>
#include <list>

#include "Piece.h"
#include "ChessEngine.h"

namespace FEN
{
    static const std::map<char, Piece::Type> pieceMap = {
        {'r', Piece::Type::ROOK},
        {'n', Piece::Type::KNIGHT},
        {'b', Piece::Type::BISHOP},
        {'q', Piece::Type::QUEEN},
        {'k', Piece::Type::KING},
        {'p', Piece::Type::PAWN},
    };
    static const std::string fenPieces = "rnbqkpRNBQKP";

    std::list<Piece *>  load(std::string fen);
    bool                isChessPiece(char &c);
};