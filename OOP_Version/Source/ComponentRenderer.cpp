#include "ComponentRenderer.h"

#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleResources.h"

#include "Entity.h"
#include "ComponentSprite.h"
#include "ComponentTransform.h"

void ComponentRenderer::Draw()
{
	Entity* entity = this->GetEntity();

	ComponentSprite* sprite = (ComponentSprite*)entity->GetComponent(Component::Type::SPRITE);
	if (sprite == nullptr)
		return;

	ComponentTransform* transform = (ComponentTransform*)entity->GetComponent(Component::Type::TRANSFORM);
	if (transform == nullptr)
		return;

	App->renderer->DrawQuad(App->resources->default_shader, transform->GetPosition(), sprite->GetSize() * transform->GetScale(), sprite->GetTexture());
}