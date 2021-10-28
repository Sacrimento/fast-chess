#pragma once

#include "olcPixelGameEngine.h"

#define CI_SCREEN_W 1280
#define CI_SCREEN_H 720

class ChessInterface : public olc::PixelGameEngine
{
    private:
        int     boardLayer;
        int     pieceLayer;
        float   pieceSize;
        
        std::map<uint8_t, olc::Decal *> pieceDecals;

    public:
        ChessInterface(const char *window_name);
        
        bool OnUserCreate() override;
        bool OnUserUpdate(float fElapsedTime) override;

        bool loadAssets();
};
