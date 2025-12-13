#ifndef SCENE0_H
#define SCENE0_H
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
class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;


	float xAxis;
	float yAxis;
	
	SDL_Renderer* renderer;

	Level poo; //Level for our game, keeps track of room number, generates differences etc.
	
	std::vector<Difference*> DiffArray;//array of our differences in the level

	Entity* UpArrow;
	Entity* DownArrow;
	Entity* UpArrowHover;
	Entity* DownArrowHover;

	Entity* LeftArrow;
	Entity* RightArrow;
	Entity* noiseMakerButton;
	Entity* inventoryButton;
	Entity* inventoryFolder;
	Entity* flashlight_playerHover;
	Entity* Arrow;
	Entity* flashlight_player; //players flashlight
	Entity* inventoryCloseButtonHover;
	Entity* Background1;
	Entity* Background2;
	Entity* Background3;
	Entity* Background4;
	Entity* flappy2;
	Entity* flappy3;
	Entity* TutorialScreen;
	Entity* TutorialStart;
	Threat* wendigo;
	

	std::vector<Threat*> horde;
	Inventory* book_inventory;

	int hordeSize;
	string page;
	bool BookUnlocked;
	bool mouseTrue;
	bool isFolderThere;
	bool isUpArrow;
	bool isDownArrow;
	bool isInventory;
	bool isFlashlight;

	bool running = 0;

	int pageNum;
	int UnlockNum;
	int startgame;

	float flappyScale; // a scale to make the texture smaller or larger
	//float wendigoScale = 1.5f;
	bool gameStart;
	int Screennum;
	MIX_Mixer* mixer;
	MIX_Audio* noiseSound;
	float master_volume = 0.25f;

	//flash transition for horde and noise maker
	bool isFlashing;
	float flashAlpha;
	float flashDuration;
	float flashTimer;



public:

	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;
	int SceneSwitch() override;
	bool NoiseMakerOn();
};

#endif
