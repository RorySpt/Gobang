#include "board.h"
using namespace std;
Board::Board(const Board& bo)
{
	this->board = bo.board;
	this->format = bo.format;
}

Board::Board(const BoardFormat& Format, LPCTSTR pImgFile) :format(Format)
{
	IMAGE BoardGrund;
	//load
	size_t temp = format.board_w > format.board_h ? format.board_w : format.board_h;
	loadimage(&BoardGrund, pImgFile, 0, 0, true);
	float resw((float)temp * BoardGrund.getwidth() / BoardGrund.getheight()), resh((float)temp);
	if (BoardGrund.getwidth() < BoardGrund.getheight())
	{
		resw = (float)temp;
		resh = (float)temp * BoardGrund.getheight() / BoardGrund.getwidth();
	}
	loadimage(&BoardGrund, pImgFile, (int)resw, (int)resh, true);

	format.board_h = format.margin_top + format.margin_down + (format.GridLines_Ny - 1) * format.GridLines_Spacing;
	format.board_w = format.margin_left + format.margin_right + (format.GridLines_Nx - 1) * format.GridLines_Spacing;

	board.Resize(format.board_w, format.board_w);

	IMAGE* imgBuffer = GetWorkingImage();
	SetWorkingImage(&board);

	putimage(0, 0, &BoardGrund);

	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	//solidrectangle(0, 0, format.board_w - 1, format.board_w - 1);


	setbkcolor(BLACK);

	setbkmode(TRANSPARENT);
	setlinecolor(format.LinesColor);
	//setlinestyle(format.pLstyle);
	settextcolor(format.LinesColor);
	//纵线
	for (size_t ix(0); ix < format.GridLines_Nx; ++ix)
	{
		WCHAR s[5];
		wsprintf(s, L"%d", ix + 1);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left + ix * format.GridLines_Spacing - tW / 2, format.margin_top - tH, s);

		line(format.margin_left + ix * format.GridLines_Spacing, format.margin_top, format.margin_left + ix * format.GridLines_Spacing, format.board_h - format.margin_down);
	}
	//横线
	for (size_t ix(0); ix < format.GridLines_Ny; ++ix)
	{
		WCHAR s;
		if (ix < 26) s = (WCHAR)('A' + ix);
		else s = (WCHAR)('a' + ix - 26);
		//wsprintf(s, L"%d", ix);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left - tW - 2, format.margin_top + ix * format.GridLines_Spacing - tH / 2, s);

		line(format.margin_left, format.margin_top + ix * format.GridLines_Spacing, format.board_w - format.margin_right, format.margin_top + ix * format.GridLines_Spacing);
	}
	SetWorkingImage(imgBuffer);
}


