#pragma once
#include <graphics.h>


class Board
{
public:
	struct seat
	{
		int x;
		int y;
	};
	struct BoardFormat
	{
		//盘线规格
		size_t GridLines_Spacing = 20;
		size_t GridLines_Nx = 19;
		size_t GridLines_Ny = 19;
		COLORREF LinesColor = BLACK;
		//棋盘边距
		size_t margin_top = 30;
		size_t margin_down = 30;
		size_t margin_left = 30;
		size_t margin_right = 30;
		//棋盘大小
		size_t board_w = 0;
		size_t board_h = 0;
		
		
		int aligning_grid()
		{
			board_h = board_w;
			GridLines_Spacing = board_w / 22;
			board_w = GridLines_Spacing * 22;
			size_t GridLines_Nx = 19;
			size_t GridLines_Ny = 19;
			size_t margin = 2 * GridLines_Spacing;
			margin_top = margin;
			margin_down = margin;
			margin_left = margin;
			margin_right = margin;
		}
		void aligning_size()
		{
			board_h = margin_top + margin_down + (GridLines_Ny - 1) * GridLines_Spacing;
			board_w = margin_left + margin_right + (GridLines_Nx - 1) * GridLines_Spacing;
		}

		bool operator==(const BoardFormat& _format)const
		{
			if (
				this->GridLines_Spacing == _format.GridLines_Spacing
				&& this->GridLines_Nx == _format.GridLines_Nx
				&& this->GridLines_Ny == _format.GridLines_Ny
				&& this->margin_top == _format.margin_top
				&& this->margin_down == _format.margin_down
				&& this->margin_left == _format.margin_left
				&& this->margin_right == _format.margin_right

				)return true;
			else return false;
		}
		bool operator!=(const BoardFormat& _format)const
		{
			if (*this == _format)return false;
			else return true;
		}
	};
public:
	Board(const BoardFormat &Format, LPCTSTR pImgFile) ;
	Board(const BoardFormat& Format, const IMAGE BoardGrund);
	Board(const BoardFormat& Format, COLORREF BoardGrund = RGB(255, 205, 150)) ;
	Board(const Board& bo);
	void BoardReload(const BoardFormat& Format, COLORREF BoardGrund = RGB(255, 205, 150));
	void BoardReload(const BoardFormat& Format, const IMAGE BoardGrund);
	void BoardReload(const BoardFormat& Format, LPCTSTR pImgFile);
	void BoardReload(const Board& bo);
	const IMAGE& BoardImage();
	const BoardFormat& getFormat()const;


	seat getSeatsub(int x,int y)
	{
		seat res;
		res.x = int(((double)x - format.margin_left) / format.GridLines_Spacing + 0.5);
		res.y = int(((double)y - format.margin_top) / format.GridLines_Spacing + 0.5);
		if ((size_t)res.x < 0)res.x = 0;
		if ((size_t)res.x >= format.GridLines_Nx)res.x = format.GridLines_Nx - 1;
		if ((size_t)res.y < 0)res.y = 0;
		if ((size_t)res.y >= format.GridLines_Ny)res.y = format.GridLines_Ny - 1;
		return res;
	}
	seat findSeat(seat _seat)
	{
		seat res;
		res.x = format.margin_left + format.GridLines_Spacing * (_seat.x);
		res.y = format.margin_top + format.GridLines_Spacing * (_seat.y);
		return res;
	}
	seat getSeat(int x, int y)
	{
		seat res;
		seat sub(getSeatsub(x,y));

		res.x = format.margin_left + format.GridLines_Spacing * (sub.x);
		res.y = format.margin_top + format.GridLines_Spacing * (sub.y);
		return res;
	}
private:
	BoardFormat format;
	IMAGE board;
};



