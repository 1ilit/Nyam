#pragma once
#include "Timer.h"
#include "Texture.h"
#include "PhysEntity.h"
#include "BoxCollider.h"
class Fish :public PhysEntity {
public:
	enum FishType {
		poison=0,
		normal=1
	};

private:
	Timer* timer;
	Texture* texture;

	float velocity;
	FishType fishtype;
	bool wasEaten;

public:
	Fish(FishType t);
	~Fish();

	void Render();
	void Update();
	void WasEaten(bool b);
	bool WasEaten();
	FishType Type(); 

private:
	void FishFalling();
};