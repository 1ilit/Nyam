#include "Background.h"

Background* Background::instance = NULL;

Background::Background() {

	clouds[0] = new Cloud(Vector2(100.0f, 60.0f));
	clouds[1] = new Cloud(Vector2(120.0f, 170.0f));
	clouds[2] = new Cloud(Vector2(-42.0f, 280.0f));
	clouds[3] = new Cloud(Vector2(107.0f, 370.0f));
	clouds[4] = new Cloud(Vector2(130.0f, 560.0f));
	clouds[5] = new Cloud(Vector2(240.0f, 100.0f));
	clouds[6] = new Cloud(Vector2(270.0f, 240.0f));
	clouds[7] = new Cloud(Vector2(210.0f, 300.0f));
	clouds[8] = new Cloud(Vector2(270.0f, 440.0f));
	clouds[9] = new Cloud(Vector2(368.0f, 550.0f));
	clouds[10] = new Cloud(Vector2(410.0f, 150.0f));
	clouds[11] = new Cloud(Vector2(400.0f, 340.0f));
	clouds[12] = new Cloud(Vector2(514.0f, 40.0f));
	clouds[13] = new Cloud(Vector2(446.0f, 220.0f));
	clouds[14] = new Cloud(Vector2(537.0f, 460.0f));
	clouds[15] = new Cloud(Vector2(480.0f, 610.0f));
	clouds[16] = new Cloud(Vector2(645.0f, 170.0f));
	clouds[17] = new Cloud(Vector2(610.0f, 350.0f));
	clouds[18] = new Cloud(Vector2(715.0f, 105.0f));
	clouds[19] = new Cloud(Vector2(820.0f, 170.0f));
	clouds[20] = new Cloud(Vector2(760.0f, 300.0f));
	clouds[21] = new Cloud(Vector2(740.0f, 450.0f));
	clouds[22] = new Cloud(Vector2(840.0f, 480.0f));
	clouds[23] = new Cloud(Vector2(820.0f, 600.0f));
	clouds[24] = new Cloud(Vector2(-20.0f, 90.0f));

}

Background* Background::Instance() {
	if (instance == NULL)
		instance = new Background();

	return instance;
}

void Background::Release() {
	delete instance;
	instance = NULL;
}

Background::~Background(){
	for (int i = 0; i < n; i++) {
		delete clouds[i];
		clouds[i] = NULL;
	}
}

void Background::Update() {
	for (int i = 0; i < n; i++) {
		clouds[i]->Update();
	}
}

void Background::Render() {
	for (int i = 0; i < n; i++) {
		clouds[i]->Render();
	}
}

