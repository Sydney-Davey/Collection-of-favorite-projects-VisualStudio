#include "Scene1.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"

Scene1::Scene1(SDL_Window* sdlWindow_) :
	 window(sdlWindow_)
	, startGame(0)
	, isStartHover(false)
	, renderer(nullptr)
	, cursor(nullptr)
	, startButtonHover(nullptr)
	, xAxis(30.0f)
	, yAxis(15.0f)
	
{

}

Scene1::~Scene1() {

}

bool Scene1::OnCreate() {
	// Create a project matrix that moves positions from physics/world space 
	// to screen/pixel space
	srand(time(NULL)); //Randomness based off the current time

	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, -1.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	projectionMatrix = ndc * ortho;

	//Create screen renderer
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Initialize renderer color (black)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_HideCursor();


	cursor = new Entity();
	cursor->pos = Vec3(0.0f, 0.0f, 0.0f);
	cursor->SetImage("textures/mouse-curser.png", renderer);

	startButton = new Entity();
	startButton->pos = Vec3(11.5f, 4.5f, 0.0f); //old y = 9.0f
	startButton->SetImage("textures/StartButton.png", renderer);

	startButtonHover = new Entity();
	startButtonHover->pos = Vec3(11.5f, 4.5f, 0.0f); //old y = 9.0f
	startButtonHover->SetImage("textures/StartButtonHover.png", renderer);

	return true;
}

void Scene1::OnDestroy() 
{
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	delete cursor;
	cursor = nullptr;

	delete startButton;
	startButton = nullptr;

	delete startButtonHover;
	startButtonHover = nullptr;

}

void Scene1::HandleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				float mx = event.button.x;
				float my = event.button.y;
				if (startButton->UpdateHover(mx, my))
				{
					std::cout << "START BUTTON CLICKED\n";
					startGame = 1;
				}
			}
		}
		break;

		case SDL_EVENT_MOUSE_MOTION: {
			///Gets the mouse postion translates it to screen space
			Vec3 currentMousePos = Vec3(static_cast<float>(event.button.x), static_cast<float>(event.button.y), 0.0f);
			Vec3 v1 = invProjectionMatrix * Vec3(static_cast<float>(event.button.x), static_cast<float>(event.button.y), 0.0f);

			//Offset for the flashlight/curser, otherwise The mouse will be the corner of the jpg

			//curser offset
				v1.x -= 0.0f; //across 40.0f
				v1.y += 0.0f; //down 24.0f
		
			//allows the flaslight to follow your mouse
			cursor->pos = v1; //v1 being our mouse


			
				float mx = event.button.x;
				float my = event.button.y;
				if (startButton->UpdateHover(mx, my))
				{
					isStartHover = true;
				}
				else {
					isStartHover = false;
				}
			

			break;
		}

		break;

		if (event.key.scancode == SDL_SCANCODE_1) {
			startGame = 2;
			std::cout << "1 Pressed - Game started" << std::endl;
		}

		default:
		break;
	}
	
}

void Scene1::Update(const float deltaTime) {
	
}

void Scene1::Render() const 
{
	SDL_RenderClear(renderer);
	// Convert from world coordinates to pixel coordinates using Scott's magical matrix
	Vec3 screenCoords;
	// Set up sprite's position and size
	SDL_FRect square;

	screenCoords = projectionMatrix * startButton->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = startButton->GetSurface()->w * 0.6f;
	square.h = startButton->GetSurface()->h * 0.6f;
	startButton->rect.x = screenCoords.x;
	startButton->rect.y = screenCoords.y;
	startButton->rect.w = startButton->GetSurface()->w * 0.6f;
	startButton->rect.h = startButton->GetSurface()->h * 0.6f;
	if (!isStartHover) {
		SDL_RenderTextureRotated(renderer, startButton->GetTexture(), nullptr, &square, startButton->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	screenCoords = projectionMatrix * startButtonHover->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = startButtonHover->GetSurface()->w * 0.6f;
	square.h = startButtonHover->GetSurface()->h * 0.6f;
	startButtonHover->rect.x = screenCoords.x;
	startButtonHover->rect.y = screenCoords.y;
	startButtonHover->rect.w = startButtonHover->GetSurface()->w * 0.6f;
	startButtonHover->rect.h = startButtonHover->GetSurface()->h * 0.6f;
	if (isStartHover) {
		SDL_RenderTextureRotated(renderer, startButtonHover->GetTexture(), nullptr, &square, startButtonHover->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	screenCoords = projectionMatrix * cursor->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = cursor->GetSurface()->w * 0.015f;
	square.h = cursor->GetSurface()->h * 0.015f;
	SDL_RenderTextureRotated(renderer, cursor->GetTexture(), nullptr, &square, cursor->angleDeg, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

int Scene1::SceneSwitch()
{
	if (startGame == 1) {
		return 1;
	}
	if (startGame == 0) {
		return 0;
	}
	if (startGame == 2) {
		return 2;
	}

}
