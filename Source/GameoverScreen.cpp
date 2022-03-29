#include "GameoverScreen.h"

GameoverScreen::GameoverScreen() {
	rec = same;
	cat1 = new AnimatedTex("gcat.png", 0, 0, 94, 60, 2, 0.5f, AnimatedTex::horizontal);
	cat1->Parent(this);
	cat1->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.4f));

	cat2 = new AnimatedTex("gcat2.png", 0, 0, 94, 60, 2, 0.5f, AnimatedTex::horizontal);
	cat2->Parent(this);
	cat2->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.4f));

	gameOverLabel = new Texture("gameover.png");
	gameOverLabel->Parent(this);
	gameOverLabel->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.3f));

	currentScore = new Texture("gcurrentscore.png");
	highScore = new Texture("ghighscore.png");

	currentScore->Parent(this);
	highScore->Parent(this);

	currentScore->Pos(Vector2(Graphics::Instance()->winWidth * 0.4f, Graphics::Instance()->winHeight * 0.5f));
	highScore->Pos(Vector2(Graphics::Instance()->winWidth * 0.46f, Graphics::Instance()->winHeight * 0.6f));

	highS = new Scoreboard();
	highS->Score(ReadScore("highscore.txt"));
	highS->Pos(Vector2(Graphics::Instance()->winWidth * 0.7f, Graphics::Instance()->winHeight * 0.6f));

	currS = new Scoreboard();
	currS->Pos(Vector2(Graphics::Instance()->winWidth * 0.7f, Graphics::Instance()->winHeight * 0.5f));

	newRecord = new Texture("gnewrecord.png");
	newRecord->Parent(this);
	newRecord->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.5));

	record = new Scoreboard();
	record->Pos(Vector2(Graphics::Instance()->winWidth * 0.52f, Graphics::Instance()->winHeight * 0.58f));

	youWon = new Texture("youwon.png");
	youWon->Parent(this);
	youWon->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.5));

	yourTotal = new Texture("yourtotal.png");
	yourTotal->Parent(this);
	yourTotal->Pos(Vector2(Graphics::Instance()->winWidth * 0.44f, Graphics::Instance()->winHeight * 0.58f));

	yourScore = new Scoreboard();
	yourScore->Pos(Vector2(Graphics::Instance()->winWidth * 0.78f, Graphics::Instance()->winHeight * 0.58f));

	controls = new Texture("gcontrols.png");
	controls->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.72));
}

GameoverScreen::~GameoverScreen() {
	delete cat1;
	cat1 = NULL;

	delete cat2;
	cat2 = NULL;

	delete gameOverLabel;
	gameOverLabel = NULL;

	delete currentScore;
	currentScore = NULL;

	delete highScore;
	highScore = NULL;

	delete highS;
	highS = NULL;

	delete currS;
	currS = NULL;

	delete newRecord;
	newRecord = NULL;

	delete record;
	record = NULL;

	delete youWon;
	youWon = NULL;

	delete yourScore;
	yourScore = NULL;

	delete yourTotal;
	yourTotal = NULL;

	delete controls;
	controls = NULL;
}

int GameoverScreen::ReadScore(std::string filename) {
	std::string s = SDL_GetBasePath();
	s.append("Assets/" + filename);

	std::ifstream input(s);

	int x;
	input >> x;

	return x;
}

void GameoverScreen::UpdateCurrent(int n) {
	currS->Score(n);
}

void GameoverScreen::UpdateRecord(int n) {
	record->Score(n);
}

void GameoverScreen::UpdateMode(Record r) {
	rec = r;
}
void GameoverScreen::UpdateTotal(int n) {
	yourScore->Score(n);
}

void GameoverScreen::Update() {
	
	gameOverLabel->Update();
	if (rec == same) {
		cat1->Update();
		highScore->Update();
		currentScore->Update();
	}
	if (rec == newrecord) {
		cat1->Update();
		newRecord->Update();
		record->Update();
	}
	if (rec == grey) {
		cat2->Update();
		youWon->Update();
	}
	if (rec == brown) {
		cat1->Update();
		youWon->Update();
	}
}

void GameoverScreen::Render() {
	
	gameOverLabel->Render();
	if (rec == same) {
		cat1->Render();
		highScore->Render();
		currentScore->Render();
		currS->Render();
		highS->Render();
	}
	if (rec == newrecord) {
		cat1->Render();
		newRecord->Render();
		record->Render();
	}
	if (rec == grey) {
		cat2->Render();
		youWon->Render();
		yourScore->Render();
		yourTotal->Render();
	}
	if (rec == brown) {
		cat1->Render();
		youWon->Render();
		yourScore->Render();
		yourTotal->Render();
	}

	controls->Render();
}
