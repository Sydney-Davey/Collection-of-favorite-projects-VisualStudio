#ifndef SCENEInventory_H
#define SCENEInventory_H
#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include <MMath.h>
#include <vector>

#include "Scene.h"
#include "Entity.h"
#include "Level.h"
#include "Threat.h"
#include "Difference.h"
#include "Inventory.h"


using namespace MATH;
class SceneInventory : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;

	float xAxis;
	float yAxis;
	
	SDL_Renderer* renderer;


	Entity* LeftArrow;
	Entity* RightArrow;
	Entity* RightArrowHover;
	Entity* LeftArrowHover;

	Entity* inventoryCloseButton;
	Entity* inventoryCloseButtonHover;

	Entity* inventoryPage1;
	Entity* inventoryPage2;
	Entity* inventoryPage3;
	Entity* inventoryPage4;
	Entity* inventoryPage5;
	Entity* cursor;
	

	bool isRightArrow;
	bool isLeftArrow;
	bool isinventoryCloseButton;

	bool running = 0;

	int pageNum;
	int UnlockNum;
	int startgame;

	float flappyScale; // a scale to make the texture smaller or larger
	//float wendigoScale = 1.5f;
	int Screennum;
	MIX_Mixer* mixer;
	float master_volume = 0.25f;



public:

	SceneInventory(SDL_Window* sdlWindow);
	~SceneInventory();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;
	int SceneSwitch() override;
};

#endif
