#include "AI.h"
#include<cmath>
int getScor(const int(&a)[9])
{
	int l = 4, r = 4;
	int _a = 3 - a[4];
	bool left(true), right(true);
	for (int n(1); n != 5; ++n)
	{
		if (a[4 + n] == a[4] && right)++r; else right = false;
		if (a[4 - n] == a[4] && left)--l; else left = false;
	}
	if (r - l >= 4)return (int)AI::MarkTable::su;
	if (r - l == 3)
	{
		if (a[r + 1] != 0 && a[l - 1] != 0)return (int)AI::MarkTable::null;
		else if (a[r + 1] == 0 && a[l - 1] == 0)return (int)AI::MarkTable::live4;
		else return (int)AI::MarkTable::die4;
	}
	if (r - l == 2)
	{
		if (a[r + 1] == 0 && a[l - 1] == 0)
		{
			if (a[r + 2] == _a && a[l - 2] == _a)return (int)AI::MarkTable::die3;
			else if (a[r + 2] == a[4] || a[l - 2] == a[4])return (int)AI::MarkTable::l_die4;
			else if (a[r + 2] == 0 || a[l - 2] == 0)return (int)AI::MarkTable::live3;
			//else return (int)AI::MarkTable::live3;
		}
		else if (a[r + 1] == _a && a[l - 1] == _a)return (int)AI::MarkTable::null;
		else if (a[r + 1] == _a)
			if (a[l - 2] == _a)return (int)AI::MarkTable::null;
			else if (a[l - 2] == 0)return (int)AI::MarkTable::die3;
			else return (int)AI::MarkTable::l_die4;
		else if (a[l - 1] == _a)
			if (a[r + 2] == _a)return (int)AI::MarkTable::null;
			else if (a[r + 2] == 0)return (int)AI::MarkTable::die3;
			else return (int)AI::MarkTable::l_die4;
		else return (int)AI::MarkTable::null;
	}
	if (r - l == 1)
	{
		int colorleft = a[l - 1];
		int	colorright = a[r + 1];
		int colorleft1 = a[l - 2];
		int colorright1 = a[r + 2];
		int colorleft2 = a[l - 3];
		int colorright2 = a[r + 3];
		int mycolor = a[4];
		int NOTHINGFLAG = 0;
		int hiscolor = _a;
#define DIE3 ((int)AI::MarkTable::die3)
#define ALIVE2 ((int)AI::MarkTable::live2)
#define LOWDIE4 ((int)AI::MarkTable::l_die4)
#define TIAO3 ((int)AI::MarkTable::j_live3)
#define NOTHREAT ((int)AI::MarkTable::null)
#define DIE2 ((int)AI::MarkTable::die2)
		if (colorleft == NOTHINGFLAG && colorright == NOTHINGFLAG)//两边断开位置均空
		{
			if ((colorright1 == NOTHINGFLAG && colorright2 == mycolor) ||
				(colorleft1 == NOTHINGFLAG && colorleft2 == mycolor))
				return DIE3;//死3
			else if (colorleft1 == NOTHINGFLAG && colorright1 == NOTHINGFLAG)
				return ALIVE2;//活2

			if ((colorright1 == mycolor && colorright2 == hiscolor) ||
				(colorleft1 == mycolor && colorleft2 == hiscolor))
				return DIE3;//死3

			if ((colorright1 == mycolor && colorright2 == mycolor) ||
				(colorleft1 == mycolor && colorleft2 == mycolor))
				return LOWDIE4;//死4

			if ((colorright1 == mycolor && colorright2 == NOTHINGFLAG) ||
				(colorleft1 == mycolor && colorleft2 == NOTHINGFLAG))
				return TIAO3;//跳活3
			//其他情况在下边返回NOTHREAT
		}
		else if (colorleft == hiscolor && colorright == hiscolor)//两边断开位置均非空
		{
			return NOTHREAT;
		}
		else if (colorleft == NOTHINGFLAG || colorright == NOTHINGFLAG)//两边断开位置只有一个空
		{
			if (colorleft == hiscolor) {//左边被对方堵住
				if (colorright1 == hiscolor || colorright2 == hiscolor) {//只要有对方的一个棋子
					return NOTHREAT;//没有威胁
				}
				else if (colorright1 == NOTHINGFLAG && colorright2 == NOTHINGFLAG) {//均空
					return DIE2;//死2
				}
				else if (colorright1 == mycolor && colorright2 == mycolor) {//均为自己的棋子
					return LOWDIE4;//死4
				}
				else if (colorright1 == mycolor || colorright2 == mycolor) {//只有一个自己的棋子
					return DIE3;//死3
				}
			}
			if (colorright == hiscolor) {//右边被对方堵住
				if (colorleft1 == hiscolor || colorleft2 == hiscolor) {//只要有对方的一个棋子
					return NOTHREAT;//没有威胁
				}
				else if (colorleft1 == NOTHINGFLAG && colorleft2 == NOTHINGFLAG) {//均空
					return DIE2;//死2
				}
				else if (colorleft1 == mycolor && colorleft2 == mycolor) {//均为自己的棋子
					return LOWDIE4;//死4
				}
				else if (colorleft1 == mycolor || colorleft2 == mycolor) {//只有一个自己的棋子
					return DIE3;//死3
				}
			}
		}
	}
	else if (r-l == 0) {//中心线1连
		int colorleft = a[l - 1];
		int	colorright = a[r + 1];
		int colorleft1 = a[l - 2];
		int colorright1 = a[r + 2];
		int colorleft2 = a[l - 3];
		int colorright2 = a[r + 3];
		int mycolor = a[4];
		int NOTHINGFLAG = 0;
		int hiscolor = _a;
		int colorleft3 = a[l - 4];
		int colorright3 = a[r + 4];
#define LOWALIVE2 ((int)AI::MarkTable::l_live2)
		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == mycolor)
			return LOWDIE4;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == mycolor)
			return LOWDIE4;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == NOTHINGFLAG && colorright == NOTHINGFLAG)
			return TIAO3;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == NOTHINGFLAG && colorleft == NOTHINGFLAG)
			return TIAO3;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == mycolor && colorleft3 == hiscolor && colorright == NOTHINGFLAG)
			return DIE3;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == mycolor && colorright3 == hiscolor && colorleft == NOTHINGFLAG)
			return DIE3;

		if (colorleft == NOTHINGFLAG && colorleft1 == NOTHINGFLAG &&
			colorleft2 == mycolor && colorleft3 == mycolor)
			return DIE3;
		if (colorright == NOTHINGFLAG && colorright1 == NOTHINGFLAG &&
			colorright2 == mycolor && colorright3 == mycolor)
			return DIE3;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == NOTHINGFLAG && colorleft3 == mycolor)
			return DIE3;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == NOTHINGFLAG && colorright3 == mycolor)
			return DIE3;

		if (colorleft == NOTHINGFLAG && colorleft1 == mycolor &&
			colorleft2 == NOTHINGFLAG && colorleft3 == NOTHINGFLAG && colorright == NOTHINGFLAG)
			return LOWALIVE2;
		if (colorright == NOTHINGFLAG && colorright1 == mycolor &&
			colorright2 == NOTHINGFLAG && colorright3 == NOTHINGFLAG && colorleft == NOTHINGFLAG)
			return LOWALIVE2;

		if (colorleft == NOTHINGFLAG && colorleft1 == NOTHINGFLAG &&
			colorleft2 == mycolor && colorleft3 == NOTHINGFLAG && colorright == NOTHINGFLAG)
			return LOWALIVE2;
		if (colorright == NOTHINGFLAG && colorright1 == NOTHINGFLAG &&
			colorright2 == mycolor && colorright3 == NOTHINGFLAG && colorleft == NOTHINGFLAG)
			return LOWALIVE2;

		//其余在下边返回没有威胁

	}
	return NOTHREAT;
}

