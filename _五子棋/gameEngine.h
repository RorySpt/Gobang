#pragma once
#include "Board.h"
#include "Piece.h"
#include <graphics.h>
#include <vector>
class gameEngine
{
public:
	enum class PIEKEY{CLR,SET_A, SET_B};
	enum class PLAYER{null,PLAY1,PLAY2};
	enum class STATUS{null,STILL,WIN_PLAY1,WIN_PLAY2,DRAW};
	struct STEP
	{
		PLAYER player;
		Board::seat seat;
	};
public:
	gameEngine(const Board &bo, const  Piece &pie_a, const  Piece &pie_b);
	~gameEngine() {
		pieSub.clear();
	};


	//规则
	STATUS rule();

	//将棋局内容输出至out
	void put(IMAGE* out);

	//放置棋子
	void set(Board::seat _seat, PIEKEY wp);

	//统计棋局
	void stats(int& a, int& b, int& n);

	//获取棋子位置信息
	const std::vector<std::vector<int>>& seeChess() const { return pieSub; }

	//获取当前待落子棋手
	PLAYER getPlayer() { return player; }

	//棋手下棋
	void playSet(Board::seat _seat ,PLAYER _player = PLAYER::null)
	{
		if(_player ==player|| _player== PLAYER::null)
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

	//开始/重置棋局
	void beginPlay(PLAYER _player) 
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

	//继续棋局
	void continuePlay()
	{
		int a, b, n;
		stats(a, b, n);
		if (a == b)player = FirstPlayer;
		else
		{
			if (a>b)player = PLAYER::PLAY2;
			else player = PLAYER::PLAY1;
		}
	}

	const std::vector<STEP>& getChessLog()
	{
		return chessStep;
	}
private:
	//一个用于存放棋子逻辑位置的动态数组
	std::vector<std::vector<int>> pieSub;

	
	//棋谱
	std::vector<STEP>chessStep;
	//IMAGE gameMap;
	Board board;
	Piece piece_a, piece_b;
	PLAYER player = PLAYER::null;
	PLAYER FirstPlayer = PLAYER::null;

};

