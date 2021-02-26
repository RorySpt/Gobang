#pragma once
#include <graphics.h>
#include "gameEngine.h"

//如果要实现AI,务必派生改类
class AI_BASE
{
public:
	virtual Board::seat calOptimalPos(gameEngine::PLAYER player) = 0; 
};

