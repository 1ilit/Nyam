#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size)
	:Collider(ColliderType::Box) {
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2(0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x, 0.5f * size.y));
	AddVert(3, Vector2(0.5f * size.x, 0.5f * size.y));

	if (DEBUG_COLLIDERS) {
		SetDebugTexture(new Texture("BoxCollider.png"));
		debugTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider() {
	for (int i = 0; i < MAX_VERTS; i++) {
		delete verts[i];
		verts[i] = NULL;
	}
}

Vector2 BoxCollider::GetFurthestPoint() {
	Vector2 localPos = Pos(GameEntity::local);

	int furthestIndex = 0;
	float dist = (localPos + verts[0]->Pos(GameEntity::local)).MagnitudeSqr();
	float otherDist = 0.0f;

	for (int i = 1; i < MAX_VERTS; i++) {
		otherDist = (localPos + verts[i]->Pos(GameEntity::local)).MagnitudeSqr();
		if (otherDist > dist) {
			furthestIndex = i;
			dist = otherDist;
		}
	}
	return localPos + verts[furthestIndex]->Pos(GameEntity::local);
}

Vector2 BoxCollider::GetVertexPos(int index) {
	return verts[index]->Pos();
}

void BoxCollider::AddVert(int index, Vector2 pos) {
	verts[index] = new GameEntity(pos);
	verts[index]->Parent(this);
}

bool BoxCollider::AreColliding(BoxCollider* other) {
	int leftA = verts[0]->Pos().x;
	int rightA = verts[1]->Pos().x;
	int topA = verts[0]->Pos().y;
	int bottomA = verts[2]->Pos().y;

	int leftB = other->verts[0]->Pos().x;
	int rightB = other->verts[1]->Pos().x;
	int topB = other->verts[0]->Pos().y;
	int bottomB = other->verts[2]->Pos().y;

	if (bottomA <= topB){
		return false;
	}

	if (topA >= bottomB){
		return false;
	}

	if (rightA <= leftB){
		return false;
	}

	if (leftA >= rightB){
		return false;
	}
	
	return true;
}