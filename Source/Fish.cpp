#include "Fish.h"
#include <random>

Fish::Fish(FishType t){
	timer = Timer::Instance();
	wasEaten = false;

	fishtype = t;
	if (fishtype == normal) {
		int type = rand() % 2;

		switch (type) {
		case 0:
			texture = new Texture("fish0.png");
			break;
		case 1:
			texture = new Texture("fish1.png");
			break;
		}
	}
	else {
		int type = rand() % 2;

		switch (type) {
		case 0:
			texture = new Texture("poisonFish0.png");
			break;
		case 1:
			texture = new Texture("poisonFish1.png");
			break;
		}
	}

	texture->Pos(VEC2_ZERO);
	texture->Parent(this);
	velocity = 220.0f;
	AddCollider(new BoxCollider(texture->ScaledDimensions()), this->Pos());

}

Fish::~Fish() {
	timer = NULL;

	delete texture;
	texture = NULL;
}

void Fish::WasEaten(bool b) {
	wasEaten = b;
}

bool Fish::WasEaten() {
	return wasEaten;
}

Fish::FishType Fish::Type() {
	return fishtype;
}

void Fish::FishFalling() {

	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(85, 775);

	Translate(VEC2_UP * velocity*timer->DeltaTime(), world);

	Vector2 pos = Pos(local);
	if (!wasEaten) {
		if ((pos.y + 36) > Graphics::Instance()->winHeight) {
			int x = distr(gen);
			Pos(Vector2(x, 0.0f));
		}
	}
	if (wasEaten) {
		int x = distr(gen);
		Pos(Vector2(x, 0.0f));
		wasEaten = false;
	}
}

void Fish::Update() {
	FishFalling();
}

void Fish::Render() {
	texture->Render();
}