#include <string>
#include <iostream>
#include "ChessInterface.h"
#include "Piece.h"
#include "Board.h"

std::string initial_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

ChessInterface::ChessInterface(const char *window_name)
{
    sAppName = window_name;
    board.loadFEN(initial_pos);
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


void    ChessInterface::DrawPiece(int row, int column, uint8_t piece) {
    if (
        piece != (Piece::Type::UNSET | Piece::Color::BLACK)
        && piece != (Piece::Type::UNSET | Piece::Color::WHITE)
    ) {
        DrawDecal(
            {float(column)* float(CELL_SIZE), float(row) * float(CELL_SIZE)},
            pieceDecals[piece],
            {pieceScaling, pieceScaling}
        );
    }
}

void    ChessInterface::DrawBoard() {
    for (uint8_t x = 0 ; x < 8 ; x++)
        for (uint8_t y = 0 ; y < 8 ; y++)
            DrawPiece(x, y, board.get(y, x));
}


bool    ChessInterface::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLANK);

    DrawBoard();

    SetDrawTarget(nullptr);

    return true;
}

bool    ChessInterface::loadAssets()
{
    olc::Sprite *sprite;
    olc::Decal  *decal;

    sprite = new olc::Sprite("./assets/default_pieces/wpawn.png");
    pieceDecals[Piece::Type::PAWN | Piece::Color::WHITE] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/bpawn.png");
    pieceDecals[Piece::Type::PAWN | Piece::Color::BLACK] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/wbishop.png");
    pieceDecals[Piece::Type::BISHOP | Piece::Color::WHITE] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/bbishop.png");
    pieceDecals[Piece::Type::BISHOP | Piece::Color::BLACK] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/wknight.png");
    pieceDecals[Piece::Type::KNIGHT | Piece::Color::WHITE] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/bknight.png");
    pieceDecals[Piece::Type::KNIGHT | Piece::Color::BLACK] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/wrook.png");
    pieceDecals[Piece::Type::ROOK | Piece::Color::WHITE] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/brook.png");
    pieceDecals[Piece::Type::ROOK | Piece::Color::BLACK] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/wqueen.png");
    pieceDecals[Piece::Type::QUEEN | Piece::Color::WHITE] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/bqueen.png");
    pieceDecals[Piece::Type::QUEEN | Piece::Color::BLACK] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/wking.png");
    pieceDecals[Piece::Type::KING | Piece::Color::WHITE] = new olc::Decal(sprite);

    sprite = new olc::Sprite("./assets/default_pieces/bking.png");
    pieceDecals[Piece::Type::KING | Piece::Color::BLACK] = new olc::Decal(sprite);

    pieceSize = pieceDecals[Piece::Type::QUEEN | Piece::Color::WHITE]->sprite->height;
    pieceScaling = ScreenHeight() / 8 / pieceSize;

    return true;
}
