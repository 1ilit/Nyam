#pragma once

#include "Timer.h"
#include "Texture.h"

class Cloud :public Texture {
private:
	static bool scroll;

	Timer* timer;

	float scrollSpeed;

public:
	static void Scroll(bool b);

	Cloud(Vector2 p_pos);
	~Cloud();

	void Render();
	void Update();

private:
	void ScrollCloud();
};
