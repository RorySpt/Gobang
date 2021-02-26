#pragma once
#include <graphics.h>
#include "gameEngine.h"
#include "AI_BASE.h"
class AI_Coach : public AI_BASE
{
public:
	//��ʼ��
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
*ԭʼ����
*********************************************************************/
	// ����λ�õ���
	class seat
	{
	public:
		int i = 0;      // y ����
		int j = 0;      // x ����
		int number = 0; // ����
	};

	// �������̵���
	class box
	{
	public:
		//void draw();            // ����
	public:
		int x = 0;              // x ����
		int y = 0;              // y ����
		int value = -1;         // ֵ�����壺1�����壺0����λ��-1��
		int modle = 0;          // ģʽ
		bool isnew = false;     // �Ƿ���ѡ���
		COLORREF color = WHITE; // ���̱���ɫ
	};


	// ȫ�ֱ���
	box BOX[19][19];      // ����
	int win = -1;         // ˭Ӯ�ˣ�0�����壬1�����壬2��ƽ�֣�
	int whoplay = 0;      // �ֵ�˭������
	int playercolor = 0;  // �����ɫ
	int dx[4]{ 1,0,1,1 }; // - | \ / �ĸ�����
	int dy[4]{ 0,1,1,-1 };
	int Score[3][5] = //���ֱ�
	{
		{ 0, 80, 250, 500, 500 }, // ����0��
		{ 0, 0,  80,  250, 500 }, // ����1��
		{ 0, 0,  0,   80,  500 }  // ����2��
	};
	int MAXxs[361] = { 0 };   //����x����
	int MAXys[361] = { 0 };   //����y����
	int mylength = 0; //���Ž���

	seat findbestseat(int color, int c);
/********************************************************************
*********************************************************************/


	//���ݲ㣬����������BOX��ֻ����valueֵ
	void CompatibilityLayer();
public:
	//����ӿ�,�������λ��
	Board::seat calOptimalPos(gameEngine::PLAYER player);
};

