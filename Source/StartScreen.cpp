#include "StartScreen.h"
   
StartScreen::StartScreen() {
	timer = Timer::Instance();
	input = InputMgr::Instance();

	//top bar
	topBar = new GameEntity(Vector2(Graphics::Instance()->winWidth*0.5f, Graphics::Instance()->winHeight*0.08));
	day = new Texture("day.png");
	day->Parent(topBar);
	day->Pos(Vector2(0.0f, 0.0f));

	//logo and stuff
	animatedLogo = new AnimatedTex("nyamlogo.png", 0, 0, 510.5f, 193, 3, 0.8f, AnimatedTex::horizontal);
	animatedLogo->Parent(this);
	animatedLogo->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.38f));

	//play mode stuff
	playModes = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.63f));
	onePlayerMode = new Texture("onep.png");
	twoPlayerMode = new Texture("twop.png");
	cursor = new Texture("cursor.png");

	onePlayerMode->Parent(playModes);
	twoPlayerMode->Parent(playModes);
	cursor->Parent(playModes);

	onePlayerMode->Pos(Vector2(0.0f, -30.0f));
	twoPlayerMode->Pos(Vector2(0.0f, 30.0f));
	cursor->Pos(Vector2(-160.0f, -30.0f));

	playModes->Parent(this);

	cursorStart = cursor->Pos(local);
	cursorOffset = Vector2(0.0f, 63.0f);
	selectedMode = 0;

	//bot bar
	botBar = new GameEntity(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.95));
	table = new Texture("grass1.png");
	table->Parent(botBar);
	table->Pos(VEC2_ZERO);

	//kitti cats
	moveSpeed = 70.0f;

	cat1 = new AnimatedTex("scat1.png", 0, 0, 126, 80, 2, 0.8f, AnimatedTex::horizontal);
	cat1->Parent(this);
	cat1->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.82f));

	cat2 = new AnimatedTex("scat2.png", 0, 0, 126, 80, 2, 0.8f, AnimatedTex::horizontal);
	cat2->Parent(this);
	cat2->Pos(Vector2(Graphics::Instance()->winWidth * 0.5f, Graphics::Instance()->winHeight * 0.82f));

	background = Background::Instance();

}

StartScreen::~StartScreen() {
	//top bar
	delete topBar;
	topBar = NULL;

	delete day;
	day = NULL;

	//logo
	delete animatedLogo;
	animatedLogo = NULL;

	//play mode
	delete playModes;
	playModes = NULL;

	delete onePlayerMode;
	onePlayerMode = NULL;

	delete twoPlayerMode;
	twoPlayerMode = NULL;

	delete cursor;
	cursor = NULL;

	//bot bar
	delete botBar;
	botBar = NULL;

	delete table;
	table = NULL;

	//kitti cats
	delete cat1;
	cat1 = NULL;

	background->Release();
}

void StartScreen::HandleMovement(int x) {
	cat1->Translate(VEC2_RIGHT * moveSpeed * timer->DeltaTime(), world);
	cat1->Update();
	Vector2 pos = cat1->Pos(local);

	if ((pos.x - 63) > Graphics::Instance()->winWidth) {
		pos.x = -63.0f;
		cat1->Pos(pos);
	}
	
	cat2->Translate(-VEC2_RIGHT * moveSpeed * timer->DeltaTime(), world);
	cat2->Update();
	Vector2 pos2 = cat2->Pos(local);

	if ((pos2.x + 63) < 0) {
		pos2.x = Graphics::Instance()->winWidth+63.0f;
		cat2->Pos(pos2);
	}
	
}

int StartScreen::SelectedMode() {
	return selectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	selectedMode += change;
	if (selectedMode < 0)
		selectedMode = 1;
	else if (selectedMode > 1)
		selectedMode = 0;

	cursor->Pos(cursorStart + cursorOffset * selectedMode);
}

void StartScreen::Update() {
	background->Update();
	
	animatedLogo->Update();

	HandleMovement(0);
	HandleMovement(1);

	if (input->KeyPressed(SDL_SCANCODE_DOWN))
		ChangeSelectedMode(1);
	else if (input->KeyPressed(SDL_SCANCODE_UP))
		ChangeSelectedMode(-1);

}

void StartScreen::Render() {

	background->Render();
	day->Render();
	animatedLogo->Render();
	onePlayerMode->Render();
	twoPlayerMode->Render();
	cursor->Render();
	table->Render();
	cat1->Render();
	cat2->Render();
}