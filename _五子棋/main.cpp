#include <graphics.h>
#include "board.h"
#include "Piece.h"
#include "gameEngine.h"
#include <string>
#include <map>
#include "AI.h"
#include<ctime>
#define KEY_DOWN(VK_NONAME) (((GetAsyncKeyState(VK_NONAME)) ) ? 1:0)
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

	
	
	Board::BoardFormat format({40,13,13});
	format.aligning_size();
	//创建棋子
	map < gameEngine::PLAYER, COLORREF > pCol;
	pCol[gameEngine::PLAYER::PLAY1] = WHITE;
	pCol[gameEngine::PLAYER::PLAY2] = BLACK;
	Piece black_pie(pCol[gameEngine::PLAYER::PLAY2], int(format.GridLines_Spacing * 0.4));
	Piece white_pie(pCol[gameEngine::PLAYER::PLAY1], int(format.GridLines_Spacing * 0.4));

	//创建棋盘
	Board bo(format, pImg[8]);
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
	AI ai0(&chess);

	/*chess.playSet({9,9}, gameEngine::PLAYER::PLAY1);
	chess.playSet({ 8,8 }, gameEngine::PLAYER::PLAY2);*/
	srand(time(NULL) * time(NULL) % 12367);
	//int n = 1;
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


		gameEngine::STATUS chStatus = chess.rule();
		//放置棋子
		/*if (mos.mkLButton)chess.set(seatSub,gameEngine::PIEKEY::SET_A);
		if (mos.mkRButton)chess.set(seatSub, gameEngine::PIEKEY::SET_B);
		if (mos.mkMButton)chess.set(seatSub, gameEngine::PIEKEY::CLR);*/
		if (chStatus == gameEngine::STATUS::STILL)
		{
			if (mos.mkLButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY1);
			//if (mos.mkRButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY2);
			chess.playSet( ai0.calOptimalPos(gameEngine::PLAYER::PLAY2), gameEngine::PLAYER::PLAY2);

			if (KEY_DOWN(VK_NUMPAD0)) chess.playSet(ai0.calOptimalPos(gameEngine::PLAYER::PLAY1), gameEngine::PLAYER::PLAY1);
		}
		
		//if (mos.mkMButton) { chess.set(seatSub, gameEngine::PIEKEY::CLR); chess.continuePlay(); }
		if (KEY_DOWN(192)) { chess.beginPlay((gameEngine::PLAYER)(rand()%2+1)); }
	
		if (mos.mkMButton) { chess.beginPlay(gameEngine::PLAYER::PLAY1); }
		/*if (n == 1) {
			n--; chess.playSet({0,0}, gameEngine::PLAYER::PLAY1);
		}*/
		


		//文本提示

		//对局情况
		wstring wchr;
		//gameEngine::STATUS chStatus = chess.rule();
		switch (chStatus)
		{
		case gameEngine::STATUS::STILL:wchr = { L"对局中" }; break;
		case gameEngine::STATUS::WIN_PLAY1:wchr = { L"白棋胜" }; break;
		case gameEngine::STATUS::WIN_PLAY2:wchr = { L"黑棋胜" }; break;
		case gameEngine::STATUS::DRAW:wchr = { L"和棋" }; break;
		default:break;
		}



		//坐标
		setbkmode(TRANSPARENT);
		WCHAR tmp[20];


		if (KEY_DOWN(VK_MENU))
		{
			COLORREF colTmp = gettextcolor();
			const vector<gameEngine::STEP>& chessLog = chess.getChessLog();
			for (auto iter(chessLog.begin()); iter != chessLog.end(); ++iter)
			{
				if((*iter).player ==gameEngine::PLAYER::PLAY1)settextcolor(pCol[gameEngine::PLAYER::PLAY2]);
				else settextcolor(pCol[gameEngine::PLAYER::PLAY1]);
				if(iter == chessLog.end() - 1)settextcolor(RED);
				swprintf_s(tmp, L"%d", iter - chessLog.begin() + 1);
				Board::seat _tuSeat = bo.findSeat((*iter).seat);
				int n = wstring(tmp).size();
				outtextxy(
					_tuSeat.x - 4*(n ),
					_tuSeat.y - 8,
					tmp
				);
			}
			
			settextcolor(colTmp);
			
			
		}
		int showAIco = 0;
		if (KEY_DOWN(90))//Z
		{
			COLORREF colTmp = getlinecolor();
			const auto& map = ai0.showMark(gameEngine::PLAYER::PLAY2);
			for (size_t iy(0); iy != map.size(); ++iy)
				for (size_t ix(0); ix != map[iy].size(); ++ix)
				{
					if (map[iy][ix] >= 1000)setlinecolor(RED);
					else setlinecolor(BLUE);
					Board::seat seat = bo.findSeat({ (int)ix, (int)iy });
					circle(seat.x, seat.y, (map[iy][ix] >= 20000) + (map[iy][ix] >= 10000)+ (map[iy][ix] >= 5000) + (map[iy][ix] >= 1000) + (map[iy][ix] >= 500)+ (map[iy][ix] >= 100) + (map[iy][ix] >= 30) + (map[iy][ix] >= 15) );
				}
			setlinecolor(colTmp);
			showAIco += 1;
		}
		

		if (KEY_DOWN(88))//X
		{
			COLORREF colTmp = getlinecolor();
			const auto& map = ai0.showMark(gameEngine::PLAYER::PLAY1);
			for (size_t iy(0); iy != map.size(); ++iy)
				for (size_t ix(0); ix != map[iy].size(); ++ix)
				{
					if (map[iy][ix] >= 1000)setlinecolor(RED);
					else setlinecolor(BLUE);
					Board::seat seat = bo.findSeat({ (int)ix, (int)iy });
					circle(seat.x, seat.y, (map[iy][ix] >= 20000) + (map[iy][ix] >= 10000) + (map[iy][ix] >= 5000)+ (map[iy][ix] >= 1000) + (map[iy][ix] >= 500) + (map[iy][ix] >= 100) + (map[iy][ix] >= 30) + (map[iy][ix] >= 15) );
				}
			setlinecolor(colTmp);
			showAIco += 10;
		}
		//ai提示文本
		switch (showAIco)
		{
			//case 0:swprintf_s(tmp, L"x:%d y:%d", seatSub.x + 1, seatSub.y + 1); break;
			case 1:swprintf_s(tmp, L"AI:%ws", L"黑"); break;
			case 10:swprintf_s(tmp, L"AI:%ws", L"白"); break;
			case 11:swprintf_s(tmp, L"AI:%ws", L"all"); break;
			default:swprintf_s(tmp, L" "); break;
		}
		outtextxy(
			0,
			0,
			tmp
		);

		//选中坐标
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

		swprintf_s(tmp, L"裁判：%ws着子(%ws)", (chess.getPlayer() == gameEngine::PLAYER::PLAY2)?L"黑棋":L"白棋",wchr.c_str());
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