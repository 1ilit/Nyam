#include "Collider.h"

Collider::Collider(ColliderType p_type)
{
	type = p_type;
	debugTexture = NULL;
}

Collider::~Collider() {
	if (debugTexture) {
		delete debugTexture;
		debugTexture = nullptr;
	}
}

void Collider::SetDebugTexture(Texture* texture) {
	delete debugTexture;

	debugTexture = texture;
	debugTexture->Parent(this);

}
 
Collider::ColliderType Collider::GetType() {
	return type;
}

void Collider::Render() {
	if (DEBUG_COLLIDERS) {
		debugTexture->Render();
	}
}