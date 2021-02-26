#include "Piece.h"
Piece::Piece(const Piece& pie)
{
	this->colSkin = pie.colSkin;
	this->radius = pie.radius;
	this->Skin = pie.Skin;
}
Piece::Piece(IMAGE& img, int rad) : radius(rad)
{

}
Piece::Piece(COLORREF col, int rad) : radius(rad), colSkin(col)
{
	
}