#pragma once

#include <string>
#include <cctype>
#include <sstream>
#include <map>
#include <list>
#include <exception>

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

    struct Position {
        std::list<Piece *>  pieces;
        char                turn = 'w';
        uint8_t             fmCounter;    

    };

    class ParserException : public std::runtime_error {
        public:
            ParserException() : std::runtime_error("invalid argument") {}
            ParserException(const std::string& what) : std::runtime_error(what) {}
            ~ParserException() throw() {}
    };

    Position            load(std::string fen);
    std::list<Piece *>  loadPieces(std::string &sPieces);
    void                loadPossibleCastles(Position *position, std::string &possibleCastles);

    Piece   *retrievePiece(std::list<Piece *> &pieces, Piece::Type t, Piece::Color c, uint8_t x = 0);
};