#include "Level.h"
#include "GameEntity.h"


Level::Level(Player* p) {
	timer = Timer::Instance();
	background = Background::Instance();

	readyFinished = false;

	stage = 0;
	stageStarted = false;

	labelTimer = 0.0f;
	readyLabel = new Texture("ready.png");
	readyLabel->Parent(this);
	readyLabel->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.5f));

	readyOn = 0.0f;
	readyOff = readyOn + 3.0f;

	player = p;
	playerHit = false;

	gameOver = false;
	gameOverDelay = 2.6f;
	gameOverOn = 0.0f;
	gameOverOff = gameOverOn+3.0f;

	topBar = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.08f));

	highScore = new Texture("highscore.png");
	highScore->Parent(topBar);
	highScore->Pos(Vector2(-280.0f, 0.0f));
 
	highS = new Scoreboard({ 108, 93, 83 });
	highS->Score(ReadScore("highscore.txt"));
	highS->Parent(topBar);
	highS->Pos(Vector2(-250.0f, 40.0f));

	currentScore = new Texture("currentscore.png");
	currentScore->Parent(topBar);
	currentScore->Pos(Vector2(230.0f, 0.0f));

	currS = new Scoreboard({ 108, 93, 83 });
	currS->Score(count);
	currS->Parent(topBar);
	currS->Pos(Vector2(250.0f, 40.0f));

	currentState = Level::running;

	playerAte = false;

	g = new GameoverScreen();
	
	HandleFishSpawning();

	waveTimer = 0.0f;
	waveTimerOff = 20.0f;
}

Level::~Level() {
	timer = NULL;
	background = NULL;

	delete readyLabel;
	readyLabel = NULL;

	player = NULL;

	for (int i = 0; i < fish.size(); i++) {
		delete fish[i];
		fish[i] = NULL;
	}

	delete currentScore;
	currentScore = NULL;

	delete highScore;
	highScore = NULL;

	delete currS;
	currS = NULL;

	delete highS;
	highS = NULL;
}

void Level::StartStage() {
	stageStarted = true;
}

bool Level::StageStarted() {
	return stageStarted;
}

void Level::HandleLabels() {
	labelTimer += timer->DeltaTime();
	if (labelTimer >= readyOff) {
		StartStage();
		readyFinished = true;
		player->Active(true);
		player->Visible(true);
	}
}

void Level::HandleCollisions() {
	if (!playerHit) {
		for (int i = 0; i < fish.size(); i++) {
			if (player->CheckCollision(fish[i]) && fish[i]->Type() == Fish::poison) {
				player->WasHit();
				playerHit = true;
			}
		}
	}
}

int Level::ReadScore(std::string filename) {
	std::string s = SDL_GetBasePath();
	s.append("Assets/" + filename);

	std::ifstream input(s);

	int highScore;
	input >> highScore;
	
	return highScore;
}

void Level::WriteScore(std::string filename, int n) {
	std::string s = SDL_GetBasePath();
	s.append("Assets/" + filename);

	std::ofstream output(s);
	output << n;
}

void Level::HandleEating() {
	
	if (!playerHit) {
		for (int i = 0; i < fish.size(); i++) {
			if (player->CheckCollision(fish[i]) && fish[i]->Type()==Fish::normal) {
				count++;
				currS->Score(count);
				fish[i]->WasEaten(true);
				player->AteFish();
				playerAte = true;
			}
		}
		
	}
	if (!player->IsEating()) {
		playerAte = false;
	}
}

void Level::HandleDeath() {

	if (playerHit) {
		gameOverTimer += timer->DeltaTime();
		if (gameOverTimer >= gameOverDelay) {
			currentState = gameover;
			prenderDone = true;
			g->UpdateCurrent(count);
		}
	}
}
	

void Level::HandleFishSpawning() {
	
	for (int i = 0; i < 5; i++) {
		fish.push_back(new Fish(Fish::normal));
		fish[i]->Pos(Vector2(rand() % (Graphics::Instance()->winWidth - 85) + 85, -(float)(rand() % 100)));
	}

	for (int i = 0; i < 2; i++) {
		fish.push_back(new Fish(Fish::poison));
		fish[fish.size()-i-1]->Pos(Vector2(rand() % (Graphics::Instance()->winWidth - 105) + 85, -(float)(rand() % 100)));
	}
}

void Level::Push() {

	fish.push_back(new Fish(Fish::poison));
	fish[fish.size()-1]->Pos(Vector2((float)(rand() % (Graphics::Instance()->winWidth)), -(float)(rand() % 100)));

}

Level::level_states Level::State() {
	return currentState;
}

bool Level::DoneDeathAnim() {
	return prenderDone;
}

void Level::Update() {
	waveTimer += timer->DeltaTime();

	highScore->Update();
	highS->Update();

	currentScore->Update();
	currS->Update();

	if (!stageStarted) {
		HandleLabels();
	}

	if (!playerHit) {
		player->Update();
		if (readyFinished) {
			HandleCollisions();
			HandleEating();
			if (waveTimer > waveTimerOff) {
				Push();
				waveTimer = 0.0f;
			}
			for (int i = 0; i < fish.size(); i++) {
				fish[i]->Update();
			}
		}
	}

	if (playerHit) {
		HandleDeath();
		player->Active(false);
		int h = ReadScore("highscore.txt");
		if (count > h) {
			WriteScore("highscore.txt", count);
			g->UpdateCurrent(count);
			g->UpdateMode(GameoverScreen::newrecord);
			g->UpdateRecord(count);
		}
	}
	g->Update();
}

void Level::Render() {
	if (!prenderDone) {
		highScore->Render();
		highS->Render();

		currentScore->Render();
		currS->Render();

		if (!playerHit) {
			if (labelTimer > readyOn && labelTimer < readyOff) {
				readyLabel->Render();
			}
			player->Render();

			if (readyFinished) {
				for (int i = 0; i < fish.size(); i++) {
					if (!fish[i]->WasEaten()) {
						fish[i]->Render();
					}
				}
			}
		}
	}
	else {	
		if (playerHit) {		
			if (gameOverTimer >= gameOverDelay) {
				g->Render();
			}		
		}
	}
}