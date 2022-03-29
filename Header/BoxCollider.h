#pragma once
#include "Collider.h"

class BoxCollider :public Collider {
private:
	static const int MAX_VERTS = 4;

	GameEntity* verts[MAX_VERTS];

public:
	BoxCollider(Vector2 size);
	~BoxCollider();
	Vector2 GetFurthestPoint() override;

	Vector2 GetVertexPos(int index);

	bool AreColliding(BoxCollider* other);

private:
	void AddVert(int index, Vector2 pos);
};
