#pragma once
#include <vector>
#include "gameEngine.h"
class AI
{
	//struct Mark
	//{
	//	size_t score;
	//};
public:	
	enum class MarkTable
	{
		null	= 1,
		die2	= 2,
		die3	= 3,
		l_live2 = 9,
		live2	= 10,
		d_live2 = 50,
		j_live3 = 90,
		live3	= 100,
		l_die4	= 400,
		die4	= 500,
		d3l3	= 1000,
		d_live3	= 5000,
		d4l3	= 10000,	live4 = 10000, d_die = 10000,
		su		= 100000
	};
	
	void Scoring(gameEngine::PLAYER player);
public:
	AI(gameEngine* gEn) :gEngine(gEn) 
	{ 
		pieMark_player[0].resize(gEngine->seeChess().size());
		for (int ix(0); ix != gEngine->seeChess().size(); ++ix)
			pieMark_player[0][ix].resize(gEngine->seeChess()[ix].size());
		pieMark_player[1]=pieMark_player[0];
	};

	const	Board::seat& calOptimalPos(gameEngine::PLAYER player);

	const std::vector<std::vector<size_t>>& showMark(gameEngine::PLAYER player)
	{
		if (player == gameEngine::PLAYER::null)return (std::vector<std::vector<size_t>>) NULL;
		return pieMark_player[(int)player - 1];
	}

private:
	std::vector<std::vector<size_t>> pieMark_player[2];
	gameEngine* gEngine;
};

