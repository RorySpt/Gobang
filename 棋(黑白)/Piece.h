#pragma once
#include <graphics.h>
#include <conio.h>
// ���øÿ����ʹ�� AlphaBlend ����
#pragma comment( lib, "MSIMG32.LIB")
#include "board.h"
class Piece
{
	
public:
	Piece(IMAGE& img, int rad);
	Piece(COLORREF col, int rad);
	Piece(const Piece& pie);
	// ��͸����ͼ����
	// ������
	//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
	//		x, y:	Ŀ����ͼλ��
	//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
	void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
	{
		HDC dstDC = GetImageHDC(dstimg);
		HDC srcDC = GetImageHDC(srcimg);
		int w = srcimg->getwidth();
		int h = srcimg->getheight();

		// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
		AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
	}
	void put(IMAGE* pibo,int x,int y)
	{
		transparentimage(pibo, x, y, &Skin);
	}

	void put(IMAGE* pibo, Board::seat _seat)
	{
		IMAGE* tmp=GetWorkingImage();
		SetWorkingImage(pibo);
		setfillcolor(colSkin);
		setfillstyle(BS_SOLID);
		fillcircle(_seat.x, _seat.y, radius);
		SetWorkingImage(tmp);
	}
private:
	IMAGE Skin;
	COLORREF colSkin = RGB(255, 205, 150);
	int radius = 7;
};