Board::Board(const BoardFormat& Format, const IMAGE BoardGrund) :format(Format)
{
	format.board_h = format.margin_top + format.margin_down + (format.GridLines_Ny - 1) * format.GridLines_Spacing;
	format.board_w = format.margin_left + format.margin_right + (format.GridLines_Nx - 1) * format.GridLines_Spacing;

	board.Resize(format.board_w, format.board_w);

	IMAGE* imgBuffer = GetWorkingImage();
	SetWorkingImage(&board);

	putimage(0, 0, &BoardGrund);

	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	//solidrectangle(0, 0, format.board_w - 1, format.board_w - 1);


	setbkcolor(BLACK);

	setbkmode(TRANSPARENT);

	setlinecolor(format.LinesColor);
	//setlinestyle(format.pLstyle);
	settextcolor(format.LinesColor);
	//纵线
	for (size_t ix(0); ix < format.GridLines_Nx; ++ix)
	{
		WCHAR s[5];
		wsprintf(s, L"%d", ix + 1);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left + ix * format.GridLines_Spacing - tW / 2, format.margin_top - tH, s);

		line(format.margin_left + ix * format.GridLines_Spacing, format.margin_top, format.margin_left + ix * format.GridLines_Spacing, format.board_h - format.margin_down);
	}
	//横线
	for (size_t ix(0); ix < format.GridLines_Ny; ++ix)
	{
		WCHAR s;
		if (ix < 26) s = (WCHAR)('A' + ix);
		else s = (WCHAR)('a' + ix - 26);
		//wsprintf(s, L"%d", ix);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left - tW - 2, format.margin_top + ix * format.GridLines_Spacing - tH / 2, s);

		line(format.margin_left, format.margin_top + ix * format.GridLines_Spacing, format.board_w - format.margin_right, format.margin_top + ix * format.GridLines_Spacing);
	}
	SetWorkingImage(imgBuffer);
}
Board::Board(const BoardFormat &Format, COLORREF BoardGrund ):format(Format)
{
	format.board_h = format.margin_top + format.margin_down + (format.GridLines_Ny - 1) * format.GridLines_Spacing;
	format.board_w = format.margin_left + format.margin_right + (format.GridLines_Nx - 1) * format.GridLines_Spacing;

	board.Resize(format.board_w, format.board_w);

	IMAGE* imgBuffer = GetWorkingImage();
	SetWorkingImage(&board);

	setfillcolor(BoardGrund);
	setfillstyle(BS_SOLID);
	solidrectangle(0, 0, format.board_w - 1, format.board_w - 1);
	

	setbkcolor(BoardGrund);

	setbkmode(TRANSPARENT);
	setlinecolor(format.LinesColor);
	//setlinestyle(format.pLstyle);
	settextcolor(format.LinesColor);
	//纵线
	for (size_t ix(0); ix < format.GridLines_Nx; ++ix)
	{
		WCHAR s[5];
		wsprintf(s, L"%d", ix + 1);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left + ix * format.GridLines_Spacing - tW / 2, format.margin_top - tH, s);

		line(format.margin_left + ix * format.GridLines_Spacing, format.margin_top, format.margin_left + ix * format.GridLines_Spacing, format.board_h - format.margin_down);
	}
	//横线
	for (size_t ix(0); ix < format.GridLines_Ny; ++ix)
	{
		WCHAR s;
		if (ix < 26) s = (WCHAR)('A' + ix);
		else s = (WCHAR)('a' + ix - 26);
		//wsprintf(s, L"%d", ix);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left - tW - 2, format.margin_top + ix * format.GridLines_Spacing - tH / 2, s);

		line(format.margin_left, format.margin_top + ix * format.GridLines_Spacing, format.board_w - format.margin_right, format.margin_top + ix * format.GridLines_Spacing);
	}
	SetWorkingImage(imgBuffer);
}
//void Board::flushBoard(BoardFormat Format, IMAGE BoardGrund);
//void Board::flushBoard(BoardFormat Format, COLORREF BoardGrund);
const IMAGE& Board::BoardImage()
{
	return board;
}

const Board::BoardFormat& Board::getFormat() const
{
	return format;
}


