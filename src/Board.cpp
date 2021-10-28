#include "Board.h"

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

uint8_t Board::get(uint8_t x, uint8_t y)
{
    return board[y * 8 + x];
}

void    Board::set(uint8_t x, uint8_t y, uint8_t val)
{
    board[y * 8 + x] = val;
}

void    Board::loadFEN(std::string &fen)
{
    //TODO: Check for user input because user is evil
    std::memset(board, 0, sizeof(board));

}
