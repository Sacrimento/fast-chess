#define OLC_PGE_APPLICATION
#define OLC_PGEX_SOUND

#include "ChessInterface.h"

int main()
{
	ChessEngine *engine = new ChessEngine();
	ChessInterface chess("duChess");

	chess.setEngine(engine);
	if (chess.Construct(CI_SCREEN_W, CI_SCREEN_H, 1, 1))
		chess.Start();

	delete engine;
	return 0;
}
