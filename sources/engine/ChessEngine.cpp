#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
    loadFEN(initial_pos);
}

ChessEngine::ChessEngine(const char *fen)
{
    loadFEN(fen);
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

Piece *ChessEngine::createPiece(Piece::Type type, Piece::Color color, Piece::pos2d pos)
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

Move   &ChessEngine::getLastMove()
{
    return lastMove;
}

Piece::Color    ChessEngine::getTurn()
{
    return turn;
}

bool    ChessEngine::isPathObstructed(Piece *piece, int8_t incx, int8_t incy, uint8_t iterations)
{
    uint8_t i = 0;
    int8_t x = piece->getPos().x;
    int8_t y = piece->getPos().y;

    while (i < iterations)
    {
        x += incx;
        y += incy;
        if (getPieceFromPos({x, y}))
            return true;
        i++;
    }
    return false;
}

void    ChessEngine::move(Piece *piece, Piece::pos2d pos)
{
    if (piece->getColor() != turn)
        return;

    auto moves = piece->getMoves(this);
    std::list<Move>::const_iterator m;

    if ((m = std::find_if(moves.cbegin(), moves.cend(),
        [pos] (const Move &m) { return m.pos == pos; })) == moves.end())
        return;

    std::cout << "Move : from " << m->moving->getPos() << " to " << m->pos << " (delete " << m->captured << ")\n";

    if (m->flag == Move::Flag::Castle)
        handleRookAfterCastle(*m);

    if (m->captured) {
        pieces.remove(m->captured);
        delete m->captured;
    }

    if (m->flag != Move::Flag::Promotion)
        piece->move(pos);
    else
    {
        pieces.remove(m->moving);
        pieces.push_back(createPiece(promotionType, m->moving->getColor(), m->pos));
        delete m->moving;
    }

    turn = (Piece::Color)(Piece::Color::WHITE - turn); // Flips turn between BLACK and WHITE thanks to their numeric values
    lastMove = *m;
}

void ChessEngine::loadFEN(std::string fen)
{
    cleanup();
    FEN::Position   position;

    try {
        position = FEN::load(fen);
    } catch (FEN::ParserException &e) {
        std::cerr << "Could not parse FEN : " << e.what() << std::endl;
    };

    pieces = position.pieces;
    turn = (position.turn == 'w' ? Piece::Color::WHITE : Piece::Color::BLACK);
}

void ChessEngine::setPromotionType(Piece::Type t)
{
    promotionType = t;
}

void ChessEngine::handleRookAfterCastle(const Move &m)
{
    auto kingx = m.pos.x - m.moving->getPos().x;
    auto targetx = m.pos.x + (kingx > 0 ? -1 : 1);
    auto rook = getPieceFromPos({(int8_t)(kingx > 0 ? 7 : 0), m.pos.y});

    rook->move({(int8_t)targetx, m.pos.y});
}
