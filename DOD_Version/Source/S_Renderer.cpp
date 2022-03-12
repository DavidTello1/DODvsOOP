#include "S_Renderer.h"

#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRenderer.h"

#include "Components.h"

#include "Optick/include/optick.h"
#include "mmgr/mmgr.h"

void S_Renderer::Init()
{
}

void S_Renderer::Render()
{
    for (EntityIdx entity : entities)
    {
        OPTICK_PUSH("Entity Draw");

        if (App->scene->GetComponent<C_Renderer>(entity).render == false)
            continue;

        C_Transform transform = App->scene->GetComponent<C_Transform>(entity);
        C_Sprite sprite = App->scene->GetComponent<C_Sprite>(entity);

        App->renderer->DrawQuad(sprite.shader, transform.position, transform.size * transform.scale,
            sprite.texture, glm::vec4(1.0f), transform.rotation, transform.size * transform.scale / 2.0f);
        
        OPTICK_POP();
    }
}