void Board::BoardReload(const BoardFormat& Format, COLORREF BoardGrund )
{
	format = Format;
	format.board_h = format.margin_top + format.margin_down + (format.GridLines_Ny - 1) * format.GridLines_Spacing;
	format.board_w = format.margin_left + format.margin_right + (format.GridLines_Nx - 1) * format.GridLines_Spacing;

	board.Resize(format.board_w, format.board_w);

	IMAGE* imgBuffer = GetWorkingImage();
	SetWorkingImage(&board);

	setfillcolor(BoardGrund);
	setfillstyle(BS_SOLID);
	solidrectangle(0, 0, format.board_w - 1, format.board_w - 1);


	setbkcolor(BoardGrund);

	setbkmode(TRANSPARENT);
	setlinecolor(format.LinesColor);
	//setlinestyle(format.pLstyle);
	settextcolor(format.LinesColor);
	//纵线
	for (size_t ix(0); ix < format.GridLines_Nx; ++ix)
	{
		WCHAR s[5];
		wsprintf(s, L"%d", ix + 1);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left + ix * format.GridLines_Spacing - tW / 2, format.margin_top - tH, s);

		line(format.margin_left + ix * format.GridLines_Spacing, format.margin_top, format.margin_left + ix * format.GridLines_Spacing, format.board_h - format.margin_down);
	}
	//横线
	for (size_t ix(0); ix < format.GridLines_Ny; ++ix)
	{
		WCHAR s;
		if (ix < 26) s = (WCHAR)('A' + ix);
		else s = (WCHAR)('a' + ix - 26);
		//wsprintf(s, L"%d", ix);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left - tW - 2, format.margin_top + ix * format.GridLines_Spacing - tH / 2, s);

		line(format.margin_left, format.margin_top + ix * format.GridLines_Spacing, format.board_w - format.margin_right, format.margin_top + ix * format.GridLines_Spacing);
	}
	SetWorkingImage(imgBuffer);
}
void Board::BoardReload(const BoardFormat& Format, const IMAGE BoardGrund)
{
	format = Format;
	format.board_h = format.margin_top + format.margin_down + (format.GridLines_Ny - 1) * format.GridLines_Spacing;
	format.board_w = format.margin_left + format.margin_right + (format.GridLines_Nx - 1) * format.GridLines_Spacing;

	board.Resize(format.board_w, format.board_w);

	IMAGE* imgBuffer = GetWorkingImage();
	SetWorkingImage(&board);

	putimage(0, 0, &BoardGrund);

	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	//solidrectangle(0, 0, format.board_w - 1, format.board_w - 1);


	setbkcolor(BLACK);

	setbkmode(TRANSPARENT);

	setlinecolor(format.LinesColor);
	//setlinestyle(format.pLstyle);
	settextcolor(format.LinesColor);
	//纵线
	for (size_t ix(0); ix < format.GridLines_Nx; ++ix)
	{
		WCHAR s[5];
		wsprintf(s, L"%d", ix + 1);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left + ix * format.GridLines_Spacing - tW / 2, format.margin_top - tH, s);

		line(format.margin_left + ix * format.GridLines_Spacing, format.margin_top, format.margin_left + ix * format.GridLines_Spacing, format.board_h - format.margin_down);
	}
	//横线
	for (size_t ix(0); ix < format.GridLines_Ny; ++ix)
	{
		WCHAR s;
		if (ix < 26) s = (WCHAR)('A' + ix);
		else s = (WCHAR)('a' + ix - 26);
		//wsprintf(s, L"%d", ix);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left - tW - 2, format.margin_top + ix * format.GridLines_Spacing - tH / 2, s);

		line(format.margin_left, format.margin_top + ix * format.GridLines_Spacing, format.board_w - format.margin_right, format.margin_top + ix * format.GridLines_Spacing);
	}
	SetWorkingImage(imgBuffer);
}
void Board::BoardReload(const BoardFormat& Format, LPCTSTR pImgFile)
{
	format = Format;
	IMAGE BoardGrund;
	//load
	size_t temp = format.board_w > format.board_h ? format.board_w : format.board_h;
	loadimage(&BoardGrund, pImgFile, 0, 0, true);
	float resw((float)temp * BoardGrund.getwidth() / BoardGrund.getheight()), resh((float)temp);
	if (BoardGrund.getwidth() < BoardGrund.getheight())
	{
		resw = (float)temp;
		resh = (float)temp * BoardGrund.getheight() / BoardGrund.getwidth();
	}
	loadimage(&BoardGrund, pImgFile, (int)resw, (int)resh, true);

	format.board_h = format.margin_top + format.margin_down + (format.GridLines_Ny - 1) * format.GridLines_Spacing;
	format.board_w = format.margin_left + format.margin_right + (format.GridLines_Nx - 1) * format.GridLines_Spacing;

	board.Resize(format.board_w, format.board_w);

	IMAGE* imgBuffer = GetWorkingImage();
	SetWorkingImage(&board);

	putimage(0, 0, &BoardGrund);

	setfillcolor(BLACK);
	setfillstyle(BS_SOLID);
	//solidrectangle(0, 0, format.board_w - 1, format.board_w - 1);


	setbkcolor(BLACK);

	setbkmode(TRANSPARENT);
	setlinecolor(format.LinesColor);
	//setlinestyle(format.pLstyle);
	settextcolor(format.LinesColor);
	//纵线
	for (size_t ix(0); ix < format.GridLines_Nx; ++ix)
	{
		WCHAR s[5];
		wsprintf(s, L"%d", ix + 1);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left + ix * format.GridLines_Spacing - tW / 2, format.margin_top - tH, s);

		line(format.margin_left + ix * format.GridLines_Spacing, format.margin_top, format.margin_left + ix * format.GridLines_Spacing, format.board_h - format.margin_down);
	}
	//横线
	for (size_t ix(0); ix < format.GridLines_Ny; ++ix)
	{
		WCHAR s;
		if (ix < 26) s = (WCHAR)('A' + ix);
		else s = (WCHAR)('a' + ix - 26);
		//wsprintf(s, L"%d", ix);
		int tH(textheight(s)), tW(textwidth(s));
		outtextxy(format.margin_left - tW - 2, format.margin_top + ix * format.GridLines_Spacing - tH / 2, s);

		line(format.margin_left, format.margin_top + ix * format.GridLines_Spacing, format.board_w - format.margin_right, format.margin_top + ix * format.GridLines_Spacing);
	}
	SetWorkingImage(imgBuffer);
}


void Board::BoardReload(const Board& bo)
{
	this->board = bo.board;
	this->format = bo.format;
}

