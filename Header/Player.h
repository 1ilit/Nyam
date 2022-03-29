#pragma once

#include "GameEntity.h"
#include "AnimatedTex.h"
#include "InputMgr.h"
#include "PhysEntity.h"
#include "BoxCollider.h"

class Player :public PhysEntity{
private:
	Timer* timer;
	InputMgr* input;

	bool isVisible;
	bool isAnimating;
	bool isAnimatingP;
	bool isAnimatingF;
	bool atePoison;
	bool ateFish;

	int type;

	int score;
	Texture* cat;
	AnimatedTex* eatingAnimation;

	AnimatedTex* eatingPoison;

	float moveSpeed;
	Vector2 moveBounds;

public:
	void HandleMovement();
	
public:
	Player(int x);
	~Player();

	void Visible(bool v);
	void WasHit();
	bool AtePoison();
	bool IsEatingPoison();

	void AteFish();
	bool IsEating();

	bool IsAnimating();
	int Score();

	void AddScore(int change);

	void Update();
	void Render();
};