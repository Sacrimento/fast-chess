#include "fen.h"

FEN::Position   FEN::load(std::string fen)
{
    std::istringstream fenstream(fen);
    std::string part;
    FEN::Position position;

    std::getline(fenstream, part, ' ');
    position.pieces = FEN::loadPieces(part);

    std::getline(fenstream, part, ' ');
    if (part.size() != 1 || (part != "w" && part != "b"))
        throw FEN::ParserException("invalid turn character");
    position.turn = part[0];

    return position;
}

std::list<Piece *>  FEN::loadPieces(std::string &sPieces)
{
    int8_t row = 0, column = 0;

    std::list<Piece *> pieces;

    for (char &c : sPieces) {
        if (c == '/') {
            ++row;
            if (row >= 8)
                return pieces;
            column = 0;
        }
        else if (std::isdigit(c))
            column += (int(c) - 48);
        else if (FEN::fenPieces.find(c) != std::string::npos) {
            pieces.push_back(
                ChessEngine::createPiece(
                    FEN::pieceMap.at(std::tolower(c)),
                    (std::isupper(c) ? Piece::Color::WHITE : Piece::Color::BLACK),
                    {column, row}
                )
            );
            ++column;
        }
        else
            throw FEN::ParserException(std::string("invalid piece type : ") + c);
    }
    return pieces;
}
