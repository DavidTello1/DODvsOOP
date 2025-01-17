#pragma once
#include "Component.h"

#include <vector>

class Entity
{
public:
	Entity() {};
	virtual ~Entity();

	UID GetUID() { return uid; }
	const std::vector<Component*>& GetComponents() const { return components; }

	Component* AddComponent(Component::Type component);
	void DeleteComponent(Component::Type component);
	Component* GetComponent(Component::Type component) const;

	void Draw();

private:
	std::vector<Component*> components;
	UID uid = 0;
};