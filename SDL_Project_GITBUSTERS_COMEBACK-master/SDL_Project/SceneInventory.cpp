#include "SceneInventory.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"
#include "Difference.h"
#include "Inventory.h"

SceneInventory::SceneInventory(SDL_Window* sdlWindow_) :
	window(sdlWindow_)
	, renderer(nullptr)
	, RightArrowHover(nullptr)
	, LeftArrowHover(nullptr)
	, RightArrow(nullptr)
	, LeftArrow(nullptr)
	, UnlockNum(0)
	, startgame(2)
	, inventoryPage1(nullptr)
	, inventoryPage2(nullptr)
	, inventoryPage3(nullptr)
	, inventoryPage4(nullptr)
	, inventoryPage5(nullptr)
	, inventoryCloseButton(nullptr)
	, inventoryCloseButtonHover(nullptr)
	, flappyScale(2.0f)
	, pageNum(0)
	, isRightArrow(false)
	, isLeftArrow(false)
	, isinventoryCloseButton(false)
	, xAxis(30.0f)
	, yAxis(15.0f)
	, mixer()
	, Screennum(0)
{
}

SceneInventory::~SceneInventory() {}

bool SceneInventory::OnCreate() {
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


	// Create the objects that will be rendered on the screen
	
	RightArrowHover = new Entity();
	RightArrowHover->pos = Vec3(25.51f, 10.5f, 0.0f);
	RightArrowHover->SetImage("textures/ArrowRightHover.png", renderer);

	LeftArrowHover = new Entity();
	LeftArrowHover->pos = Vec3(0.0f, 10.5f, 0.0f);
	LeftArrowHover->SetImage("textures/ArrowLeftHover.png", renderer);
	

	// Inventory HUD //

	LeftArrow = new Entity();
	LeftArrow->pos = Vec3(0.0f, 10.5f, 0.0f);
	LeftArrow->SetImage("textures/ArrowLeft.png", renderer);

	RightArrow = new Entity();
	RightArrow->pos = Vec3(25.51f, 10.5f, 0.0f);
	RightArrow->SetImage("textures/ArrowRight.png", renderer);

	inventoryCloseButton = new Entity();
	inventoryCloseButton->pos = Vec3(27.5f, 14.5f, 0.0f);
	inventoryCloseButton->SetImage("textures/white-close-button.png", renderer);

	inventoryCloseButtonHover = new Entity();
	inventoryCloseButtonHover->pos = Vec3(27.5f, 14.5f, 0.0f);
	inventoryCloseButtonHover->SetImage("textures/white-close-buttonHover.png", renderer);

	inventoryPage1 = new Entity();
	inventoryPage1->pos = Vec3(0.0f, 22.0f, 0.0f);
	inventoryPage1->SetImage("textures/FOLDER-Page1.jpg", renderer);

	inventoryPage2 = new Entity();
	inventoryPage2->pos = Vec3(0.0f, 22.0f, 0.0f);
	inventoryPage2->SetImage("textures/FOLDER-Page2.jpg", renderer);

	inventoryPage3 = new Entity();
	inventoryPage3->pos = Vec3(0.0f, 22.0f, 0.0f);
	inventoryPage3->SetImage("textures/FOLDER-Page3.jpg", renderer);

	inventoryPage4 = new Entity();
	inventoryPage4->pos = Vec3(0.0f, 22.0f, 0.0f);
	inventoryPage4->SetImage("textures/FOLDER-Page4.jpg", renderer);

	inventoryPage5 = new Entity();
	inventoryPage5->pos = Vec3(0.0f, 22.0f, 0.0f);
	inventoryPage5->SetImage("textures/FOLDER-Page5.jpg", renderer);

	//////////////////

	cursor = new Entity();
	cursor->pos = Vec3(0.0f, 0.0f, 0.0f);
	cursor->SetImage("textures/mouse-curser.png", renderer);

	SDL_Init(SDL_INIT_AUDIO);
	MIX_Init();

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

	if (!mixer)
	{
		std::cout << "Failed to create mixer: %s\n", SDL_GetError();
		return 0;
	}

	//// Load and play music
	MIX_Audio* Music = MIX_LoadAudio(mixer, "Audio/CrabRave.wav", true);
	MIX_SetMasterGain(mixer, master_volume);
	MIX_PlayAudio(mixer, Music);
	MIX_DestroyAudio(Music);

	return true;
}

