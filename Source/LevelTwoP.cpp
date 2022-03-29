#include "LevelTwoP.h"
#include "GameEntity.h" 

LevelTwoP::LevelTwoP(Player* p1, Player* p2) {
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

	player1 = p1;
	player1Hit = false;
	player1Ate = false;

	player2 = p2;
	player2Hit = false;
	player2Ate = false;

	gameOver = false;
	gameOverDelay = 2.6f;
	gameOverOn = 0.0f;
	gameOverOff = gameOverOn + 3.0f;

	topBar = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.08f));
	bar[0] = new Texture("bar_eq.png");
	bar[1] = new Texture("2-3.png");
	bar[2] = new Texture("1-3.png");
	bar[3] = new Texture("3-2.png");
	bar[4] = new Texture("3-1.png");
	bar[5] = new Texture("1-2.png");
	bar[6] = new Texture("2-1.png");
	bar[7] = new Texture("0-x.png");
	bar[8] = new Texture("x-0.png");

	for (int i = 0; i < 9; i++) {
		bar[i]->Parent(topBar);
		bar[i]->Pos(VEC2_ZERO);
	}

	cat1 = new Texture("barcat1.png");
	cat1->Parent(topBar);
	cat1->Pos(Vector2(-186.0f, 0.0f));

	cat2 = new Texture("barcat2.png");
	cat2->Parent(topBar);
	cat2->Pos(Vector2(186.0f, 0.0f));

	currentState = LevelTwoP::running;

	g = new GameoverScreen();

	HandleFishSpawning();

	waveTimer = 0.0f;
	waveTimerOff = 20.0f;

	h1 = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.2f, Graphics::Instance()->winHeight * 0.08f));
	for (int i = 0; i < 3; i++) {
		health1[i]=new Texture("heart.png");
		health1[i]->Parent(h1);
		health1[i]->Pos(Vector2(-30.0f * i, 0.0f));
	}

	h2 = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.87f, Graphics::Instance()->winHeight * 0.08f));
	for (int i = 0; i < 3; i++) {
		health2[i]=new Texture("heart.png");
		health2[i]->Parent(h2);
		health2[i]->Pos(Vector2(-30.0f * i, 0.0f));
	}

	lives1 = lives2 = 3;

	levelOver = false;
}

LevelTwoP::~LevelTwoP() {
	timer = NULL;
	background = NULL;

	delete readyLabel;
	readyLabel = NULL;

	player1 = NULL;
	player2 = NULL;

	for (int i = 0; i < fish.size(); i++) {
		delete fish[i];
		fish[i] = NULL;
	}

	for (int i = 0; i < 3; i++) {
		delete health1[i];
		health1[i]=NULL;
	}

	for (int i = 0; i < 3; i++) {
		delete health2[i];
		health2[i] = NULL;
	}

	delete topBar;
	topBar = NULL;

	for (int i = 0; i < 9; i++) {
		delete bar[i];
		bar[i] = NULL;
	}

	delete cat1;
	cat1 = NULL;

	delete cat2;
	cat2 = NULL;
}

void LevelTwoP::StartStage() {
	stageStarted = true;
}

bool LevelTwoP::StageStarted() {
	return stageStarted;
}

void LevelTwoP::HandleLabels() {
	labelTimer += timer->DeltaTime();
	if (labelTimer >= readyOff) {
		StartStage();
		readyFinished = true;
		player1->Active(true);
		player1->Visible(true);

		player2->Active(true);
		player2->Visible(true);
	}
}

void LevelTwoP::HandleCollisions() {
	if (!levelOver) {
		for (int i = 0; i < fish.size(); i++) {
			if (player1->CheckCollision(fish[i]) && fish[i]->Type() == Fish::poison) {
				player1->WasHit();
				fish[i]->WasEaten(true);
				player1Hit = true;
				if (player1Hit && lives1==3) {
					Vector2 pos = health1[2]->Pos();
					health1[2] = new Texture("emptyheart.png");
					health1[2]->Pos(pos);
					player1Hit = false;
					lives1--;
					count1 = 0;
				}
				if (player1Hit && lives1==2) {
					Vector2 pos = health1[1]->Pos();
					health1[1] = new Texture("emptyheart.png");
					health1[1]->Pos(pos);
					player1Hit = false;
					lives1--;
					count1 = 0;
				}
				if (player1Hit && lives1==1) {
					Vector2 pos = health1[0]->Pos();
					health1[0] = new Texture("emptyheart.png");
					health1[0]->Pos(pos);
					player1Hit = false;
					lives1=0;
					count1 = 0;					
				}
			}
			
			if (player2->CheckCollision(fish[i]) && fish[i]->Type() == Fish::poison) {
				player2->WasHit();
				fish[i]->WasEaten(true);
				player2Hit = true;
				if (player2Hit && lives2 == 3) {
					Vector2 pos = health2[0]->Pos();
					health2[0] = new Texture("emptyheart.png");
					health2[0]->Pos(pos);
					player2Hit = false;
					lives2--;
					count2 = 0;
				}
				if (player2Hit && lives2 == 2) {
					Vector2 pos = health2[1]->Pos();
					health2[1] = new Texture("emptyheart.png");
					health2[1]->Pos(pos);
					player2Hit = false;
					lives2--;
					count2 = 0;
				}
				if (player2Hit && lives2 == 1) {
					Vector2 pos = health2[2]->Pos();
					health2[2] = new Texture("emptyheart.png");
					health2[2]->Pos(pos);
					player2Hit = false;
					lives2 = 0;
					count2 = 0;
				}
			}
		}	
	}
}

