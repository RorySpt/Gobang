#include <graphics.h>
#include "board.h"
#include "Piece.h"
#include "gameEngine.h"
#include <string>
#include <map>
#include "AI.h"
#include "AI_Coach.h"
#include<ctime>
#define KEY_DOWN(VK_NONAME) (((GetAsyncKeyState(VK_NONAME)) ) ? 1:0)
using namespace std;

#define ImgNum 4
LPCTSTR pImg[4] = { 
	L"res/wallhaven-674625.jpg",
	L"res/wallhaven-729415.jpg",
	L"res/wallhaven-739712.jpg",
	L"res/wallhaven-742272.jpg",
};

//#define Image(n) (Image (n))
void mouseSet()
{
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("C:\\Windows\\Cursors\\aero_link_l.cur"), IMAGE_CURSOR, 40, 40, LR_LOADFROMFILE);
	HWND hwnd = GetHWnd();							// ��ȡ��ͼ���ھ��
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// ���ô�����������ʽ
}

int EzMessageBox(int x,int y,const WCHAR *Format, ...)
{
	const int bSize = 1024;
	WCHAR tmp[bSize] = {NULL};
	//va_list pArgList(va_list(&Format) + sizeof(const WCHAR*));
	va_list pArgList;
	va_start(pArgList, Format);
	vswprintf_s(tmp, bSize, Format, pArgList);
	WCHAR *cstr = &tmp[0];
	WCHAR* cstr_end= & tmp[0];
	while (*cstr_end != L'\0')++cstr_end;
	while(1)
	{
		WCHAR* hcstr;
		hcstr = cstr;
		while (cstr != cstr_end)
		{
			switch (*cstr)
			{
			case L'\n':*cstr = L'\0'; break;
			case L'\0':return 0;
			case L'\\':*cstr = L' '; break;
			default:++cstr; break;
			}
			if (*cstr == L'\0') break;
			/*if (*cstr == L'\n') { *cstr = L'\0'; break; }

			else if (*cstr == L'\0') return 0;
			else ++cstr;*/
			
		}
		if (cstr != cstr_end)
		{
			outtextxy(x, y, hcstr);
			y += 20;
			++cstr;
		}
		
		else return 0;
	}
	

	//outtextxy(x, y, tmp);
	va_end(pArgList);
	return 0;
}

