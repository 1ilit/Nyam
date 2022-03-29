#include "TwoPlayer.h"

TwoPlayer::TwoPlayer() {
	timer = Timer::Instance();
	input = InputMgr::Instance();

	background = Background::Instance();
	grass = new Texture("grass1.png");
	grass->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.95f));

	labelTimer = 0.0f;

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

	conPanel1 = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.3f, Graphics::Instance()->winHeight * 0.5));
	controls = new Texture("controls21.png");
	esc = new Texture("controls2.png");

	controls->Parent(conPanel1);
	esc->Parent(this);

	controls->Pos(Vector2(0.0f, -50.0f));
	esc->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.52));

	conPanel2 = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.7f, Graphics::Instance()->winHeight * 0.5));
	controls2 = new Texture("controls23.png");
	controls2->Parent(conPanel2);
	controls2->Pos(Vector2(0.0f, -50.0f));

	enterStart = new Texture("controls3.png");
	enterStart->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.6));

	controlsOn = instrOff;

	cat1 = new Player(0);
	cat1->Parent(this);
	cat1->Pos(Vector2(Graphics::Instance()->winWidth * 0.3f, Graphics::Instance()->winHeight * 0.796f));

	cat2 = new Player(1);
	cat2->Parent(this);
	cat2->Pos(Vector2(Graphics::Instance()->winWidth * 0.7f, Graphics::Instance()->winHeight * 0.796f));

	levelStarted = false;

	gameStarted = false;

}

TwoPlayer::~TwoPlayer() {
	delete grass;
	grass = NULL;

	delete instr;
	instr = NULL;

	delete controls;
	controls = NULL;

	delete esc;
	esc = NULL;

	delete controls2;
	controls2 = NULL;

	delete enterStart;
	enterStart = NULL;

	delete cat1;
	cat1 = NULL;

	delete cat2;
	cat2 = NULL;

}

void TwoPlayer::StartLevel() {
	levelStarted = true;

	level = new LevelTwoP(cat1, cat2);

}
void TwoPlayer::SetStartedLevel(bool b) {
	levelStarted = b;
}

bool TwoPlayer::GameOver() {
	if (!levelStarted)
		return false;

	return level->State() == LevelTwoP::gameover;
}

void TwoPlayer::Activate() {
	cat1->Active(true);
	cat2->Active(true);
}

void TwoPlayer::Center() {
	cat1->Pos(Vector2(Graphics::Instance()->winWidth * 0.3f, Graphics::Instance()->winHeight * 0.796f));
	cat2->Pos(Vector2(Graphics::Instance()->winWidth * 0.7f, Graphics::Instance()->winHeight * 0.796f));
}

void TwoPlayer::Update() {
	labelTimer += timer->DeltaTime();
	if (gameStarted) {
		background->Update();

		grass->Update();

		if (!levelStarted) {
			StartLevel();
		}
		if (levelStarted) {
			level->Update();

			if (level->State() == LevelTwoP::gameover && input->KeyPressed(SDL_SCANCODE_SPACE)) {
				levelStarted = false;
				Activate();
				Center();
			}
		}
		cat1->Update();
		cat2->Update();
	}
	else {
		if (input->KeyPressed(SDL_SCANCODE_RETURN)) {
			gameStarted = true;
		}

		cat1->Update();
		cat2->Update();
	}
}

void TwoPlayer::Render() {
	if (levelStarted && !level->DoneDeathAnim()) {
		cat1->Render();
		cat2->Render();
	}

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

			controls2->Render();

			enterStart->Render();
		}
	}
	if (gameStarted) {
		if (levelStarted)
			level->Render();
	}

	grass->Render();

}