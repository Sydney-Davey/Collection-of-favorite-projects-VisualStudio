#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "Scene1.h"
#include "SceneInventory.h"
#include "EndingScene.h"
#include <iostream>


GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	InvnentoryOpened = false;
	currentScene = nullptr;
	LevelCount_ = -1;
}


bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Scene1(windowPtr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	SDL_Event event;
	timer->Start();
	while (isRunning) {
		SDL_PollEvent(&event);
		timer->UpdateFrameTicks();
		currentScene->HandleEvents(event);
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		if (currentScene->SceneSwitch() == 1){
			//Checks to see if there were differences in the level, and if so, what exit the player used
			//end of forest exit, diffs present
			if (LevelCount_ != -1) {
				if (currentScene->LevelDiffsPresent == true && currentScene->FrontDoorUsed == true
					&& InvnentoryOpened == false //and the inventory wasn't opened
					|| //OR
					//No differences present, but they exited through room 1
					currentScene->LevelDiffsPresent == false && currentScene->FrontDoorUsed == false
					 && InvnentoryOpened == false) { //and the inventory wasn't opened	
					std::cout << "Wrong exit used :(" << std::endl;
					LevelCount_ = 0;
				}
			}
			InvnentoryOpened = false;
			LevelCount_++;
			std::cout << LevelCount_ << std::endl;
			GameManager::OnDestroy();
			const int SCREEN_WIDTH = 1280;
			const int SCREEN_HEIGHT = 720;
			windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
			windowPtr->OnCreate();
			timer = new Timer();
			currentScene = new Scene0(windowPtr->GetSDL_Window());
			currentScene->LevelCount = LevelCount_;
			currentScene->OnCreate();
		}

		if (currentScene->SceneSwitch() == 2) {
			
			GameManager::OnDestroy();
			LevelCount_--;
			InvnentoryOpened = true;

			const int SCREEN_WIDTH = 1280;
			const int SCREEN_HEIGHT = 720;
			windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
			windowPtr->OnCreate();
			timer = new Timer();
			currentScene = new SceneInventory(windowPtr->GetSDL_Window());
			currentScene->LevelCount = LevelCount_;
			currentScene->OnCreate();
		}
		if (currentScene->SceneSwitch() == 3) {

			GameManager::OnDestroy();
			const int SCREEN_WIDTH = 1280;
			const int SCREEN_HEIGHT = 720;
			windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
			windowPtr->OnCreate();
			timer = new Timer();
			currentScene = new EndingScene(windowPtr->GetSDL_Window());
			currentScene->OnCreate();
		}

		if(event.type == SDL_EVENT_QUIT){
			isRunning = false;
		}
		switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
		
			if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
				GameManager::OnDestroy();
				const int SCREEN_WIDTH = 1920;
				const int SCREEN_HEIGHT = 1080;
				windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
				windowPtr->OnCreate();
				timer = new Timer();
				currentScene = new Scene0(windowPtr->GetSDL_Window());
				currentScene->OnCreate();
			}
			if (event.key.scancode == SDL_SCANCODE_F2) {
				GameManager::OnDestroy();
				const int SCREEN_WIDTH = 1920;
				const int SCREEN_HEIGHT = 1080;
				windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
				windowPtr->OnCreate();
				timer = new Timer();
				currentScene = new Scene1(windowPtr->GetSDL_Window());
				currentScene->OnCreate();
			}
			if (event.key.scancode == SDL_SCANCODE_F3) {
				GameManager::OnDestroy();
				const int SCREEN_WIDTH = 1920;
				const int SCREEN_HEIGHT = 1080;
				windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
				windowPtr->OnCreate();
				timer = new Timer();
				currentScene = new SceneInventory(windowPtr->GetSDL_Window());
				currentScene->OnCreate();
			}
		
		default:
			break;
		}

		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
	}

	if (timer) delete timer;

	if (windowPtr) {
		windowPtr->OnDestroy();
		delete windowPtr;
	}
}


