#include "fen.h"

bool    FEN::isChessPiece(char &c) {
    return fenPieces.find(c) != std::string::npos;
}

std::list<Piece *>  FEN::load(std::string fen)
{
    //TODO: Check for user input because user is evil
    uint8_t row = 0, column = 0, nb_spaces = 0;

    std::list<Piece *> pieces;

    for (char &c : fen) {
        if (c == '/') {
            ++row;
            if (row >= 8)
                return pieces;
            column = 0;
        }
        else if (std::isdigit(c))
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
        else if (FEN::isChessPiece(c) && !nb_spaces) {
            pieces.push_back(
                ChessEngine::create_piece(
                    pieceMap.at(std::tolower(c)),
                    (std::isupper(c) ? Piece::Color::WHITE : Piece::Color::BLACK),
                    {column, row} 
                )
            );
            ++column;
        }
    }
    return pieces;
}
