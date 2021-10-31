#pragma once

#include "olcPixelGameEngine.h"

#include "ChessEngine.h"

#define CI_SCREEN_W 1280
#define CI_SCREEN_H 720
#define CELL_SIZE CI_SCREEN_H / 8

#define ALLOC_SPRITE(path, key) sprite = new olc::Sprite(path); pieceDecals[key] = new olc::Decal(sprite);

class ChessInterface : public olc::PixelGameEngine
{
    private:
        int     boardLayer;
        int     pieceLayer;
        float   pieceSize;
        float   pieceScaling;

        ChessEngine *engine = nullptr;

        std::map<uint8_t, olc::Decal *> pieceDecals;

    public:
        ChessInterface(const char *window_name);

        bool OnUserCreate() override;
        bool OnUserUpdate(float fElapsedTime) override;
        bool OnUserDestroy() override;

        void drawBoard();
        void drawPiece(Piece::pos2d pos, uint8_t piece);

        bool loadAssets();

        void setEngine(ChessEngine *e) { engine = e; }
};
