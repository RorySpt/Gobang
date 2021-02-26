#include <graphics.h>
#include "board.h"
#include "Piece.h"
#include "gameEngine.h"
#include <string>
using namespace std;
LPCTSTR pImg[10] = { 
	L"E:/壁纸/wallhaven-739712.jpg", 
	L"C:/Users/zhang/Pictures/Saved Pictures/v2-0963de0885224e9da786aff051d1b536_r.jpg",
	L"C:/Users/zhang/Pictures/Saved Pictures/v2-64736fe98876a48978f980965c5a4b89_r.jpg",
	L"E:/壁纸/wallhaven-730881.jpg",
	L"E:/壁纸/wallhaven-742272.jpg",
	L"E:/壁纸/wallhaven-743498.png",
	L"E:/壁纸/wallhaven-727341.jpg",
	L"E:/壁纸/wallhaven-729634.jpg",
	L"E:/壁纸/wallhaven-739712.jpg",
	L"E:/壁纸/wallhaven-739712.jpg",
};

void mouseSet()
{
	
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("C:\\Windows\\Cursors\\aero_link_l.cur"), IMAGE_CURSOR, 40, 40, LR_LOADFROMFILE);
	HWND hwnd = GetHWnd();							// 获取绘图窗口句柄
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// 设置窗口类的鼠标样式
}

int main()
{

	
	
	Board::BoardFormat format({30,19,19});
	format.aligning_size();
	//创建棋子
	Piece black_pie(BLACK, int(format.GridLines_Spacing * 0.4));
	Piece white_pie(WHITE, int(format.GridLines_Spacing * 0.4));

	//创建棋盘
	Board bo(format/*, pImg[0]*/);
	//Board bo(format, RGB(255, 205, 150));

	//窗口初始化
	initgraph(bo.getFormat().board_w, bo.getFormat().board_h);

	//创建棋局
	gameEngine chess (bo,  white_pie, black_pie);

	

	BeginBatchDraw();

	//鼠标
	MOUSEMSG mos(GetMouseMsg());
	mouseSet();
	chess.beginPlay(gameEngine::PLAYER::PLAY1);
	while (1)
	{
		cleardevice();

		//输出棋局内容
		chess.put(NULL);
		//捕捉鼠标操作
		if(MouseHit())mos = GetMouseMsg();
		FlushMouseMsgBuffer();
		if(!mos.mkLButton)circle(mos.x,mos.y,5);
		else fillcircle(mos.x, mos.y, 5);
		Board::seat seat = bo.getSeat(mos.x, mos.y);
		//提示选中框
		rectangle(seat.x + format.GridLines_Spacing/2, seat.y + format.GridLines_Spacing / 2, seat.x - format.GridLines_Spacing / 2, seat.y - format.GridLines_Spacing / 2);
		
		/*if (mos.mkLButton)black_pie.put(NULL, seat);
		if (mos.mkRButton)white_pie.put(NULL, seat);*/
		Board::seat seatSub = bo.getSeatsub(mos.x, mos.y);


		//放置棋子
		/*if (mos.mkLButton)chess.set(seatSub,gameEngine::PIEKEY::SET_A);
		if (mos.mkRButton)chess.set(seatSub, gameEngine::PIEKEY::SET_B);
		if (mos.mkMButton)chess.set(seatSub, gameEngine::PIEKEY::CLR);*/

		if (mos.mkLButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY1);
		if (mos.mkRButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY2);
		//if (mos.mkMButton) { chess.set(seatSub, gameEngine::PIEKEY::CLR); chess.continuePlay(); }
		if (mos.mkMButton) { chess.beginPlay(gameEngine::PLAYER::PLAY1); }


		//文本提示

		//坐标
		setbkmode(TRANSPARENT);
		WCHAR tmp[20];
		swprintf_s(tmp, L"x:%d y:%d", seatSub.x + 1, seatSub.y + 1);
		outtextxy(
			format.board_w - 4*16,
			format.board_h - 16,
			tmp
		);

		//棋盘概况
		int a, b, n;
		chess.stats(a, b, n);
		swprintf_s(tmp, L"A:%d B:%d N:%d", a, b, n);
		outtextxy(
			0,
			format.board_h - 16,
			tmp
		);

		swprintf_s(tmp, L"裁判：%ws着子", (chess.getPlayer() == gameEngine::PLAYER::PLAY2)?L"黑棋":L"白棋");
		outtextxy(
			format.board_w/3,
			format.board_h - 16,
			tmp
		);
		FlushBatchDraw();
		Sleep(10);
	}
	EndBatchDraw();
}