int main()
{
	//IMAGE a (IDB_PNG1);
	
	Board::BoardFormat format({30,19,19});
	format.aligning_size();
	//��������
	map < gameEngine::PLAYER, COLORREF > pCol;
	pCol[gameEngine::PLAYER::PLAY1] = WHITE;
	pCol[gameEngine::PLAYER::PLAY2] = BLACK;
	Piece black_pie(pCol[gameEngine::PLAYER::PLAY2], int(format.GridLines_Spacing * 0.4));
	Piece white_pie(pCol[gameEngine::PLAYER::PLAY1], int(format.GridLines_Spacing * 0.4));

	//��������
	
	Board bo(format);
	//Board bo(format, RGB(255, 205, 150));
	//���ڳ�ʼ��
	initgraph(bo.getFormat().board_w, bo.getFormat().board_h, EW_SHOWCONSOLE);

	//�������
	gameEngine chess (bo,  white_pie, black_pie);


	BeginBatchDraw();

	//���
	MOUSEMSG mos(GetMouseMsg());
	mouseSet();
	chess.beginPlay(gameEngine::PLAYER::PLAY1);
	AI ai0(&chess);
	AI_Coach ai1(&chess);
	/*chess.playSet({9,9}, gameEngine::PLAYER::PLAY1);
	chess.playSet({ 8,8 }, gameEngine::PLAYER::PLAY2);*/
	srand(time(NULL) * time(NULL) % 12367);

	#define Key_ADD  107
	#define Key_DEL  109
	map<int, bool>KeyStatus;
	KeyStatus[Key_ADD] = false;
	KeyStatus[Key_DEL] = false;

	//int n = 1;
	while (1)
	{
		cleardevice();
		//loadimage(NULL,L"IDR_IMAGE1.IMAGE")
		//����������
		chess.put(NULL);
		//��׽������
		if (MouseHit())mos = GetMouseMsg();
		FlushMouseMsgBuffer();
		if(!mos.mkLButton)circle(mos.x,mos.y,5);
		else fillcircle(mos.x, mos.y, 5);
		Board::seat seat = bo.getSeat(mos.x, mos.y);
		//��ʾѡ�п�
		rectangle(seat.x + format.GridLines_Spacing/2, seat.y + format.GridLines_Spacing / 2, seat.x - format.GridLines_Spacing / 2, seat.y - format.GridLines_Spacing / 2);
		
		/*if (mos.mkLButton)black_pie.put(NULL, seat);
		if (mos.mkRButton)white_pie.put(NULL, seat);*/
		Board::seat seatSub = bo.getSeatsub(mos.x, mos.y);


		gameEngine::STATUS chStatus = chess.rule();
		//��������
		/*if (mos.mkLButton)chess.set(seatSub,gameEngine::PIEKEY::SET_A);
		if (mos.mkRButton)chess.set(seatSub, gameEngine::PIEKEY::SET_B);
		if (mos.mkMButton)chess.set(seatSub, gameEngine::PIEKEY::CLR);*/
		if (chStatus == gameEngine::STATUS::STILL)
		{
			if (mos.mkLButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY2);
			//if (mos.mkRButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY2);
			if(chess.rule() == gameEngine::STATUS::STILL)
				chess.playSet( ai0.calOptimalPos(gameEngine::PLAYER::PLAY1), gameEngine::PLAYER::PLAY1);
				//if (KEY_DOWN(VK_NUMPAD0)) chess.playSet(ai1.calOptimalPos(gameEngine::PLAYER::PLAY2), gameEngine::PLAYER::PLAY2);
		}
		
		//if (mos.mkMButton) { chess.set(seatSub, gameEngine::PIEKEY::CLR); chess.continuePlay(); }
		if (KEY_DOWN(192)) { chess.beginPlay((gameEngine::PLAYER)(rand()%2+1)); }
	
		if (mos.mkMButton) { chess.beginPlay(gameEngine::PLAYER::PLAY1); }
		/*if (n == 1) {
			n--; chess.playSet({0,0}, gameEngine::PLAYER::PLAY1);
		}*/

		static int BoardImgc = ImgNum;
		if (KEY_DOWN(Key_ADD)) {
			if (KeyStatus[Key_ADD])
			{
				if (BoardImgc < ImgNum)++BoardImgc; else BoardImgc = 0; KeyStatus[Key_ADD] = false;
				if (BoardImgc < ImgNum)bo.BoardReload(format, pImg[BoardImgc]);
				else bo.BoardReload(format);
				chess.gameEngineReload(bo, white_pie, black_pie);
			}
		}
		else KeyStatus[Key_ADD] = true;
		if (KEY_DOWN(Key_DEL)) {
			if (KeyStatus[Key_DEL])
			{
				if (BoardImgc > 0)--BoardImgc; else BoardImgc = ImgNum; KeyStatus[Key_DEL] = false;
				if (BoardImgc < ImgNum)bo.BoardReload(format, pImg[BoardImgc]);
				else bo.BoardReload(format);
				chess.gameEngineReload(bo, white_pie, black_pie);

			}
		}
		else KeyStatus[Key_DEL] = true;

		RECT rect = { (LONG)format.margin_left, (LONG)format.margin_top,(LONG)(format.board_w - format.margin_right), (LONG)(format.board_h - format.margin_down) };
		//�ı���ʾ
		settextcolor(BLUE);
		if(clock()<7000)DrawText(GetImageHDC(), L"��ALT���Թ۲�����˳��z��x�����Թ۲����ơ�С����+,-�����л�����,����м�������ѡ�壬~�������л�����", 
			-1, 
			&rect,
			/* DT_SINGLELINE |*/ DT_CENTER | DT_VCENTER|DT_WORDBREAK| DT_PATH_ELLIPSIS| DT_TABSTOP
			
		);
		else if(clock() < 10000)DrawText(GetImageHDC(),
			L"Good luck and have fun,player!!",
			-1,
			&rect,
			/* DT_SINGLELINE |*/ DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_PATH_ELLIPSIS | DT_TABSTOP

);

		/*EzMessageBox(format.margin_left, format.margin_top,
			L"��Ļ��������һ���ڿ���̨��������Ķ�ά�ַ�����ɫ���顣  \nϵͳ�ڴ����¿���̨ʱ�ͻᴴ��һ����Ļ������������CreateFile  \
			\n����ָ��CONOUT$ֵ��ɴ򿪿���̨�ĵ�ǰ��Ļ�������� \
			\n�������CreateConsoleScreenBuffer ����Ϊ���Ŀ���̨�����������Ļ��������  \
			\nһ���µ���Ļ���������Լ��ľ������SetConsoleActiveScreenBuffer�����������Ϊ��ǰ�������� \
			\nȻ���������Ƿ��ǵ�ǰ�������������Ա������Խ��ж�ȡ��д�������"
		);*/
		settextcolor(WHITE);
		//�Ծ����
		wstring wchr;
		//gameEngine::STATUS chStatus = chess.rule();
		switch (chStatus)
		{
		case gameEngine::STATUS::STILL:wchr = { L"�Ծ���" }; break;
		case gameEngine::STATUS::WIN_PLAY1:wchr = { L"����ʤ" }; break;
		case gameEngine::STATUS::WIN_PLAY2:wchr = { L"����ʤ" }; break;
		case gameEngine::STATUS::DRAW:wchr = { L"����" }; break;
		default:break;
		}



		//����
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
		//ai��ʾ�ı�
		switch (showAIco)
		{
			//case 0:swprintf_s(tmp, L"x:%d y:%d", seatSub.x + 1, seatSub.y + 1); break;
			case 1:swprintf_s(tmp, L"AI:%ws", L"��"); break;
			case 10:swprintf_s(tmp, L"AI:%ws", L"��"); break;
			case 11:swprintf_s(tmp, L"AI:%ws", L"all"); break;
			default:swprintf_s(tmp, L" "); break;
		}
		outtextxy(
			0,
			0,
			tmp
		);

		//ѡ������
		swprintf_s(tmp, L"x:%d y:%d", seatSub.x + 1, seatSub.y + 1);
		outtextxy(
			format.board_w - 4*16,
			format.board_h - 16,
			tmp
		);

		//���̸ſ�
		int a, b, n;
		chess.stats(a, b, n);
		swprintf_s(tmp, L"A:%d B:%d N:%d", a, b, n);
		outtextxy(
			0,
			format.board_h - 16,
			tmp
		);

		swprintf_s(tmp, L"���У�%ws����(%ws)", (chess.getPlayer() == gameEngine::PLAYER::PLAY2)?L"����":L"����",wchr.c_str());
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