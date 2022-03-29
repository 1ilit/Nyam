#pragma once
#include <vector>
#include "Collider.h"

class PhysEntity :public GameEntity {
protected:

	std::vector<Collider*> colliders;

public:
	PhysEntity();
	virtual ~PhysEntity();


	bool CheckCollision(PhysEntity* other);
	virtual void Hit(PhysEntity* other);

	virtual void Render();

protected:

	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};
