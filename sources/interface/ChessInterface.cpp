#include "ChessInterface.h"

ChessInterface::ChessInterface(const char *window_name)
{
    sAppName = window_name;
}

bool    ChessInterface::OnUserCreate()
{
    auto black = olc::Pixel(179, 92, 45);
    auto white = olc::Pixel(255, 223, 186);

    boardLayer = CreateLayer();
    SetDrawTarget(boardLayer);

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            FillRect(
                x * CELL_SIZE,
                y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE,
                ((x + y) % 2 ? black : white)
            );

    EnableLayer(boardLayer, true);
    SetDrawTarget(nullptr);

    pieceLayer = CreateLayer();
    SetDrawTarget(pieceLayer);
    EnableLayer(pieceLayer, true);

    if (!loadAssets())
        return false;

    return true;
}


void    ChessInterface::drawPiece(Piece::pos2d pos, uint8_t piece) {
    if (
        piece != (Piece::Type::UNSET | Piece::Color::BLACK)
        && piece != (Piece::Type::UNSET | Piece::Color::WHITE)
    ) 
    {
        DrawDecal(
            {float(pos.x) * float(CELL_SIZE), float(pos.y) * float(CELL_SIZE)},
            pieceDecals[piece],
            {pieceScaling, pieceScaling}
        );
    }
}

void    ChessInterface::drawBoard() {
    for (auto p : engine->pieces)
        drawPiece(p->getPos(), p->getPieceRepresentation());
}


bool    ChessInterface::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLANK);

    drawBoard();

    SetDrawTarget(nullptr);

    return true;
}

bool    ChessInterface::loadAssets()
{
    olc::Sprite *sprite;

    ALLOC_SPRITE("./assets/chess.com/wpawn.png", Piece::Type::PAWN | Piece::Color::WHITE)
    ALLOC_SPRITE("./assets/chess.com/bpawn.png", Piece::Type::PAWN | Piece::Color::BLACK)
    ALLOC_SPRITE("./assets/chess.com/wbishop.png", Piece::Type::BISHOP | Piece::Color::WHITE)
    ALLOC_SPRITE("./assets/chess.com/bbishop.png", Piece::Type::BISHOP | Piece::Color::BLACK)
    ALLOC_SPRITE("./assets/chess.com/wknight.png", Piece::Type::KNIGHT | Piece::Color::WHITE)
    ALLOC_SPRITE("./assets/chess.com/bknight.png", Piece::Type::KNIGHT | Piece::Color::BLACK)
    ALLOC_SPRITE("./assets/chess.com/wrook.png", Piece::Type::ROOK | Piece::Color::WHITE)
    ALLOC_SPRITE("./assets/chess.com/brook.png", Piece::Type::ROOK | Piece::Color::BLACK)
    ALLOC_SPRITE("./assets/chess.com/wqueen.png", Piece::Type::QUEEN | Piece::Color::WHITE)
    ALLOC_SPRITE("./assets/chess.com/bqueen.png", Piece::Type::QUEEN | Piece::Color::BLACK)
    ALLOC_SPRITE("./assets/chess.com/wking.png", Piece::Type::KING | Piece::Color::WHITE)
    ALLOC_SPRITE("./assets/chess.com/bking.png", Piece::Type::KING | Piece::Color::BLACK)

    pieceSize = pieceDecals[Piece::Type::QUEEN | Piece::Color::WHITE]->sprite->height;
    pieceScaling = ScreenHeight() / 8 / pieceSize;

    return true;
}
