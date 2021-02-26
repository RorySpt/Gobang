#include <graphics.h>
#include "board.h"
#include "Piece.h"
#include "gameEngine.h"
#include <string>
using namespace std;
LPCTSTR pImg[10] = { 
	L"E:/��ֽ/wallhaven-739712.jpg", 
	L"C:/Users/zhang/Pictures/Saved Pictures/v2-0963de0885224e9da786aff051d1b536_r.jpg",
	L"C:/Users/zhang/Pictures/Saved Pictures/v2-64736fe98876a48978f980965c5a4b89_r.jpg",
	L"E:/��ֽ/wallhaven-730881.jpg",
	L"E:/��ֽ/wallhaven-742272.jpg",
	L"E:/��ֽ/wallhaven-743498.png",
	L"E:/��ֽ/wallhaven-727341.jpg",
	L"E:/��ֽ/wallhaven-729634.jpg",
	L"E:/��ֽ/wallhaven-739712.jpg",
	L"E:/��ֽ/wallhaven-739712.jpg",
};

void mouseSet()
{
	
	HCURSOR hcur = (HCURSOR)LoadImage(NULL, _T("C:\\Windows\\Cursors\\aero_link_l.cur"), IMAGE_CURSOR, 40, 40, LR_LOADFROMFILE);
	HWND hwnd = GetHWnd();							// ��ȡ��ͼ���ھ��
	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	// ���ô�����������ʽ
}

int main()
{

	
	
	Board::BoardFormat format({30,19,19});
	format.aligning_size();
	//��������
	Piece black_pie(BLACK, int(format.GridLines_Spacing * 0.4));
	Piece white_pie(WHITE, int(format.GridLines_Spacing * 0.4));

	//��������
	Board bo(format/*, pImg[0]*/);
	//Board bo(format, RGB(255, 205, 150));

	//���ڳ�ʼ��
	initgraph(bo.getFormat().board_w, bo.getFormat().board_h);

	//�������
	gameEngine chess (bo,  white_pie, black_pie);

	

	BeginBatchDraw();

	//���
	MOUSEMSG mos(GetMouseMsg());
	mouseSet();
	chess.beginPlay(gameEngine::PLAYER::PLAY1);
	while (1)
	{
		cleardevice();

		//����������
		chess.put(NULL);
		//��׽������
		if(MouseHit())mos = GetMouseMsg();
		FlushMouseMsgBuffer();
		if(!mos.mkLButton)circle(mos.x,mos.y,5);
		else fillcircle(mos.x, mos.y, 5);
		Board::seat seat = bo.getSeat(mos.x, mos.y);
		//��ʾѡ�п�
		rectangle(seat.x + format.GridLines_Spacing/2, seat.y + format.GridLines_Spacing / 2, seat.x - format.GridLines_Spacing / 2, seat.y - format.GridLines_Spacing / 2);
		
		/*if (mos.mkLButton)black_pie.put(NULL, seat);
		if (mos.mkRButton)white_pie.put(NULL, seat);*/
		Board::seat seatSub = bo.getSeatsub(mos.x, mos.y);


		//��������
		/*if (mos.mkLButton)chess.set(seatSub,gameEngine::PIEKEY::SET_A);
		if (mos.mkRButton)chess.set(seatSub, gameEngine::PIEKEY::SET_B);
		if (mos.mkMButton)chess.set(seatSub, gameEngine::PIEKEY::CLR);*/

		if (mos.mkLButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY1);
		if (mos.mkRButton)chess.playSet(seatSub, gameEngine::PLAYER::PLAY2);
		//if (mos.mkMButton) { chess.set(seatSub, gameEngine::PIEKEY::CLR); chess.continuePlay(); }
		if (mos.mkMButton) { chess.beginPlay(gameEngine::PLAYER::PLAY1); }


		//�ı���ʾ

		//����
		setbkmode(TRANSPARENT);
		WCHAR tmp[20];
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

		swprintf_s(tmp, L"���У�%ws����", (chess.getPlayer() == gameEngine::PLAYER::PLAY2)?L"����":L"����");
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