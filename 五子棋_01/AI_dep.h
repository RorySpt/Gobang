#pragma once
#include "gameEngine.h"
class AI_dep
{
	struct ChessPos
	{
		//Board::seat _seat;
		size_t _score;
	};
	AI_dep(gameEngine* gEn);
	//�����δ��
	//size_t getScor(const int(&a)[9]);
	////����ִ��
	//std::vector<std::vector<ChessPos>>& Scoring(std::vector<gameEngine::STEP> _chessStep);
	////��Ȩ���
	//void PwMSA(std::vector<std::vector<ChessPos>>& ScoreMap);


	std::vector<gameEngine::STEP>chessStep;

	std::vector<std::vector<ChessPos>> ChessScoreMap[2];
	const std::vector<std::vector<int>> *ChessMap;
	const gameEngine* gEngine;
};