void SceneInventory::OnDestroy() {
	// Clean up the renderer
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	//// Turn off audio
	if (mixer)
	{
		MIX_DestroyMixer(mixer);
		MIX_Quit();
	}

	// Delete the objects created on the heap
	// and set to the null pointer just to be safe
	
	delete RightArrowHover;
	RightArrow = nullptr;

	delete LeftArrowHover;
	LeftArrow = nullptr;

	delete LeftArrow;
	LeftArrow = nullptr;

	delete RightArrow;
	RightArrow = nullptr;

	delete inventoryCloseButton;
	inventoryCloseButton = nullptr;

	delete inventoryPage1;
	inventoryPage1 = nullptr;

	delete inventoryPage2;
	inventoryPage2 = nullptr;

	delete inventoryPage3;
	inventoryPage3 = nullptr;

	delete inventoryPage4;
	inventoryPage4 = nullptr;

	delete inventoryPage5;
	inventoryPage5 = nullptr;

	delete cursor;
	cursor = nullptr;
}

void SceneInventory::HandleEvents(const SDL_Event& event)
{
	float mouseX, mouseY; //Mouse X and Y pos
	SDL_GetMouseState(&mouseX, &mouseY); //sets our float value to both the mouses X and Y pos on screen
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:

		// Mouse and Buttons
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			
			float mx = event.button.x;
			float my = event.button.y;

			// Left Arrow (page navigation)
			if (LeftArrow->UpdateHover(mx, my))
			{
				std::cout << "LEFT ARROW CLICKED\n";
				isLeftArrow = false;

				// Option 1: clamp to 0 (stops at first page)
				if (pageNum > 0)
				{
					std::cout << pageNum << std::endl;
					pageNum -= 1;
				}
			}

			// Right Arrow (page navigation)
			else if (RightArrow->UpdateHover(mx, my))
			{
				std::cout << "RIGHT ARROW CLICKED\n";
				if (pageNum < 4)
				{
					pageNum += 1;
				}
				std::cout << pageNum << std::endl;
			}

			
			// Inventory Close Button
			else if (inventoryCloseButton->UpdateHover(mx, my))
			{
				startgame = 1;
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
			cursor->pos = v1;
		
		
		float mx = event.button.x;
		float my = event.button.y;
		if (LeftArrow->UpdateHover(mx, my))
		{
			isLeftArrow = true;
		}
		else {
			isLeftArrow = false;
		}

		if (RightArrow->UpdateHover(mx, my))
		{
			isRightArrow = true;
		}
		else {
			isRightArrow = false;
		}

		if (inventoryCloseButton->UpdateHover(mx, my))
		{
			isinventoryCloseButton = true;
		}
		else {
			isinventoryCloseButton = false;
		}

		break;
	}

	default:
		break;
	}
}

void SceneInventory::Update(const float deltaTime) { }


