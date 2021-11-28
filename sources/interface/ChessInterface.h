#pragma once

#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"

#include "ChessEngine.h"

#define DEBUG 0

#define CI_SCREEN_W 1280
#define CI_SCREEN_H 720
#define MARGIN_H    40
#define MARGIN_W    40
#define BOARD_H (CI_SCREEN_H - 2*MARGIN_H)
#define CELL_SIZE (BOARD_H/ 8)

#define MAX_BOARD(x) (x > BOARD_H ? BOARD_H : x)
#define ALLOC_SPRITE(path, key) sprite = new olc::Sprite(path); pieceDecals[key] = new olc::Decal(sprite);



class ChessInterface : public olc::PixelGameEngine
{
    public:
        struct ButtonInfo {
            uint8_t posx;
            uint8_t posy;
            uint8_t sizex;
            uint8_t sizey;
            //int color = {0,0,0};
        };

        struct Button {

            ButtonInfo  bInfo;
            bool        isShown = False;
            void        (*buttonFct)();

        };

        ChessInterface(const char *window_name);

        void setEngine(ChessEngine *e) { engine = e; }

    private:


        int     boardLayer;
        int     pieceLayer;
        int     buttonLayer;

        float   pieceSize;
        float   pieceScaling;

        Piece   *selectedPiece = nullptr;

        ChessEngine *engine = nullptr;

        std::map<ChessEngine::MoveType, int>    sounds;
        std::map<uint8_t, olc::Decal *>         pieceDecals;
        std::map<std::string, Button>           buttons;

        bool    OnUserCreate() override;
        bool    OnUserUpdate(float fElapsedTime) override;
        bool    OnUserDestroy() override;

        Button  createButton(uint8_t posx, uint8_t posy, uint8_t sizex, uint8_t sizey, void (*fction)());
        bool    loadAssets();
        bool    loadButtons();

        bool    handleUserInput();
        olc::vi2d   getCellFromMouse(const olc::vi2d mousePos);

        void    drawPieces();
        void    drawAvailableCells();
        void    drawAttackedCells();
        void    drawButton(Button b);

};
void    TestButton();