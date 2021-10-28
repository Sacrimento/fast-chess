#define OLC_PGE_APPLICATION

#include "ChessInterface.h"

int main()
{
	ChessInterface chess("Fast Chess");
	if (chess.Construct(1280, 720, 1, 1))
		chess.Start();
	return 0;
}
