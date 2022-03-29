#include "Cloud.h"

bool Cloud::scroll = false;

void Cloud::Scroll(bool b) {
	scroll = b;
}

Cloud::Cloud(Vector2 p_pos) 
	:Texture("fof.png", 0, 0, 85, 37) {
	timer = Timer::Instance();

	int type = rand() % 2;
	clippedRect.y = type * 38;

	Pos(p_pos);

	scrollSpeed = 5.0f;
}

Cloud::~Cloud() {
	timer = NULL;
}

void Cloud::ScrollCloud() {
	Translate(VEC2_RIGHT * scrollSpeed*timer->DeltaTime(), world);

	Vector2 pos = Pos(local);

	if ((pos.x-42) > Graphics::Instance()->winWidth) {
		pos.x = -42.0f;
		Pos(pos);
	}
}

void Cloud::Update() {
	ScrollCloud();
}

void Cloud::Render() {
	Texture::Render();
}