void AI::Scoring(gameEngine::PLAYER _player)
{
	if (_player == gameEngine::PLAYER::null)return;
	int player = (int)_player ;
	const std::vector<std::vector<int>> pieSub = gEngine->seeChess();
	for (size_t iy(0); iy != pieSub.size(); ++iy)
		for (size_t ix(0); ix != pieSub[iy].size(); ++ix)
			if (pieSub[iy][ix] == 0)
			{
				int a[9];
				int score(0);
				int dx(0), dy(0);
				//1
				for (int n(0); n != 9; ++n)
				{
					dx = (int)ix - 4 + n;
					dy = (int)iy;
					if (dx >= 0 && dx < (int)pieSub[iy].size() && dy >= 0 && dy < (int)pieSub.size())
						a[n] = pieSub[dy][dx];
					else a[n] = 3 - player;
				}
				a[4] = player;
				score = getScor(a);
				//2
				for (int n(0); n != 9; ++n)
				{
					dx = (int)ix ;
					dy = (int)iy - 4 + n;
					if (dx >= 0 && dx < (int)pieSub[iy].size() && dy >= 0 && dy < (int)pieSub.size())
						a[n] = pieSub[dy][dx];
					else a[n] = 3 - player;
				}
				a[4] = player;
				score += getScor(a);
				//3
				for (int n(0); n != 9; ++n)
				{
					dx = (int)ix - 4 + n;
					dy = (int)iy - 4 + n;
					if (dx >= 0 && dx < (int)pieSub[iy].size() && dy >= 0 && dy < (int)pieSub.size())
						a[n] = pieSub[dy][dx];
					else a[n] = 3 - player;
				}
				a[4] = player;
				score += getScor(a);
				//4
				for (int n(0); n != 9; ++n)
				{
					dx = (int)ix - 4 + n;
					dy = (int)iy + 4 - n;
					if (dx >= 0 && dx < (int)pieSub[iy].size() && dy >= 0 && dy < (int)pieSub.size())
						a[n] = pieSub[dy][dx];
					else a[n] = 3 - player;
				}
				a[4] = player;
				
				score += getScor(a);

				score += ((pieSub.size() / 2 -abs(int(pieSub.size() / 2 - iy)))+(pieSub[iy].size() / 2 -abs(int(pieSub[iy].size() / 2 - ix))))/2 ;
				pieMark_player[player - 1][iy][ix] = score;
			}
			else
			{
				pieMark_player[player - 1][iy][ix] = 0;
			}
}
#include <vector>
//#include<iostream>
Board::seat AI::calOptimalPos(gameEngine::PLAYER player)
{
	Scoring(gameEngine::PLAYER::PLAY1);
	Scoring(gameEngine::PLAYER::PLAY2);
	struct OptimalC { size_t score; Board::seat _seat; };
	std::vector < OptimalC > MaxScore[2];
	int _player = (int)player - 1;
	int n_player = 1 - _player;
	//Board::seat seat[2] = { {0,0},{0,0} };
	for (int n = 0; n != 2; ++n)
		for (size_t iy(0); iy != pieMark_player[n].size(); ++iy)
			for (size_t ix(0); ix != pieMark_player[n].size(); ++ix)
			{
				if (MaxScore[n].empty())MaxScore[n].push_back({ pieMark_player[n][iy][ix], (int)ix, (int)iy });
				else
				{
					if (pieMark_player[n][iy][ix] > MaxScore[n][0].score)
					{
						MaxScore[n].clear(); 
						MaxScore[n].push_back({ pieMark_player[n][iy][ix], (int)ix, (int)iy });
					}
					else if (pieMark_player[n][iy][ix] == MaxScore[n][0].score)
					{
						MaxScore[n].push_back({ pieMark_player[n][iy][ix], (int)ix, (int)iy });
					}
					
				}

			}
	Board::seat _seat;
	if (MaxScore[_player][0].score >= MaxScore[n_player][0].score)
	{
		_seat = MaxScore[_player][(rand() % (int)MaxScore[_player].size())]._seat;
	}
	else
	{
		_seat = MaxScore[n_player][(rand() % (int)MaxScore[n_player].size())]._seat;
	}

	//std::cout << MaxScore[_player][0].score << ',' << MaxScore[n_player][0].score << std::endl;
	return _seat;
	//return (MaxScore[(int)player - 1] > MaxScore[2 - (int)player] ? seat[(int)player - 1] : seat[2 - (int)player]);
		/*for (size_t iy(0); iy != pieMark_player[1].size(); ++iy)
			for (size_t ix(0); ix != pieMark_player[1].size(); ++ix)
			{
				if (pieMark_player[1][iy][ix]+ pieMark_player[0][iy][ix] > MaxScore[0]) {
					MaxScore[0] = pieMark_player[1][iy][ix] + pieMark_player[0][iy][ix];
					seat[0] = { (int)ix,(int)iy };
				}

			}
		return seat[0];*/
	//return seat[2 - (int)player];
};
