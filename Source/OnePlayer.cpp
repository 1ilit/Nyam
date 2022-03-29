#include "OnePlayer.h"

OnePlayer::OnePlayer() {
	timer = Timer::Instance();
	input = InputMgr::Instance();

	background = Background::Instance();
	grass = new Texture("grass1.png");
	grass->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.95f));

	labelTimer = 0.0f;

	//top bar
	topBar = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.08f));
	highScore = new Texture("highscore.png");
	highScore->Parent(topBar);
	highScore->Pos(VEC2_ZERO);

	score=new Scoreboard({ 108, 93, 83 });
	score->Score(ReadScore("highscore.txt"));
	score->Parent(topBar);
	score->Pos(Vector2(10.0f, 40.0f));
	
	dinner = new Texture("dinner.png");
	dinner->Parent(this);
	dinner->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.5f));

	dinnerOn = 0.0f;
	dinnerOff = 2.0f;

	instr = new Texture("food.png");
	instr->Parent(this);
	instr->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.5f));

	instrOn = dinnerOff;
	instrOff = dinnerOff + 2.0f;

	conPanel = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.5));
	controls = new Texture("controls1.png");
	esc = new Texture("controls2.png");
	enterStart = new Texture("controls3.png");

	controls->Parent(conPanel);
	esc->Parent(conPanel);
	enterStart->Parent(conPanel);

	controls->Pos(Vector2(0.0f, -50.0f));
	esc->Pos(Vector2(0.0f, 0.0f));
	enterStart->Pos(Vector2(0.0f, 50.0f));

	controlsOn = instrOff;

	cat = new Player(0);
	cat->Parent(this);
	cat->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.796f));

	levelStarted = false;

	gameStarted = false;

}

OnePlayer::~OnePlayer() {
	delete grass;
	grass = NULL;

	delete highScore;
	highScore = NULL;

	delete instr;
	instr = NULL;

	delete controls;
	controls = NULL;

	delete esc;
	esc = NULL;

	delete enterStart;
	enterStart = NULL;

	delete cat;
	cat = NULL;


}

int OnePlayer::ReadScore(std::string filename) {
	std::string s = SDL_GetBasePath();
	s.append("Assets/" + filename);

	std::ifstream input(s);

	int highScore;
	input >> highScore;

	return highScore;
}


void OnePlayer::StartLevel() {

	levelStarted = true;
	
	level = new Level(cat);
}

void OnePlayer::SetStartedLevel(bool b) {
	levelStarted = b;
}

bool OnePlayer::GameOver() {
	if (!levelStarted)
		return false;

	return level->State() == Level::gameover;
}

void OnePlayer::Activate() {
	cat->Active(true);
}

void OnePlayer::Center() {
	cat->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.796f));
}

void OnePlayer::Update() {
	labelTimer += timer->DeltaTime();
	if (gameStarted) {
		background->Update();

		grass->Update();

		if (!levelStarted) {
			StartLevel();
		}
		if (levelStarted) {
			level->Update();

			if (level->State() == Level::gameover && input->KeyPressed(SDL_SCANCODE_SPACE)) {
				levelStarted = false;
				Activate();
				Center();

			}
		}
		cat->Update();
	}
	else {
		if (input->KeyPressed(SDL_SCANCODE_RETURN)) {
			gameStarted = true;
		}

		cat->Update();
	}
	
}


void OnePlayer::Render() {
	if(levelStarted && !level->DoneDeathAnim())
		cat->Render();
	
	if (!gameStarted) {

		if (labelTimer > dinnerOn && labelTimer < dinnerOff) {
			dinner->Render();
		}
		if (labelTimer > instrOn && labelTimer < instrOff) {
			instr->Render();
		}
		if (labelTimer > controlsOn) {
			controls->Render();
			esc->Render();
			enterStart->Render();
		}
		if (!levelStarted) {
			highScore->Render();
			score->Render();
		}

	}

	if (gameStarted) {

		if (levelStarted)
			level->Render();	
	}
	
	grass->Render();
	
}