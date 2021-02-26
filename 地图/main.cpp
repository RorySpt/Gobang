#include <graphics.h>
#include "board.h"



int main()
{

	
	
	Board::BoardFormat format({0,0,30,30,30,30,20,36,36});
	format.aligning_size();
	//Board bo(format, RGB(255, 205, 150));
	
	Board bo(format, L"E:/壁纸/wallhaven-739712.jpg");
	initgraph(bo.getFormat().board_w, bo.getFormat().board_h);
	BeginBatchDraw();
	MOUSEMSG mos(GetMouseMsg());
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("C:\\Windows\\Cursors\\aero_link_l.cur"), IMAGE_CURSOR, 40, 40, LR_LOADFROMFILE);
	HWND hwnd = GetHWnd();							// 获取绘图窗口句柄
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// 设置窗口类的鼠标样式
	while (1)
	{
		cleardevice();
		//system("pause");
		putimage(0,0,&bo.BoardImage());
		
		if(MouseHit())mos = GetMouseMsg();
		if(!mos.mkLButton)circle(mos.x,mos.y,5);
		else fillcircle(mos.x, mos.y, 5);
		Board::seat seat = bo.getSeat(mos.x, mos.y);
		rectangle(seat.x + 10, seat.y + 10, seat.x - 10, seat.y - 10);
		FlushBatchDraw();
	}
	EndBatchDraw();
}