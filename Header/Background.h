#pragma once

#include "Cloud.h"

class Background {
private:
	static Background* instance;
	static const int n = 25;
	Cloud* clouds[n];

public:
	static Background* Instance();
	static void Release();
	
	void Update();
	void Render();

private:
	Background();
	~Background();

};
