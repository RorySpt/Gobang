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
		//����ǵ�һ��
		//�������
		mylength = 0;
	}
	int MAXnumber = INT_MIN;    //��ѷ���
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (BOX[i][j].value == -1) {
				//����ÿһ����λ��
				int length;        //��ǰ���򳤶�
				int emeny;         //��ǰ�������
				int nowi = 0;      //���ڱ�������y����
				int nowj = 0;      //���ڱ�������x����
				int thescore = 0;  //���λ�õĳ�ʼ����
				//�ж��ܱ���û������
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
					//�����Χû�����ӣ��Ͳ��õݹ���
					continue;
				}
				//�Լ�
				BOX[i][j].value = color;//������������
				for (int k = 0; k < 4; k++)
				{
					//����ĸ�����
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
					length -= 2;//�жϳ���
					if (length > 4)
					{
						length = 4;
					}
					if (Score[emeny][length] == 500)
					{
						//����ʤ���������ݹ�
						BOX[i][j].value = -1;
						return{ i,j,Score[emeny][length] };
					}
					thescore += Score[emeny][length];
					length = 0;
					emeny = 0;
				}
				//���ˣ�ԭ��ͬ�ϣ�
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
				//����Ѿ�����߷���С����û��Ҫ�ݹ���
				if (thescore >= MAXnumber)
				{
					if (c < 3)
					{
						//ֻ����4�㣬����ʱ��̫��
						BOX[i][j].value = color;
						//�ݹ�Ѱ�ҶԷ�����
						int nowScore = thescore - findbestseat(!color, c + 1).number;//�ݹ�������λ�õķ�ֵ
						BOX[i][j].value = -1;
						if (nowScore > MAXnumber)
						{
							//����߷�ֵ��
							MAXnumber = nowScore;
							if (c == 0)
							{
								//��һ��
								mylength = 0;//�������
							}
						}
						if (c == 0)
						{
							//��һ��
							if (nowScore >= MAXnumber)
							{
								//�ѵ�ǰλ�ü�������
								MAXxs[mylength] = i;
								MAXys[mylength] = j;
								mylength++;
							}
						}
					}
					else {
						//����ݹ鵽�����һ��
						if (thescore > MAXnumber)
						{
							//ֱ�Ӹ���
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
		//��һ��
		//���������λ��
		int mynum = rand() % mylength;
		return { MAXxs[mynum],MAXys[mynum],MAXnumber };
	}
	//������
	return { 0,0,MAXnumber };
}
