#include <map>
#include <iostream>

#include "Board.h"

std::map<char, int> fen_piece_map = {
    {'r', Piece::Type::ROOK},
    {'n', Piece::Type::KNIGHT},
    {'b', Piece::Type::BISHOP},
    {'q', Piece::Type::QUEEN},
    {'k', Piece::Type::KING},
    {'p', Piece::Type::PAWN},
};
const std::string fen_pieces = "rnbqkpRNBQKP";

Board::Board()
{
    std::memset(board, 0, sizeof(board));
}

Board::Board(std::string &fen)
{
    std::memset(board, 0, sizeof(board));
    loadFEN(fen);
}

Board::~Board()
{
}

// x = column / y = row
uint8_t Board::get(uint8_t x, uint8_t y)
{
    return board[y * 8 + x];
}

// x = column / y = row
void    Board::set(uint8_t x, uint8_t y, uint8_t val)
{
    board[y * 8 + x] = val;
}


uint8_t Board::get_piece_from_char(char c) {
    uint8_t color = Piece::Color::BLACK;
    if (c <= 90) {
        color = Piece::Color::WHITE;
        c += 32;
    }
    return fen_piece_map[c] | color;
}

bool    Board::is_chess_piece(char &c) {
    return fen_pieces.find(c) != std::string::npos;
}


void    Board::loadFEN(std::string &fen)
{
    //TODO: Check for user input because user is evil
    int row = 0;
    int column = 0;
    int nb_spaces = 0;

    std::memset(board, 0, sizeof(board));
    for (char &c : fen) {
        if (c == '/') {
            ++row;
            if (row >= 8)
                std::cerr << "ALLO C PAS BON LE FEN LA" << std::endl;
            column = 0;
        }
        else if (c >= '1' && c <= '8')
            column += (int(c) - 48);
        else if (c == ' ') {
            if (nb_spaces == 0)
                // Player turn : 'w' = white / 'b' = black
                {;}
            else if (nb_spaces == 1)
                /*
                 *  Possibles rocks:
                 *  K = White rock from king side
                 *  Q = White rock from queen side
                 *  k = Black rock from king side
                 *  q = Black rock from queen side
                 */
                {;}
            else if (nb_spaces == 2)
                // Possible en passant
                {;}
            else if (nb_spaces == 3)
                // Half moves??
                {;}
            else if (nb_spaces == 4)
                // Full moves
                {;}
            ++nb_spaces;
        }
        else if (is_chess_piece(c)) {
            set(column, row, get_piece_from_char(c));
            ++column;
        }
    }

}
