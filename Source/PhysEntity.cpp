#include "PhysEntity.h"
#include "BoxCollider.h"


PhysEntity::PhysEntity() {

}

PhysEntity::~PhysEntity() {
	for (int i = 0; i < colliders.size(); i++) {
		delete colliders[i];
		colliders[i] = nullptr;
	}

	colliders.clear();
}

bool PhysEntity::CheckCollision(PhysEntity* other) {

	return static_cast<BoxCollider*>(colliders[0])->AreColliding(static_cast<BoxCollider*>(other->colliders[0]));

}

void PhysEntity::Hit(PhysEntity* other) {

}

void PhysEntity::AddCollider(Collider* collider, Vector2 localPos) {
	collider->Parent(this);
	collider->Pos(localPos);

	colliders.push_back(collider);
}

void PhysEntity::Render() {
	for (int i = 0; i < colliders.size(); i++) {
		colliders[i]->Render();
	}
}