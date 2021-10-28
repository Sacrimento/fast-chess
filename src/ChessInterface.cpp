#include "ChessInterface.h"
#include "Piece.h"

ChessInterface::ChessInterface(const char *window_name)
{
    sAppName = window_name;
}

bool    ChessInterface::OnUserCreate()
{
    auto cellSize = CI_SCREEN_H / 8;
    auto black = olc::Pixel(54, 31, 10);
    auto white = olc::Pixel(201, 177, 135);

	boardLayer = CreateLayer();
	SetDrawTarget(boardLayer);
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            FillRect(x * cellSize, y * cellSize, cellSize, cellSize, ((x + y) % 2 ? black : white));
    EnableLayer(boardLayer, true);
    SetDrawTarget(nullptr);

    pieceLayer = CreateLayer();
    SetDrawTarget(pieceLayer);
    EnableLayer(pieceLayer, true);

    if (!loadAssets())
        return false;

    return true;
}


bool    ChessInterface::OnUserUpdate(float fElapsedTime)
{
    auto pieceScaling = ScreenHeight() / 8 / pieceSize;

    Clear(olc::BLANK);

    DrawDecal({0.0, 0.0}, pieceDecals[ Piece::Type::QUEEN | Piece::Color::BLACK ], {pieceScaling, pieceScaling});

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

    return true;
}