void SceneInventory::Render() const {
	SDL_RenderClear(renderer);
	// Convert from world coordinates to pixel coordinates using Scott's magical matrix
	Vec3 screenCoords;
	// Set up sprite's position and size
	SDL_FRect square;

	// ARROWS // 

	// Right Arrow Hover
	screenCoords = projectionMatrix * RightArrowHover->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = RightArrowHover->GetSurface()->w * 0.6f;
	square.h = RightArrowHover->GetSurface()->h * 0.6f;
	screenCoords = projectionMatrix * RightArrowHover->pos;
	RightArrowHover->rect.x = screenCoords.x;
	RightArrowHover->rect.y = screenCoords.y;
	RightArrowHover->rect.w = RightArrowHover->GetSurface()->w * 0.6f;
	RightArrowHover->rect.h = RightArrowHover->GetSurface()->h * 0.6f;
	if (isRightArrow) {
		SDL_RenderTextureRotated(renderer, RightArrowHover->GetTexture(), nullptr, &square, RightArrowHover->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Inventory Page 1
	screenCoords = projectionMatrix * inventoryPage1->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryPage1->GetSurface()->w * 0.38f;
	square.h = inventoryPage1->GetSurface()->h * 0.38f;
	inventoryPage1->rect.x = screenCoords.x;
	inventoryPage1->rect.y = screenCoords.y;
	inventoryPage1->rect.w = inventoryPage1->GetSurface()->w * 0.05f;
	inventoryPage1->rect.h = inventoryPage1->GetSurface()->h * 0.05f;
	if (pageNum == 0) {
		SDL_RenderTextureRotated(renderer, inventoryPage1->GetTexture(), nullptr, &square, inventoryPage1->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Inventory Page 2
	screenCoords = projectionMatrix * inventoryPage2->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryPage2->GetSurface()->w * 0.38f;
	square.h = inventoryPage2->GetSurface()->h * 0.38f;
	inventoryPage2->rect.x = screenCoords.x;
	inventoryPage2->rect.y = screenCoords.y;
	inventoryPage2->rect.w = inventoryPage2->GetSurface()->w * 0.05f;
	inventoryPage2->rect.h = inventoryPage2->GetSurface()->h * 0.05f;
	if (pageNum == 1) {
		SDL_RenderTextureRotated(renderer, inventoryPage2->GetTexture(), nullptr, &square, inventoryPage2->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Inventory Page 3
	screenCoords = projectionMatrix * inventoryPage3->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryPage3->GetSurface()->w * 0.38f;
	square.h = inventoryPage3->GetSurface()->h * 0.38f;
	inventoryPage3->rect.x = screenCoords.x;
	inventoryPage3->rect.y = screenCoords.y;
	inventoryPage3->rect.w = inventoryPage3->GetSurface()->w * 0.05f;
	inventoryPage3->rect.h = inventoryPage3->GetSurface()->h * 0.05f;
	if (pageNum == 2) {
		SDL_RenderTextureRotated(renderer, inventoryPage3->GetTexture(), nullptr, &square, inventoryPage3->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Inventory Page 4
	screenCoords = projectionMatrix * inventoryPage4->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryPage4->GetSurface()->w * 0.38f;
	square.h = inventoryPage4->GetSurface()->h * 0.38f;
	inventoryPage4->rect.x = screenCoords.x;
	inventoryPage4->rect.y = screenCoords.y;
	inventoryPage4->rect.w = inventoryPage4->GetSurface()->w * 0.05f;
	inventoryPage4->rect.h = inventoryPage4->GetSurface()->h * 0.05f;
	if (pageNum == 3) {
		SDL_RenderTextureRotated(renderer, inventoryPage4->GetTexture(), nullptr, &square, inventoryPage4->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Inventory Page 5
	screenCoords = projectionMatrix * inventoryPage5->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryPage5->GetSurface()->w * 0.38f;
	square.h = inventoryPage5->GetSurface()->h * 0.38f;
	inventoryPage5->rect.x = screenCoords.x;
	inventoryPage5->rect.y = screenCoords.y;
	inventoryPage5->rect.w = inventoryPage5->GetSurface()->w * 0.05f;
	inventoryPage5->rect.h = inventoryPage5->GetSurface()->h * 0.05f;
	if (pageNum == 4) {
		SDL_RenderTextureRotated(renderer, inventoryPage5->GetTexture(), nullptr, &square, inventoryPage5->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Left Arrow Hover
	screenCoords = projectionMatrix * LeftArrowHover->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = LeftArrowHover->GetSurface()->w * 0.6f;
	square.h = LeftArrowHover->GetSurface()->h * 0.6f;
	LeftArrowHover->rect.x = screenCoords.x;
	LeftArrowHover->rect.y = screenCoords.y;
	LeftArrowHover->rect.w = LeftArrowHover->GetSurface()->w * 0.6f;
	LeftArrowHover->rect.h = LeftArrowHover->GetSurface()->h * 0.6f;
	if (isLeftArrow) {
		SDL_RenderTextureRotated(renderer, LeftArrowHover->GetTexture(), nullptr, &square, LeftArrowHover->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	////////////////////////////////

	// Left Arrow
	screenCoords = projectionMatrix * LeftArrow->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = LeftArrow->GetSurface()->w * 0.6f;
	square.h = LeftArrow->GetSurface()->h * 0.6f;
	screenCoords = projectionMatrix * LeftArrow->pos;
	LeftArrow->rect.x = screenCoords.x;
	LeftArrow->rect.y = screenCoords.y;
	LeftArrow->rect.w = LeftArrow->GetSurface()->w * 0.6f;
	LeftArrow->rect.h = LeftArrow->GetSurface()->h * 0.6f;
	if (!isLeftArrow) {
		SDL_RenderTextureRotated(renderer, LeftArrow->GetTexture(), nullptr, &square, LeftArrow->angleDeg, nullptr, SDL_FLIP_NONE);
	}



	// Right Arrow
	screenCoords = projectionMatrix * RightArrow->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = RightArrow->GetSurface()->w * 0.6f;
	square.h = RightArrow->GetSurface()->h * 0.6f;
	RightArrow->rect.x = screenCoords.x;
	RightArrow->rect.y = screenCoords.y;
	RightArrow->rect.w = RightArrow->GetSurface()->w * 0.6f;
	RightArrow->rect.h = RightArrow->GetSurface()->h * 0.6f;
	SDL_RenderTextureRotated(renderer, RightArrow->GetTexture(), nullptr, &square, RightArrow->angleDeg, nullptr, SDL_FLIP_NONE);


	// Inventory Close Button
	screenCoords = projectionMatrix * inventoryCloseButton->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryCloseButton->GetSurface()->w * 0.03f;
	square.h = inventoryCloseButton->GetSurface()->h * 0.03f;
	inventoryCloseButton->rect.x = screenCoords.x;
	inventoryCloseButton->rect.y = screenCoords.y;
	inventoryCloseButton->rect.w = inventoryCloseButton->GetSurface()->w * 0.1f;
	inventoryCloseButton->rect.h = inventoryCloseButton->GetSurface()->h * 0.1f;
	if (!isinventoryCloseButton) {
		SDL_RenderTextureRotated(renderer, inventoryCloseButton->GetTexture(), nullptr, &square, inventoryCloseButton->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Inventory Close Button Hover
	screenCoords = projectionMatrix * inventoryCloseButtonHover->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryCloseButtonHover->GetSurface()->w * 0.03f;
	square.h = inventoryCloseButtonHover->GetSurface()->h * 0.03f;
	inventoryCloseButtonHover->rect.x = screenCoords.x;
	inventoryCloseButtonHover->rect.y = screenCoords.y;
	inventoryCloseButtonHover->rect.w = inventoryCloseButtonHover->GetSurface()->w * 0.1f;
	inventoryCloseButtonHover->rect.h = inventoryCloseButtonHover->GetSurface()->h * 0.1f;
	if (isinventoryCloseButton) {
		SDL_RenderTextureRotated(renderer, inventoryCloseButtonHover->GetTexture(), nullptr, &square, inventoryCloseButtonHover->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Cursor
	screenCoords = projectionMatrix * cursor->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = cursor->GetSurface()->w * 0.015f;
	square.h = cursor->GetSurface()->h * 0.015f;
	SDL_RenderTextureRotated(renderer, cursor->GetTexture(), nullptr, &square, cursor->angleDeg, nullptr, SDL_FLIP_NONE);
	

	// Update the screen
	SDL_RenderPresent(renderer);
}

int SceneInventory::SceneSwitch()
{
	if (startgame == 0) {
		return 0;
	}
	if (startgame == 1) {
		return 1;
	}
}
