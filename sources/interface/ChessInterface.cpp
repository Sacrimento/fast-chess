#include "ChessInterface.h"
#include <iostream>


ChessInterface::ChessInterface(const char *windowName)
{
    sAppName = windowName;
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

    olc::SOUND::InitialiseAudio();

    if (!loadAssets())
        return false;

    return true;
}


void    ChessInterface::drawPieces() {
    Piece::pos2d pos;
    for (auto p : engine->pieces)
    {
        if (p != selectedPiece)
        {
            pos = p->getPos();
            DrawDecal(
                {float(pos.x) * float(CELL_SIZE), float(pos.y) * float(CELL_SIZE)},
                pieceDecals[p->getPieceRepresentation()],
                {pieceScaling, pieceScaling}
            );
        }
    }
    // Draw selected piece on top of the others
    if (selectedPiece)
        DrawDecal(
            {
                MAX_BOARD(GetMouseX()) - pieceSize * pieceScaling / 2,
                MAX_BOARD(GetMouseY()) - pieceSize * pieceScaling / 2
            },
            pieceDecals[selectedPiece->getPieceRepresentation()],
            {pieceScaling, pieceScaling}
        );
}

bool    ChessInterface::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLANK);

    if (!handleUserInput())
        return false;

    drawPieces();

#if DEBUG
    drawAttackedCells();
#endif
    drawAvailableCells();

    SetDrawTarget(nullptr);

    return true;
}

bool    ChessInterface::OnUserDestroy()
{
    for (auto d: pieceDecals)
    {
        delete d.second->sprite;
        delete d.second;
    }

    olc::SOUND::DestroyAudio();

    return true;
}

bool    ChessInterface::handleUserInput()
{
    auto cell = getCellFromMouse(GetMousePos());

    if (GetMouse(0).bPressed)
        selectedPiece = engine->getPieceFromPos({(int8_t)cell.x, (int8_t)cell.y});
    else if (GetMouse(0).bReleased)
    {
        if (cell.x > 7 || cell.y > 7)
        {
            selectedPiece = nullptr;
            return true;
        }
        if (selectedPiece) {
            auto mt = engine->move(selectedPiece, {(int8_t)cell.x, (int8_t)cell.y});
            if (mt != ChessEngine::MoveType::CANCELLED)
                olc::SOUND::PlaySample(sounds[mt]);
        }
        selectedPiece = nullptr;
    }

    return true;
}

void    ChessInterface::drawAvailableCells()
{
    if (!selectedPiece || selectedPiece->getColor() != engine->getTurn() || engine->getState() != ChessEngine::State::INGAME)
        return;

    SetPixelMode(olc::Pixel::ALPHA);
    for (auto m: selectedPiece->getMoves(engine))
    {
        FillRect(
            m.pos.x * CELL_SIZE,
            m.pos.y * CELL_SIZE,
            CELL_SIZE,
            CELL_SIZE,
            olc::Pixel(219, 136, 11, 120)
        );
    }
    SetPixelMode(olc::Pixel::NORMAL);
}

void    ChessInterface::drawAttackedCells()
{
    SetPixelMode(olc::Pixel::ALPHA);
    for (auto &p: engine->getAttackedSquares())
        for (auto &pos : p.second)
            FillRect(
                pos.x * CELL_SIZE,
                pos.y * CELL_SIZE,
                CELL_SIZE,
                CELL_SIZE,
                olc::Pixel(255, 30, 30, 150)
            );
    SetPixelMode(olc::Pixel::NORMAL);
}

olc::vi2d   ChessInterface::getCellFromMouse(const olc::vi2d mousePos)
{
    return mousePos / CELL_SIZE;
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

    sounds[ChessEngine::MoveType::REGULAR] = olc::SOUND::LoadAudioSample("./assets/sounds/move.wav");
    sounds[ChessEngine::MoveType::CAPTURE] = olc::SOUND::LoadAudioSample("./assets/sounds/capture.wav");
    sounds[ChessEngine::MoveType::CHECK] = olc::SOUND::LoadAudioSample("./assets/sounds/draw.wav");

    pieceSize = pieceDecals[Piece::Type::QUEEN | Piece::Color::WHITE]->sprite->height;
    pieceScaling = ScreenHeight() / 8 / pieceSize;

    return true;
}
