#pragma once
#include <graphics.h>
#include "gameEngine.h"
#include "AI_BASE.h"
class AI_Coach : public AI_BASE
{
public:
	//初始化
	AI_Coach(const gameEngine* _gEngine)
	{
		if (_gEngine->seeChess().size() == 19 && _gEngine->seeChess()[0].size() == 19)
		{
			gEngine = _gEngine;
		}
		else return;
	}
private:
	const gameEngine *gEngine;

/********************************************************************
*原始数据
*********************************************************************/
	// 保存位置的类
	class seat
	{
	public:
		int i = 0;      // y 坐标
		int j = 0;      // x 坐标
		int number = 0; // 分数
	};

	// 保存棋盘的类
	class box
	{
	public:
		//void draw();            // 绘制
	public:
		int x = 0;              // x 坐标
		int y = 0;              // y 坐标
		int value = -1;         // 值（黑棋：1，白棋：0，空位：-1）
		int modle = 0;          // 模式
		bool isnew = false;     // 是否有选择框
		COLORREF color = WHITE; // 棋盘背景色
	};


	// 全局变量
	box BOX[19][19];      // 棋盘
	int win = -1;         // 谁赢了（0：白棋，1：黑棋，2：平局）
	int whoplay = 0;      // 轮到谁下棋了
	int playercolor = 0;  // 玩家颜色
	int dx[4]{ 1,0,1,1 }; // - | \ / 四个方向
	int dy[4]{ 0,1,1,-1 };
	int Score[3][5] = //评分表
	{
		{ 0, 80, 250, 500, 500 }, // 防守0子
		{ 0, 0,  80,  250, 500 }, // 防守1子
		{ 0, 0,  0,   80,  500 }  // 防守2子
	};
	int MAXxs[361] = { 0 };   //最优x坐标
	int MAXys[361] = { 0 };   //最优y坐标
	int mylength = 0; //最优解数

	seat findbestseat(int color, int c);
/********************************************************************
*********************************************************************/


	//兼容层，拷贝棋盘至BOX，只传递value值
	void CompatibilityLayer();
public:
	//对外接口,返回最佳位置
	Board::seat calOptimalPos(gameEngine::PLAYER player);
};

