#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleWindow.h"
#include "ModuleGUI.h"
#include "ModuleResources.h"
#include "ModuleScene.h"

#include "Imgui/imgui.h"
#include "Glew/include/glew.h"
#include "SDL/include/SDL_opengl.h"
#include "glm/include/glm/gtc/type_ptr.hpp"

#pragma comment(lib, "glew/libx86/glew32.lib")
#pragma comment (lib, "glu32.lib")    // link OpenGL Utility lib
#pragma comment (lib, "opengl32.lib") // link Microsoft OpenGL lib

#include "mmgr/mmgr.h"

ModuleRenderer::ModuleRenderer(bool start_enabled) : Module("ModuleRenderer", start_enabled)
{
	context = NULL;
}

ModuleRenderer::~ModuleRenderer()
{}

bool ModuleRenderer::Init()
{
	LOG("Creating 3D Renderer context\n");
	bool ret = true;

	//Create context
	context = SDL_GL_CreateContext(App->window->GetWindow());
	if (context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	// Initialize glew
	GLenum error = glewInit();
	LOG("Loading glew");

	// OpenGL
	glViewport(0, 0, App->window->GetWidth(), App->window->GetHeight());
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Quad
	float vertices[] = {
		// positions          // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glGenBuffers(1, &quadIBO);

	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	return ret;
}

bool ModuleRenderer::PreUpdate(float dt)
{
	// Clear Screen & Set Viewport
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool ModuleRenderer::PostUpdate(float dt)
{
	// Grid & Axis
	//***

	// Render Scene
	App->scene->Draw();

	// Debug Draw
	//***

	// Render ImGui
	App->gui->Draw();

	SDL_GL_SwapWindow(App->window->GetWindow());
	return true;
}

bool ModuleRenderer::CleanUp()
{
	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(context);

	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);

	return true;
}

//--------------------------------
void ModuleRenderer::DrawQuad(const GLuint shader, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "uViewProj"), 1, GL_FALSE, (GLfloat*)&App->scene->GetViewProjMatrix());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader, "uTransform"), 1, GL_FALSE, (GLfloat*)&model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, App->resources->default_tex);
	glUniform1i(glGetUniformLocation(shader, "uTexture"), 0);

	glUniform4f(glGetUniformLocation(shader, "uColor"), color.r, color.g, color.b, color.a);

	glBindVertexArray(App->renderer->quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void ModuleRenderer::DrawQuad(const GLuint shader, const glm::vec2& position, const glm::vec2& size, uint32_t texture)
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "uViewProj"), 1, GL_FALSE, (GLfloat*)&App->scene->GetViewProjMatrix());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader, "uTransform"), 1, GL_FALSE, (GLfloat*)&model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader, "uTexture"), 0);

	glUniform4f(glGetUniformLocation(shader, "uColor"), 1.0f, 1.0f, 1.0f, 1.0f);

	glBindVertexArray(App->renderer->quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void ModuleRenderer::DrawCircle(const glm::vec2& center, const float radius, const glm::vec4& color)
{
}

void ModuleRenderer::UpdateViewportSize()
{
	glViewport(0, 0, App->window->GetWidth(), App->window->GetHeight());
}
