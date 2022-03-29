#include "Scoreboard.h"

Scoreboard::Scoreboard()
	:Scoreboard({ 108, 93, 83 }) {
}

Scoreboard::Scoreboard(SDL_Color p_color) {
	color = p_color;

	Score(0);
}

Scoreboard::~Scoreboard() {
	ClearBoard();
}

void Scoreboard::ClearBoard() {
	for (int i = 0; i < score.size(); i++) {
		delete score[i];
		score[i] = NULL;
	}
	score.clear();
}

void Scoreboard::Score(int s) {
	ClearBoard();

	if (s == 0) {
		for (int i = 0; i < 3; i++) {
			score.push_back(new Texture("0", "bubblebutt.ttf", 40, color));
			score[i]->Parent(this);
			score[i]->Pos(Vector2((float)(-25.0*i), 0.0f));
		}
	}
	else if (s > 0 && s < 10) {
		std::string str = std::to_string(s);
		score.push_back(new Texture("0", "bubblebutt.ttf", 42, color));
		score[0]->Parent(this);
		score[0]->Pos(Vector2(-50.0f, 0.0f));

		score.push_back(new Texture("0", "bubblebutt.ttf", 42, color));
		score[1]->Parent(this);
		score[1]->Pos(Vector2(-25.0f, 0.0f));
		
		score.push_back(new Texture(str, "bubblebutt.ttf", 42, color));
		score[2]->Parent(this);
		score[2]->Pos(Vector2(0.0f, 0.0f));
		
	}
	else if (s < 100 && s>10) {
		std::string str = std::to_string(s);
		int lastIndex = str.length() - 1;
		score.push_back(new Texture("0", "bubblebutt.ttf", 42, color));
		score[0]->Parent(this);
		score[0]->Pos(Vector2(-50.0f, 0.0f));
		for (int i = 0; i <= lastIndex; i++) {
			score.push_back(new Texture(str.substr(i, 1), "bubblebutt.ttf", 40, color));
			score[i+1]->Parent(this);
			score[i+1]->Pos(Vector2(-25.0f * (lastIndex - i), 0.0f));
		}
	}
	else {
		std::string str = std::to_string(s);
		int lastIndex = str.length() - 1;
		for (int i = 0; i <= lastIndex; i++) {
			score.push_back(new Texture(str.substr(i, 1), "bubblebutt.ttf", 40, color));
			score[i]->Parent(this);
			score[i]->Pos(Vector2(-24.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Scoreboard::Render() {
	for (int i = 0; i < score.size(); i++) {
		score[i]->Render();
	}
}