#pragma once

#include "Texture.h"

class Collider :public GameEntity {
public:

	enum class ColliderType {
		Box,
		Circle
	};

protected:
	ColliderType type;
	static const bool DEBUG_COLLIDERS = true;	
	Texture* debugTexture;

public:
	Collider(ColliderType p_type);
	~Collider();

	ColliderType GetType();
	virtual Vector2 GetFurthestPoint()=0;
	virtual void Render();
	 
protected:
	void SetDebugTexture(Texture* texture);
};