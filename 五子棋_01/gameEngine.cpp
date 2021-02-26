#include "gameEngine.h"
gameEngine::gameEngine(const Board& bo, const  Piece& pie_a, const  Piece& pie_b) :board(bo), piece_a(pie_a), piece_b(pie_b)
{
	pieSub.resize(bo.getFormat().GridLines_Ny);
	for (size_t iy(0); iy < pieSub.size(); ++iy)
		pieSub[iy].resize(bo.getFormat().GridLines_Nx, 0);

};

void gameEngine::put(IMAGE* out)
{
	IMAGE* tmp = GetWorkingImage();
	SetWorkingImage(out);
	putimage(0, 0, &board.BoardImage());
	if (board.getFormat().GridLines_Nx == 19 && board.getFormat().GridLines_Ny == 19)
	{
		setfillcolor(BLACK);
		Board::seat _seat = board.findSeat({ 3, 3 });
		solidcircle(_seat.x, _seat.y, 3 + board.getFormat().GridLines_Spacing / 40);
		_seat = board.findSeat({ 15, 15 });
		solidcircle(_seat.x, _seat.y, 3 + board.getFormat().GridLines_Spacing / 21);
		_seat = board.findSeat({ 3, 15 });
		solidcircle(_seat.x, _seat.y, 3 + board.getFormat().GridLines_Spacing / 21);
		_seat = board.findSeat({ 15, 3 });
		solidcircle(_seat.x, _seat.y, 3 + board.getFormat().GridLines_Spacing / 21);
		_seat = board.findSeat({ 9, 9 });
		solidcircle(_seat.x, _seat.y, 3 + board.getFormat().GridLines_Spacing / 21);
	}

	for (int iy(0); iy != pieSub.size(); ++iy)
		for (int ix(0); ix != pieSub[iy].size(); ++ix)
		{
			if (pieSub[iy][ix] != 0)
			{
				Board::seat _seat = board.findSeat({ ix,iy });
				if (pieSub[iy][ix] == 1)piece_a.put(out, _seat);
				if (pieSub[iy][ix] == 2)piece_b.put(out, _seat);
			}
		}
	SetWorkingImage(tmp);
}

void gameEngine::set(Board::seat _seat, PIEKEY wp)
{
	if (_seat.y < (int)pieSub.size() && _seat.x < (int)pieSub[0].size())
		switch (wp)
		{
		case PIEKEY::SET_A:pieSub[_seat.y][_seat.x] = 1; chessStep.push_back({ PLAYER::PLAY1,_seat }); break;
		case PIEKEY::SET_B:pieSub[_seat.y][_seat.x] = 2; chessStep.push_back({ PLAYER::PLAY2,_seat }); break;
		case PIEKEY::CLR:
		{
			/*int a, b, n;
			stats(a, b, n);
			if (pieSub[_seat.y][_seat.x] == 1 && a > b) { pieSub[_seat.y][_seat.x] = 0; break; }
			if (pieSub[_seat.y][_seat.x] == 2 && a < b) { pieSub[_seat.y][_seat.x] = 0; break; }
			if (a == b)
			{
				if (FirstPlayer == PLAYER::PLAY1 && pieSub[_seat.y][_seat.x] == 2)  pieSub[_seat.y][_seat.x] = 0;
				if (FirstPlayer == PLAYER::PLAY2 && pieSub[_seat.y][_seat.x] == 1)  pieSub[_seat.y][_seat.x] = 0;
			}*/
			pieSub[_seat.y][_seat.x] = 0; chessStep.push_back({ PLAYER::null,_seat });
			break;
		}
		}

}

void gameEngine::stats(int& a, int& b, int& n)
{
	int _a(0), _b(0), _n(0);
	for (int iy(0); iy != pieSub.size(); ++iy)
		for (int ix(0); ix != pieSub[iy].size(); ++ix)
			switch (pieSub[iy][ix])
			{
			case 0:_n++; break;
			case 1:_a++; break;
			case 2:_b++; break;
			}
	a = _a; b = _b; n = _n;
}


