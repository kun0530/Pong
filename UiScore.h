#pragma once
#include "TextGo.h"

// SCORE = ??

class UiScore : public TextGo
{
protected:
	std::string textFormat = "SCORE: ";
	int score = 0;

public:
	UiScore(const std::string& name = "");

	void Reset() override;

	void SetScore(int score);
	int GetScore() { return score; };

	void AddScore(int addedScore);
	void AddScore2(int addedScore);

};

