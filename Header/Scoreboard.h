#pragma once
#include "Texture.h"
#include <vector>

class Scoreboard :public GameEntity {

private:
	std::vector<Texture*> score;
	SDL_Color color;

public:
	Scoreboard();
	Scoreboard(SDL_Color p_color);
	~Scoreboard();

	void Score(int score);
	void Render();

private:
	void ClearBoard();


};