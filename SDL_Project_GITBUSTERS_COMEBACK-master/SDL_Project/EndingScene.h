#ifndef EndingScene_H
#define EndingScene_H
#include <SDL3/SDL.h>
#include <Matrix.h>
#include "Scene.h"
#include "Entity.h"
#include <SDL3/SDL_mixer.h>

using namespace MATH;
class EndingScene : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;


	float xAxis;
	float yAxis;
	Scene* startGameSwitch;
	int startGame;
	float master_volume;
	bool isStartHover;

	SDL_Renderer* renderer;
	Entity* cursor;
	Entity* startButton;
	Entity* startButtonHover;
	MIX_Mixer* mixer;
	MIX_Audio* noiseSound;

public:
	EndingScene(SDL_Window* sdlWindow);
	~EndingScene();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;
	int SceneSwitch() override;
};

#endif