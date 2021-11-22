#pragma once

#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"

#include "ChessEngine.h"

#define DEBUG 0

#define CI_SCREEN_W 1280
#define CI_SCREEN_H 720
#define CELL_SIZE (CI_SCREEN_H / 8)

#define MAX_BOARD(x) (x > CI_SCREEN_H ? CI_SCREEN_H : x)
#define ALLOC_SPRITE(path, key) sprite = new olc::Sprite(path); pieceDecals[key] = new olc::Decal(sprite);

class ChessInterface : public olc::PixelGameEngine
{
    private:
        int     boardLayer;
        int     pieceLayer;
        float   pieceSize;
        float   pieceScaling;

        Piece   *selectedPiece = nullptr;

        ChessEngine *engine = nullptr;

        std::map<ChessEngine::MoveType, int>    sounds;
        std::map<uint8_t, olc::Decal *>         pieceDecals;

        bool    OnUserCreate() override;
        bool    OnUserUpdate(float fElapsedTime) override;
        bool    OnUserDestroy() override;

        bool    loadAssets();

        bool    handleUserInput();
        olc::vi2d   getCellFromMouse(const olc::vi2d mousePos);

        void    drawPieces();
        void    drawAvailableCells();
        void    drawAttackedCells();

    public:
        ChessInterface(const char *window_name);

        void setEngine(ChessEngine *e) { engine = e; }
};
