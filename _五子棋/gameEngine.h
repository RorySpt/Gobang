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

	//��ʼ/�������
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

	//�������
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

