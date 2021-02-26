#pragma once
#include <graphics.h>
#include <conio.h>
// 引用该库才能使用 AlphaBlend 函数
#pragma comment( lib, "MSIMG32.LIB")
#include "board.h"
class Piece
{
	
public:
	Piece(IMAGE& img, int rad);
	Piece(COLORREF col, int rad);
	Piece(const Piece& pie);
	// 半透明贴图函数
	// 参数：
	//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
	//		x, y:	目标贴图位置
	//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
	void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
	{
		HDC dstDC = GetImageHDC(dstimg);
		HDC srcDC = GetImageHDC(srcimg);
		int w = srcimg->getwidth();
		int h = srcimg->getheight();

		// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		// 使用 Windows GDI 函数实现半透明位图
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
