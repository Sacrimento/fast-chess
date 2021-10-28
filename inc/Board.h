#pragma once

#include <string>
#include <cstring>

#include "Piece.h"

class Board
{
    private:
        uint8_t board[64];

    public:
        Board();
        Board(std::string &fen);
        ~Board();

        void    loadFEN(std::string &fen);
        uint8_t get(uint8_t x, uint8_t y);
        void    set(uint8_t x, uint8_t y, uint8_t val);
        uint8_t get_piece_from_char(char c);
        bool    is_chess_piece(char &c);
};
