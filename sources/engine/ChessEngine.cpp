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

    attackedSquares.clear();

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

std::map<Piece *, std::list<Piece::pos2d>> &ChessEngine::getAttackedSquares()
{
    return attackedSquares;
}

std::list<Piece *>  &ChessEngine::getCheckingPieces()
{
    return checkingPieces;
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

ChessEngine::MoveType   ChessEngine::move(Piece *piece, Piece::pos2d pos)
{
    if (piece->getColor() != turn || state != State::INGAME)
        return MoveType::CANCELLED;

    auto moves = piece->getMoves(this);
    std::list<Move>::const_iterator m;

    if ((m = std::find_if(moves.cbegin(), moves.cend(),
        [pos] (const Move &m) { return m.pos == pos; })) == moves.end())
        //Move illegal
        return MoveType::CANCELLED;

    if (m->flag == Move::Flag::Castle)
        handleRookAfterCastle(*m);

    if (m->captured) {
        pieces.remove(m->captured);
        delete m->captured;
        fmCounter = 0;
    }

    if (m->flag != Move::Flag::Promotion) {
        piece->move(pos);
        fmCounter = piece->getType() != Piece::Type::PAWN ? fmCounter + 1 : 0;
    }
    else
    {
        pieces.remove(m->moving);
        pieces.push_back(createPiece(promotionType, m->moving->getColor(), m->pos));
        delete m->moving;
        fmCounter = 0;
    }

    if (fmCounter == 50)
        state = DRAW;

    // Compute attacked squares by the player that just moved
    computeAttackedSquares();
    turn = (Piece::Color)(Piece::Color::WHITE - turn); // Flips turn between BLACK and WHITE thanks to their numeric values
    // Check if the enemy King is in check
    updateEnemyKingStatus();
    lastMove = *m;

    if (!checkingPieces.empty())
        return MoveType::CHECK;

    return (lastMove.captured ? MoveType::CAPTURE : MoveType::REGULAR);
}

void ChessEngine::updateEnemyKingStatus()
{
    checkingPieces.clear();
    Piece *king = *std::find_if(pieces.begin(), pieces.end(), [this] (Piece *p) { return p->getPieceRepresentation() == (Piece::Type::KING | turn);});

    for (auto &p : attackedSquares)
        if (std::find_if(p.second.cbegin(), p.second.cend(), [king] (const Piece::pos2d &pos) { return king->getPos() == pos; }) != p.second.cend())
            checkingPieces.push_back(p.first);
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
    fmCounter = position.fmCounter;
}

void ChessEngine::computeAttackedSquares()
{
    attackedSquares.clear();

    for (auto &p : pieces)
    {
        std::list<Piece::pos2d> attacked;
        if (p->getColor() != turn)
            continue;
        for (auto &m : p->getMoves(this, true))
            attacked.push_back(m.pos);
        attackedSquares.insert({p, attacked});
    }
}

bool ChessEngine::isSquareAttacked(Piece::pos2d &pos)
{
    for (auto &a : attackedSquares)
        if (std::find_if(a.second.cbegin(), a.second.cend(), [pos] (const Piece::pos2d &p) { return p == pos; }) != a.second.cend())
            return true;
    return false;
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