void LevelTwoP::HandleEating() {

	if (!levelOver) {
		for (int i = 0; i < fish.size(); i++) {
			if (player1->CheckCollision(fish[i]) && fish[i]->Type() == Fish::normal) {
				totalcount1++;
				count1++;
				fish[i]->WasEaten(true);
				player1->AteFish();
				if (lives1 == 2 && count1==5) {
					Vector2 pos = health1[2]->Pos();
					health1[2] = new Texture("heart.png");
					health1[2]->Pos(pos);
					lives1++;
					count1 = 0;
				}
				if (lives1 == 1 && count1 == 5) {
					Vector2 pos = health1[1]->Pos();
					health1[1] = new Texture("heart.png");
					health1[1]->Pos(pos);
					lives1++;
					count1 = 0;
				}
			}
			if (player2->CheckCollision(fish[i]) && fish[i]->Type() == Fish::normal) {
				totalcount2++;
				count2++;
				fish[i]->WasEaten(true);
				player2->AteFish();
				if (lives2 == 2 && count2 == 5) {
					Vector2 pos = health2[0]->Pos();
					health2[0] = new Texture("heart.png");
					health2[0]->Pos(pos);
					lives2++;
					count2 = 0;
				}
				if (lives2 == 1 && count2 == 5) {
					Vector2 pos = health2[1]->Pos();
					health2[1] = new Texture("heart.png");
					health2[1]->Pos(pos);
					lives2++;
					count2 = 0;
				}
			}
		}
	}
}

void LevelTwoP::HandleDeath() {

	if (levelOver) {
		gameOverTimer += timer->DeltaTime();
		if (gameOverTimer >= gameOverDelay) {
			currentState = gameover;
			prenderDone = true;
		}
	}
}

void LevelTwoP::HandleFishSpawning() {

	for (int i = 0; i < 5; i++) {
		fish.push_back(new Fish(Fish::normal));
		fish[i]->Pos(Vector2(rand() % (Graphics::Instance()->winWidth - 85) + 85, -(float)(rand() % 100)));
	}

	for (int i = 0; i < 2; i++) {
		fish.push_back(new Fish(Fish::poison));
		fish[fish.size() - i - 1]->Pos(Vector2(rand() % (Graphics::Instance()->winWidth - 85) + 85, -(float)(rand() % 100)));
	}
}

void LevelTwoP::Push() {

	fish.push_back(new Fish(Fish::poison));
	fish[fish.size()-1]->Pos(Vector2((float)(rand() % (Graphics::Instance()->winWidth)), -(float)(rand() % 100)));

}

LevelTwoP::level_states LevelTwoP::State() {
	return currentState;
}

bool LevelTwoP::DoneDeathAnim() {
	return prenderDone;
}

void LevelTwoP::Update() {
	waveTimer += timer->DeltaTime();

	if (!stageStarted) {
		HandleLabels();
	}

	if (!levelOver) {
		player1->Update();
		player2->Update();
		if (readyFinished) {
			
			if (waveTimer > waveTimerOff) {
				Push();
				waveTimer = 0.0f;
			}
			for (int i = 0; i < fish.size(); i++) {
				fish[i]->Update();
			}
			for (int i = 0; i < 3; i++) {
				health1[i]->Update();
			}
			HandleCollisions();
			HandleEating();

			if (lives1 == 0) {
				levelOver = true;
				g->UpdateMode(GameoverScreen::grey);
				g->UpdateTotal(totalcount2);
			}
			if (lives2 == 0) {
				levelOver = true;
				g->UpdateMode(GameoverScreen::brown);
				g->UpdateTotal(totalcount1);
			}
		}
	}

	if (levelOver) {
		HandleDeath();
		player1->Active(false);
		player2->Active(false);
	}
	g->Update();
}

void LevelTwoP::Render() {
	if (!prenderDone) {

		if (lives1 == lives2)
			bar[0]->Render();
		if (lives1 == 2 && lives2 == 3)
			bar[1]->Render();
		if (lives1 == 1 && lives2 == 3)
			bar[2]->Render();
		if (lives1 == 3 && lives2 == 2)
			bar[3]->Render();
		if (lives1 == 3 && lives2 == 1)
			bar[4]->Render();
		if (lives1 == 1 && lives2 == 2)
			bar[5]->Render();
		if (lives1 == 2 && lives2 == 1)
			bar[6]->Render();
		if (lives1 == 0)
			bar[7]->Render();
		if (lives2 == 0)
			bar[8]->Render();

		cat1->Render();
		cat2->Render();

		for (int i = 0; i < 3; i++) {
			health1[i]->Render();
		}
		for (int i = 0; i < 3; i++) {
			health2[i]->Render();
		}

		if (!levelOver) {
			if (labelTimer > readyOn && labelTimer < readyOff) {
				readyLabel->Render();
			}
			player1->Render();
			player2->Render();

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
		if (levelOver) {
			if (prenderDone) {
				g->Render();
			}
		}
	}
}