gameEngine::STATUS gameEngine::rule()
{
	int nop(0);
	for (size_t iy(0); iy != pieSub.size(); ++iy)
		for (size_t ix(0); ix != pieSub[iy].size(); ++ix)
			if (pieSub[iy][ix] != 0)
			{
				int cp = pieSub[iy][ix];
				int length[4] = { NULL };
				//				
#define  WINER (cp == 1 ? STATUS::WIN_PLAY1 : STATUS::WIN_PLAY2)


				for (int in(1); in != 5; ++in)
					if ((int)iy + in < (int)pieSub.size() && ix + in < pieSub[iy].size())
						if (pieSub[iy + in][ix + in] == cp) { ++length[0]; if (length[0] == 4)return WINER; }
						else break;
				for (int in(1); in != 5; ++in)
					if ((int)iy - in >= 0 && (int)ix - in >= 0)
						if (pieSub[iy - in][ix - in] == cp) { ++length[0]; if (length[0] == 4)return WINER; }
						else break;

				for (int in(1); in != 5; ++in)
					if ((int)iy < (int)pieSub.size() && (int)ix + in < (int)pieSub[iy].size())
						if (pieSub[iy][ix + in] == cp) { ++length[1]; if (length[1] == 4)return WINER; }
						else break;
				for (int in(1); in != 5; ++in)
					if ((int)iy < pieSub.size() && (int)ix - in >= 0)
						if (pieSub[iy][ix - in] == cp) { ++length[1]; if (length[1] == 4)return WINER; }
						else break;

				for (int in(1); in != 5; ++in)
					if ((int)iy + in < (int)pieSub.size())
						if (pieSub[iy + in][ix] == cp) { ++length[2]; if (length[2] == 4)return WINER; }
						else break;
				for (int in(1); in != 5; ++in)
					if ((int)iy - in >= 0)
						if (pieSub[iy - in][ix] == cp) { ++length[2]; if (length[2] == 4)return WINER; }
						else break;

				for (int in(1); in != 5; ++in)
					if ((int)iy + in < (int)pieSub.size() && (int)ix - in >= 0)
						if (pieSub[iy + in][ix - in] == cp) { ++length[3]; if (length[3] == 4)return WINER; }
						else break;
				for (int in(1); in != 5; ++in)
					if ((int)iy - in >= 0 && (int)ix + in < (int)pieSub[iy].size())
						if (pieSub[iy - in][ix + in] == cp) { ++length[3]; if (length[3] == 4)return WINER; }
						else break;
			}
			else ++nop;
	if (nop)return STATUS::STILL;
	else return STATUS::DRAW;
}


void gameEngine::playSet(Board::seat _seat, PLAYER _player )
{
	if (_player == player || _player == PLAYER::null)
	{
		if (pieSub[_seat.y][_seat.x] == 0 && player != PLAYER::null)
			if (player == PLAYER::PLAY1)
			{
				set(_seat, PIEKEY::SET_A);
				player = PLAYER::PLAY2;
			}
			else if (player == PLAYER::PLAY2)
			{
				set(_seat, PIEKEY::SET_B);
				player = PLAYER::PLAY1;
			}
	}

}

void gameEngine::beginPlay(PLAYER _player)
{
	if (FirstPlayer == PLAYER::null)
	{
		FirstPlayer = _player;
		player = FirstPlayer;
	}
	else
	{
		//pieSub.resize(board.getFormat().GridLines_Ny);
		for (size_t iy(0); iy < (int)pieSub.size(); ++iy)
			for (size_t ix(0); ix < (int)pieSub[0].size(); ++ix)
				pieSub[iy][ix] = 0;
		//pieSub[iy].resize(board.getFormat().GridLines_Nx, 0);
		FirstPlayer = _player;
		player = FirstPlayer;
		chessStep.clear();
	}
}

void gameEngine::gameEngineReload(const Board& bo, const  Piece& pie_a, const  Piece& pie_b)
{
	const Board::BoardFormat& _Format = board.getFormat();
	board.BoardReload(bo);
	this->piece_a = pie_a;
	this->piece_b = pie_b;
	if(_Format!= board.getFormat())
	{
		pieSub.resize(bo.getFormat().GridLines_Ny);
		for (size_t iy(0); iy < pieSub.size(); ++iy)
			pieSub[iy].resize(bo.getFormat().GridLines_Nx, 0);
	}
	
}
