#ifndef Scene1_H
#define Scene1_H
#include <SDL3/SDL.h>
#include <Matrix.h>
#include "Scene.h"
#include "Entity.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window* window;
	Matrix4 projectionMatrix;
	Matrix4 invProjectionMatrix;


	float xAxis;
	float yAxis;
	Scene* startGameSwitch;
	int startGame;
	bool isStartHover;

	SDL_Renderer* renderer;
	Entity* cursor;
	Entity* startButton;
	Entity* startButtonHover;


public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;
	int SceneSwitch() override;
};

#endif

