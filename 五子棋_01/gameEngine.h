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

	//����
	STATUS rule();

	//��������������out
	void put(IMAGE* out);

	//��������
	void set(Board::seat _seat, PIEKEY wp);

	//ͳ�����
	void stats(int& a, int& b, int& n);

	//��ȡ����λ����Ϣ
	const std::vector<std::vector<int>>& seeChess() const { return pieSub; }

	//��ȡ��ǰ����������
	PLAYER getPlayer() { return player; }

	//��������
	void playSet(Board::seat _seat, PLAYER _player = PLAYER::null);
	

	//��ʼ/�������
	void beginPlay(PLAYER _player);

	const std::vector<STEP>& getChessLog()
	{
		return chessStep;
	}
private:
	//һ�����ڴ�������߼�λ�õĶ�̬����
	std::vector<std::vector<int>> pieSub;

	
	//����
	std::vector<STEP>chessStep;
	//IMAGE gameMap;
	Board board;
	Piece piece_a, piece_b;
	PLAYER player = PLAYER::null;
	PLAYER FirstPlayer = PLAYER::null;

};

