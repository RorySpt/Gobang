#include "AI_Coach.h"
#include <iostream>
void AI_Coach::CompatibilityLayer()
{
	auto& chessMap = gEngine->seeChess();
	for (int iy(0); iy < 19; ++iy)
		for (int ix(0); ix < 19; ++ix)
		{
			BOX[iy][ix].value = chessMap[iy][ix] - 1;
		}
}

Board::seat  AI_Coach::calOptimalPos(gameEngine::PLAYER player)
{
	CompatibilityLayer();
	seat _seat;
	_seat = findbestseat(2-(int)player, 0);
	std::cout << _seat.j<<','<<_seat.i << std::endl;
	return { _seat.j, _seat.i };
}

AI_Coach::seat AI_Coach::findbestseat(int color, int c)
{
	if (c == 0)
	{
		//如果是第一层
		//清空数组
		mylength = 0;
	}
	int MAXnumber = INT_MIN;    //最佳分数
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (BOX[i][j].value == -1) {
				//遍历每一个空位置
				int length;        //当前方向长度
				int emeny;         //当前方向敌子
				int nowi = 0;      //现在遍历到的y坐标
				int nowj = 0;      //现在遍历到的x坐标
				int thescore = 0;  //这个位置的初始分数
				//判断周边有没有棋子
				int is = 0;
				for (int k = 0; k < 4; k++)
				{
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi += dx[k];
					nowj += dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
					nowi = i;
					nowj = j;
					nowi -= dx[k];
					nowj -= dy[k];
					if (nowi >= 0 && nowj >= 0
						&& nowi <= 18 && nowj <= 18
						&& BOX[nowi][nowj].value != -1)
					{
						is = 1;
						break;
					}
				}
				if (!is)
				{
					//如果周围没有棋子，就不用递归了
					continue;
				}
				//自己
				BOX[i][j].value = color;//尝试下在这里
				for (int k = 0; k < 4; k++)
				{
					//检测四个方向
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == !color)
					{
						emeny++;
					}
					length -= 2;//判断长度
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 500)
					{
						//己方胜利，结束递归
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//敌人（原理同上）
				BOX[i][j].value = !color;
				for (int k = 0; k < 4; k++)
				{
					length = 0;
					emeny = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj += dy[k];
						nowi += dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].value == !color)
					{
						length++;
						nowj -= dy[k];
						nowi -= dx[k];
					}
					if (nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18 || BOX[nowi][nowj].value == color)
					{
						emeny++;
					}
					length -= 2;
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 500)
					{
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				BOX[i][j].value = -1;
				//如果已经比最高分数小，就没必要递归了
				if (thescore >= MAXnumber)
				{
					if (c < 3)
					{
						//只能找4层，否则时间太长
						BOX[i][j].value = color;
						//递归寻找对方分数
						int nowScore = thescore - findbestseat(!color, c + 1).number;//递归求出这个位置的分值
						BOX[i][j].value = -1;
						if (nowScore > MAXnumber)
						{
							//比最高分值大
							MAXnumber = nowScore;
							if (c == 0)
							{
								//第一层
								mylength = 0;//清空数组
							}
						}
						if (c == 0)
						{
							//第一层
							if (nowScore >= MAXnumber)
							{
								//把当前位置加入数组
								MAXxs[mylength] = i;
								MAXys[mylength] = j;
								mylength++;
							}
						}
					}
					else {
						//如果递归到了最后一层
						if (thescore > MAXnumber)
						{
							//直接更新
							MAXnumber = thescore;
						}
					}
				}
			}
		}
	}
	if (c == 0)
	{
		if(mylength == 0)
		{return { 9,9,MAXnumber };}
		//第一层
		//随机化落子位置
		int mynum = rand() % mylength;
		return { MAXxs[mynum],MAXys[mynum],MAXnumber };
	}
	//其他层
	return { 0,0,MAXnumber };
}
