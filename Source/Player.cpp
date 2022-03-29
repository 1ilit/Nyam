#include "Player.h"

Player::Player(int x) {
	timer = Timer::Instance();
	input = InputMgr::Instance();

	isVisible = true;
	isAnimating = false;
	atePoison = false;

	score = 0;

	if (x == 0) {
		type = 0;

		cat = new AnimatedTex("cat1.png", 0, 0, 169, 100, 2, 1.0f, AnimatedTex::horizontal);
		cat->Parent(this);
		cat->Pos(VEC2_ZERO);

		eatingAnimation = new AnimatedTex("eating1.png", 0, 0, 169, 100, 2, 1.0f, AnimatedTex::horizontal);
		eatingAnimation->Parent(this);
		eatingAnimation->Pos(VEC2_ZERO);
		eatingAnimation->WrapMode(AnimatedTex::once);

		eatingPoison = new AnimatedTex("eatingpoison1.png", 0, 0, 169, 142, 4, 2.5f, AnimatedTex::horizontal);
		eatingPoison->Parent(this);
		eatingPoison->Pos(Vector2(0.0f, -21.0f));
		eatingPoison->WrapMode(AnimatedTex::once);

		
	}
	if (x == 1) {
		type = 1;
		cat = new AnimatedTex("cat2.png", 0, 0, 169, 100, 2, 1.0f, AnimatedTex::horizontal);
		cat->Parent(this);
		cat->Pos(VEC2_ZERO);

		eatingAnimation = new AnimatedTex("eating2.png", 0, 0, 169, 100, 2, 1.0f, AnimatedTex::horizontal);
		eatingAnimation->Parent(this);
		eatingAnimation->Pos(VEC2_ZERO);
		eatingAnimation->WrapMode(AnimatedTex::once);

		eatingPoison = new AnimatedTex("eatingpoison2.png", 0, 0, 169, 142, 4, 2.5f, AnimatedTex::horizontal);
		eatingPoison->Parent(this);
		eatingPoison->Pos(Vector2(0.0f, -21.0f));
		eatingPoison->WrapMode(AnimatedTex::once);

	}
	moveSpeed = 240.0f;

	AddCollider(new BoxCollider(Vector2(28.0f, 10.0f)), Vector2(2.0f, 10.0f));

	moveBounds = Vector2(82.0f, 780.0f);
	
}

Player::~Player() {
	timer = NULL;
	input = NULL;

	delete cat;
	cat = NULL;

	delete eatingAnimation;
	eatingAnimation = NULL;

	delete eatingPoison;
	eatingPoison = NULL;
}

void Player::HandleMovement() {
	if (type == 0) {
		if (input->KeyDown(SDL_SCANCODE_RIGHT)) {
			Translate(VEC2_RIGHT * moveSpeed * timer->DeltaTime(), world);
		}
		else if (input->KeyDown(SDL_SCANCODE_LEFT)) {
			Translate(-VEC2_RIGHT * moveSpeed * timer->DeltaTime(), world);
		}
	}
	if (type == 1) {
		if (input->KeyDown(SDL_SCANCODE_D)) {
			Translate(VEC2_RIGHT * moveSpeed * timer->DeltaTime(), world);
		}
		else if (input->KeyDown(SDL_SCANCODE_A)) {
			Translate(-VEC2_RIGHT * moveSpeed * timer->DeltaTime(), world);
		}
	}

	Vector2 pos = Pos(local);
	if (pos.x < moveBounds.x)
		pos.x = moveBounds.x;
	else if (pos.x > moveBounds.y)
		pos.x = moveBounds.y;
	
	Pos(pos);
}

void Player::Visible(bool v) {
	isVisible = v;
}

bool Player::IsEatingPoison() {

	return isAnimatingP && !eatingPoison->IsAnimating();
}

void Player::WasHit() {
	
	eatingPoison->ResetAnimation();
	isAnimatingP = true;
	atePoison = true;
}

void Player::AteFish() {
	eatingAnimation->ResetAnimation();
	isAnimatingF = true;
	ateFish = true;
}

bool Player::IsEating() {
	return eatingAnimation->IsAnimating();
}

bool Player::AtePoison() {
	return atePoison;
}

bool Player::IsAnimating() {
	return isAnimating;
}

int Player::Score() {
	return score;
}

void Player::AddScore(int change) {
	score += change;
}

void Player::Update() {
	if (atePoison) {
		eatingPoison->Update();
		isAnimatingP = eatingPoison->IsAnimating();
	}
	if (ateFish) {
		eatingAnimation->Update();
		isAnimatingF = eatingAnimation->IsAnimating();
	}

	if (isVisible) {
		if (Active()) {
			cat->Update();
			HandleMovement();
		}
	}
}

void Player::Render() {
	cat->Render();
	if (isAnimatingP) {
		eatingPoison->Render();
	}
	if (isAnimatingF) {
		eatingAnimation->Render();
	}
}


