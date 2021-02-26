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
		chessStep.clear();
	};

	void gameEngineReload(const Board& bo, const  Piece& pie_a, const  Piece& pie_b);

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
	void playSet(Board::seat _seat, PLAYER _player = PLAYER::null);
	

	//开始/重置棋局
	void beginPlay(PLAYER _player);

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

