#pragma once
#include <graphics.h>
#include "gameEngine.h"

//���Ҫʵ��AI,�����������
class AI_BASE
{
public:
	virtual Board::seat calOptimalPos(gameEngine::PLAYER player) = 0; 
};

