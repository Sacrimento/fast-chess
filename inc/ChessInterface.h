#pragma once

#include "olcPixelGameEngine.h"
#include "Board.h"

#define CI_SCREEN_W 1280
#define CI_SCREEN_H 720
#define CELL_SIZE CI_SCREEN_H / 8

class ChessInterface : public olc::PixelGameEngine
{
    private:
        Board   board;
        int     boardLayer;
        int     pieceLayer;
        float   pieceSize;
        float   pieceScaling;

        std::map<uint8_t, olc::Decal *> pieceDecals;

    public:
        ChessInterface(const char *window_name);

        bool OnUserCreate() override;
        bool OnUserUpdate(float fElapsedTime) override;
        void DrawBoard();
        void DrawPiece(int row, int column, uint8_t piece);

        bool loadAssets();
};
