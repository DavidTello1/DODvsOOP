#pragma once
#include "Component.h"

#include "glm/include/glm/glm.hpp"

class ComponentTransform : public Component
{
public:
	ComponentTransform(Entity* entity) : size(0.0f), position(0.0f), scale(1.0f), rotation(0.0f), Component(Component::Type::TRANSFORM, entity) { UpdateTransform(); }
	~ComponentTransform() {};

	static inline Component::Type GetType() { return Component::Type::TRANSFORM; }

	const glm::mat4& GetTransform() const { return transform; }
	const glm::vec2& GetSize() const { return size; }
	const glm::vec2& GetPosition() const { return position; }
	const glm::vec2& GetScale() const { return scale; }
	const float& GetRotation() const { return rotation; }

	void SetSize(glm::vec2 new_size) { size = new_size; }
	void SetPosition(glm::vec2 pos) { position = pos; UpdateTransform(); }
	void SetScale(glm::vec2 new_scale) { scale = new_scale; UpdateTransform(); }
	void SetRotation(float rot) { rotation = rot; UpdateTransform(); }
	   
private:
	void UpdateTransform();

private:
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 scale = glm::vec2(1.0f);
	float rotation = 0.0f;

	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec2 size = glm::vec2(0.0f);
};

