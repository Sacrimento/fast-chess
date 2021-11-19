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

    std::getline(fenstream, part, ' ');
    FEN::loadPossibleCastles(&position, part);

    return position;
}

Piece   *FEN::retrievePiece(std::list<Piece *> &pieces, Piece::Type t, Piece::Color c, uint8_t x)
{
    for (auto &p : pieces)
        if (p->getColor() == c && p->getType() == t && (t == Piece::Type::KING || p->getPos().x == x))
            return p;
    throw FEN::ParserException("illegal castle instruction");
}

void    FEN::loadPossibleCastles(FEN::Position *position, std::string &possibleCastles)
{
    std::list<Piece *>::iterator p;
    Piece::Color    color;

    if (possibleCastles == "-")
        return;

    for (auto &c : possibleCastles)
    {
        if (std::tolower(c) != 'k' && std::tolower(c) != 'q')
            throw FEN::ParserException("invalid castle character");
        color = (std::islower(c) ? Piece::Color::BLACK : Piece::Color::WHITE);
        static_cast<King *>(FEN::retrievePiece(position->pieces, Piece::Type::KING, color))->canCastle = true;
        static_cast<Rook *>(FEN::retrievePiece(position->pieces, Piece::Type::ROOK, color, (std::tolower(c) == 'k' ? 7 : 0)))->canCastle = true;
    }
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
