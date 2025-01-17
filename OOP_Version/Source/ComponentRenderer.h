#pragma once
#include "Component.h"

class ComponentRenderer : public Component
{
public:
	ComponentRenderer(Entity* entity) : Component(Component::Type::RENDERER, entity) {};
	~ComponentRenderer() {};

	static inline Component::Type GetType() { return Component::Type::RENDERER; }

	void Draw();
};

