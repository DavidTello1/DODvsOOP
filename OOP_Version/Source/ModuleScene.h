#pragma once
#include "Module.h"

#include <vector>
#include "PCG/pcg_basic.h"
#include "glm/include/glm/glm.hpp"

typedef unsigned int uint;

#define BASE_ENTITIES 6 //camera + background + boundaries(4)
#define WORLD_WIDTH 500
#define WORLD_HEIGHT 500
#define BOUNDARIES_SIZE 100

class Entity;
class ComponentCameraController;
class ComponentSprite;
class ComponentRectCollider;

class ModuleScene : public Module
{
public:
	ModuleScene(bool start_enabled = true);
	virtual ~ModuleScene();

	bool Init() override;
	bool Start() override;
	bool Update(float dt) override;
	bool CleanUp() override;

	void Draw();
	void DrawDebug();

	// --- Demo ---

	// RNG
	pcg32_random_t& GetRNG() { return rng; }

	// Debug Drawing
	void DrawAxis();
	void DrawGrid(float grid_size);
	
	const bool& IsDebug() const { return is_debug; }
	void SwitchDebug() { is_debug = !is_debug; }

	// World
	const glm::mat4& GetViewProjMatrix() const;
	const int& GetWorldWidth() const { return world_width; }
	const int& GetWorldHeight() const { return world_height; }

	void SetWorldWidth(int width) { world_width = width; UpdateWorldSize(); }
	void SetWorldHeight(int height) { world_height = height; UpdateWorldSize(); }

	void UpdateWorldSize();

	// Asteroids
	void AddAsteroids(int num);
	void DeleteAsteroids(int num);

private:
	Entity* CreateEntity();
	void DeleteEntity(Entity* entity);

public:
	std::vector<Entity*> entities;
	ComponentCameraController* main_camera = nullptr;

	// --- Demo
	ComponentSprite* background = nullptr;
	Entity* b_top = nullptr;
	Entity* b_bottom = nullptr;
	Entity* b_left = nullptr;
	Entity* b_right = nullptr;

private:
	bool is_debug = false;
	float grid_size = 5.0f;
	int world_width, world_height = 0;

	pcg32_random_t rng;
};
