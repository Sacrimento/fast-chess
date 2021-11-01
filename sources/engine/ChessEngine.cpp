#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
    load_FEN(initial_pos);
}

ChessEngine::ChessEngine(const char *fen)
{
    load_FEN(fen);
}

ChessEngine::~ChessEngine()
{
    cleanup();
}

void ChessEngine::cleanup()
{
    // Clean every state of the game

    for (auto &p: pieces)
        delete p;
}

Piece *ChessEngine::create_piece(Piece::Type type, Piece::Color color, Piece::pos2d pos)
{
    switch (type)
    {
        case Piece::Type::PAWN: return new Pawn(color, pos);
        case Piece::Type::BISHOP: return new Bishop(color, pos);
        case Piece::Type::KNIGHT: return new Knight(color, pos);
        case Piece::Type::ROOK: return new Rook(color, pos);
        case Piece::Type::QUEEN: return new Queen(color, pos);
        case Piece::Type::KING: return new King(color, pos);
        default: return nullptr;
    }
}

Piece   *ChessEngine::getPieceFromPos(Piece::pos2d pos)
{
    for (auto p: pieces)
        if (p->getPos() == pos)
            return p;
    return nullptr;
}

void    ChessEngine::move(Piece *piece, Piece::pos2d pos)
{
    auto target = getPieceFromPos(pos);

    // Check if move is legal, can capture, etc

    if (target)
    {
        if (piece == target || piece->getColor() == target->getColor())
            return;
        pieces.remove(target);
        delete target;
    }

    piece->setPos(pos);

}

void ChessEngine::load_FEN(std::string fen)
{
    cleanup();
    pieces = FEN::load(fen);
}

bool    operator==(const Piece::pos2d &lhs, const Piece::pos2d &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
