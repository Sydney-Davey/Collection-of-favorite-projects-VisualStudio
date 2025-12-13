#include "Scene0.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"
#include "Difference.h"
#include "Inventory.h"



Scene0::Scene0(SDL_Window* sdlWindow_) :
	  window(sdlWindow_)
	, renderer(nullptr)
	, Arrow(nullptr)
	, UpArrow(nullptr)
	, DownArrow(nullptr)
	, UpArrowHover(nullptr)
	, DownArrowHover(nullptr)
	, RightArrow(nullptr)
	, LeftArrow(nullptr)
	, UnlockNum(0)
	, flashlight_player(nullptr)
	, flashlight_playerHover(nullptr)
	, Background1(nullptr)
	, Background2(nullptr)
	, Background3(nullptr)
	, Background4(nullptr)
	, flappy2(nullptr)
	, flappy3(nullptr)
	, noiseMakerButton(nullptr)
	, inventoryFolder(nullptr)
	, inventoryButton(nullptr)
	, flappyScale(2.0f)
	, pageNum(0)
	, book_inventory(nullptr)
	, BookUnlocked(false)
	, mouseTrue(false)
	, isFolderThere(false)
	, isUpArrow(false)
	, isDownArrow(false)
	, isInventory(false)
	, isFlashlight(false)
	, wendigo(nullptr)
	, hordeSize(0)
	, horde()
	, xAxis(30.0f)
	, yAxis(15.0f)
	, mixer()
	, Screennum(0)
	, poo() //Level for our game, controls room number, differences present, etc
	, DiffArray{} //Array of differences in the level
	, noiseSound(nullptr)
	, flashAlpha(0.0f)
	, flashDuration(1.0f)
	, flashTimer(0.0f)
	, isFlashing(false)
	, gameStart(false)
	, TutorialScreen(nullptr)
	, TutorialStart(nullptr)
{ }

Scene0::~Scene0(){ }

bool Scene0::OnCreate() {
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

				// Main HUD //
	
	// Buttons //
	UpArrow = new Entity();
	UpArrow->pos = Vec3(11.5f, 15.0f, 0.0f);
	UpArrow->SetImage("textures/ArrowUp.png", renderer);

	DownArrow = new Entity();
	DownArrow->pos = Vec3(11.5f, 2.5f, 0.0f);
	DownArrow->SetImage("textures/ArrowDown.png", renderer);

	UpArrowHover = new Entity();
	UpArrowHover->pos = Vec3(11.5f, 15.0f, 0.0f);
	UpArrowHover->SetImage("textures/ArrowUpHover.png", renderer);

	DownArrowHover = new Entity();
	DownArrowHover->pos = Vec3(11.5f, 2.5f, 0.0f);
	DownArrowHover->SetImage("textures/ArrowDownHover.png", renderer);
	//////////////

	noiseMakerButton = new Entity();
	noiseMakerButton->pos = Vec3(0.5f, 5.5f, 0.0f);
	noiseMakerButton->SetImage("textures/NoiseMaker.png", renderer);

	inventoryButton = new Entity();
	inventoryButton->pos = Vec3(0.0f, 3.0f, 0.0f);
	inventoryButton->SetImage("textures/FOLDER.jpg", renderer);

				// Inventory HUD //

	LeftArrow = new Entity();
	LeftArrow->pos = Vec3(0.0f, 10.5f, 0.0f);
	LeftArrow->SetImage("textures/ArrowLeft.png", renderer);

	RightArrow = new Entity();
	RightArrow->pos = Vec3(25.51f, 10.5f, 0.0f);
	RightArrow->SetImage("textures/ArrowRight.png", renderer);

	// inventoryFolder
	inventoryFolder = new Entity();
	inventoryFolder->pos = Vec3(14.0f, 10.0f, 0.0f);
	inventoryFolder->SetImage("textures/FOLDER.jpg", renderer);

	//////////////////

	flashlight_player = new Entity();
	flashlight_player->pos = Vec3(0.0f, 0.0f, 0.0f);
	flashlight_player->SetImage("textures/FlashlightNEW.png", renderer);

	flashlight_playerHover = new Entity();
	flashlight_playerHover->pos = Vec3(0.0f, 0.0f, 0.0f);
	flashlight_playerHover->SetImage("textures/FlashlightNEWFlash.png", renderer);

	Background1 = new Entity();
	Background1->pos = Vec3(2.0f, 15.0f, 0.0f);
	Background1->SetImage("textures/Background/Background/ForestLoop1.png", renderer);

	Background2 = new Entity();
	Background2->pos = Vec3(2.0f, 15.0f, 0.0f);
	Background2->SetImage("textures/Background/Background/ForestLoop2.png", renderer);

	Background3 = new Entity();
	Background3->pos = Vec3(2.0f, 15.0f, 0.0f);
	Background3->SetImage("textures/Background/Background/ForestLoop3.png", renderer);

	Background4 = new Entity();
	Background4->pos = Vec3(2.0f, 15.0f, 0.0f);
	Background4->SetImage("textures/Background/Background/ForestLoop4.png", renderer);

	flappy2 = new Entity();
	flappy2->pos = Vec3(10.0f, 5.0f, 0.0f);
	flappy2->SetImage("textures/flappyBird.png", renderer);

	flappy3 = new Entity();
	flappy3->pos = Vec3(10.0f, 15.0f, 0.0f);
	flappy3->SetImage("textures/flappyBird.png", renderer);

	// threat test //
	// seed the random number generator
	SDL_srand(SDL_GetPerformanceCounter());

	wendigo = new Threat();
	wendigo->threatName = "Wendigo";
	wendigo->spwanChance = 2; //20% chance to spawn
	wendigo->radius = 1.0f;
	wendigo->pos = Vec3(-100.0f, -100.0f, 0.0f);
	wendigo->SetImage("textures/scott.png", renderer);

	hordeSize = 3;
	for (int i = 0; i < hordeSize;i++) {
		Threat* newHordeMember = new Threat();

		newHordeMember->threatName = "Horde" + std::to_string(i + 1); //name each threat in the horde like Horde1, Horde2, etc.
		newHordeMember->spwanChance = 2; //each horde member has a 20% chance to spawn
		newHordeMember->radius = 1.0f;
		newHordeMember->pos = Vec3(-100.0f, -100.0f, 0.0f);

		std::string filename = "textures/scottHorde" + std::to_string(i + 1) + ".png"; //different texture for each horde member
		newHordeMember->SetImage(filename.c_str(), renderer);

		horde.push_back(newHordeMember);
	}
	 

	

	for (int d = 0; d < 11; d++) {
		DiffArray.push_back(new Difference());	
		//DiffArray[d]->SetImage("textures/flappyBird.png", "textures/Ball.png", renderer);
	}
	//set the pos of all our differences
	DiffArray[0]->pos = Vec3(15.0f, 15.0f, 0.0f);
	DiffArray[1]->pos = Vec3(0.0f, 6.0f, 0.0f);
	DiffArray[2]->pos = Vec3(10.0f, 5.0f, 0.0f);
	DiffArray[3]->pos = Vec3(10.0f, 15.0f, 0.0f);
	DiffArray[4]->pos = Vec3(16.0f, 14.0f, 0.0f);
	DiffArray[5]->pos = Vec3(1.0f, 5.0f, 0.0f);
	DiffArray[6]->pos = Vec3(11.0f, 4.0f, 0.0f);
	DiffArray[7]->pos = Vec3(12.0f, 13.0f, 0.0f);
	DiffArray[8]->pos = Vec3(17.0f, 10.0f, 0.0f);
	DiffArray[9]->pos = Vec3(7.0f, 6.0f, 0.0f);
	DiffArray[10]->pos = Vec3(17.0f, 0.0f, 0.0f);

	poo = Level(LevelCount, 2, true); //our level,
	poo.setDifferences();
	poo.generate_Differences(DiffArray); //Generates differences if the level differences is true
	if (poo.diff_pres == true) {
		std::cout << "diffs pres" << std::endl;
		LevelDiffsPresent = true;
	}
	if (poo.diff_pres == false) {
		std::cout << "diffs no pres" << std::endl;
		LevelDiffsPresent = false;
	}
	for (int d = 0; d < 11; d++) { //loops for all entries of our array
		DiffArray[d]->SetImage("textures/flappyBird.png", "textures/Ball.png", renderer); //set the image depending on the state of the difference
	}


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

	//load noise sound
	noiseSound = MIX_LoadAudio(mixer, "Audio/noiseSound2.wav", true);


	// Flash transition setup
	isFlashing = false;
	flashAlpha = 0.0f;
	flashDuration = 2.0f;
	flashTimer = 0.0f;

	if (LevelCount == 0) {
		TutorialScreen = new Entity();
		TutorialScreen->SetImage("textures/Tutorial.png", renderer);
		TutorialScreen->pos = Vec3(0.0f, 15.0f, 0.0f);
		TutorialStart = new Entity();
		TutorialStart->pos = Vec3(11.5f, 4.5f, 0.0f); 
		TutorialStart->SetImage("textures/StartButton.png", renderer);
	}
	else {
		startgame = true;
	}


	return true;
}

void Scene0::OnDestroy() {
	// Clean up the renderer
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (TutorialScreen != nullptr) {
		delete TutorialScreen;
		TutorialScreen = nullptr;
		delete TutorialStart; 
		TutorialStart = nullptr;
	}
	//// Turn off audio
	if (mixer)
	{
		MIX_DestroyMixer(mixer);
		MIX_Quit();
	}

	// Delete the objects created on the heap
	// and set to the null pointer just to be safe
	delete UpArrow;
	UpArrow = nullptr;

	delete DownArrow;
	DownArrow = nullptr;

	delete UpArrowHover;
	UpArrow = nullptr;

	delete DownArrowHover;
	DownArrow = nullptr;

	delete LeftArrow;
	LeftArrow = nullptr;

	delete RightArrow;
	RightArrow = nullptr;

	delete noiseMakerButton;
	noiseMakerButton = nullptr;

	delete inventoryButton;
	inventoryButton = nullptr;

	delete inventoryFolder;
	inventoryFolder = nullptr;

	delete flashlight_playerHover;
	flashlight_playerHover = nullptr;

	delete flashlight_player;
	flashlight_player = nullptr;

	delete Background1;
	Background1 = nullptr;

	delete flappy2;
	flappy2 = nullptr;

	delete flappy3;
	flappy3 = nullptr;

	//threat test delete
	delete wendigo;
	wendigo = nullptr;

	for (Threat* threat : horde) {
		delete threat; 
		threat = nullptr;
	}
	horde.clear();

	delete book_inventory;
	book_inventory = nullptr;


	for (int d = 0; d < DiffArray.size(); d++) { // deletes all 4 entries of the array
		delete DiffArray[d];
		DiffArray[d] = nullptr;
	}

	MIX_DestroyAudio(noiseSound);

}

void Scene0::HandleEvents(const SDL_Event& event)
{
	float mouseX, mouseY; //Mouse X and Y pos
	SDL_GetMouseState(&mouseX, &mouseY); //sets our float value to both the mouses X and Y pos on screen
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:

		if (event.key.scancode == SDL_SCANCODE_1) {
			BookUnlocked = true;
			std::cout << "SDL_EVENT_MOUSE_WHEEL called: BookUnlocked = BookUnlocked #" << BookUnlocked << std::endl;

		}
		break;

	// Mouse and Buttons
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	{
		float mx = event.button.x;
		float my = event.button.y;
		if (TutorialStart != nullptr) {
			if (TutorialStart->UpdateHover(mx, my) && !mouseTrue) {
				startgame = true;
				break;
			}
		}
		if (event.button.button == SDL_BUTTON_LEFT && startgame == true)
		{
			
	
			//Tutorial button
			
			// Up Arrow
			if (UpArrow->UpdateHover(mx, my) && !mouseTrue)
			{
				std::cout << "UP ARROW CLICKED\n";
				poo.move(1);

				
				// Threat test spawn on key press
				if (poo.CheckLevelID() == 2) { // not spwan on level 1
					// level 2 spawn wendigo only
					wendigo->spwanThreat();
				}
				else if (poo.CheckLevelID() >= 3) {
					// level 3 and up spawn wendigo and horde

					// check if any horde members are already active
					bool isAnyHordeActive = false;
					for(Threat* t : horde) {
						if (t->isThreatActive) {
							isAnyHordeActive = true;
							break;
						}
					}

					// if no threats are active, spawn either wendigo or a random horde member
					if (!isAnyHordeActive && !wendigo->isThreatActive) {
						int randomType = SDL_rand(2);
						if (randomType == 0) {
							// spawn wendigo
							wendigo->spwanThreat();
						}
						else {
							// spawn a random horde member
							int randomIndex = SDL_rand(hordeSize);
							horde[randomIndex]->spwanThreat();
						}
					}
				}
				
			}

			// Down Arrow
			else if (DownArrow->UpdateHover(mx, my) && !mouseTrue)
			{
				std::cout << "DOWN ARROW CLICKED\n";
				poo.move(0);
			}

			//Noise Maker
			else if (noiseMakerButton->UpdateHover(mx, my) && !mouseTrue)
			{
				std::cout << "NOISE MAKER BUTTON CLICKED\n";
				NoiseMakerOn();

				isFlashing = true;
				flashAlpha = 1.0f; // start fully white
				flashTimer = 0.0f;

				//remove horde from screen
				for (Threat* t : horde) {
					if (t->isThreatActive) {
						t->threatReset();
					}
				}
				
			}

			// Inventory Open Button
			else if (inventoryButton->UpdateHover(mx, my) && BookUnlocked && poo.CheckRoomID() == 0)
			{
				std::cout << "INVENTORY BUTTON CLICKED " << mouseTrue << std::endl;
				startgame = 2;
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
		
		//flashlight offset
		
			v1.x -= 40.5f; //across 40.0f
			v1.y += 21.0f; //down 24.0f

			//allows the flaslight to follow your mouse
			if (isFlashlight) {
				flashlight_playerHover->pos = v1;
			}
			else if (!isFlashlight){
				flashlight_player->pos = v1; //v1 being our mouse
			}

		

		float mx = event.button.x;
		float my = event.button.y;
		

		if (DownArrow->UpdateHover(mx, my))
		{
			isDownArrow = true;
		}
		else {
			isDownArrow = false;
		}

		if (UpArrow->UpdateHover(mx, my))
		{
			isUpArrow = true;
		}
		else {
			isUpArrow = false;
		}

		if (wendigo->UpdateHover(mx, my))
		{
			isFlashlight = true;
			wendigo->stunThreat();
		}
		else {
			isFlashlight = false;
		}

		//Tutorial button hover and start game
		if (TutorialStart != nullptr) {
			if (!mouseTrue && TutorialStart->UpdateHover(mx, my)) {
				TutorialStart->SetImage("textures/StartButtonHover.png", renderer);
				break;
			}
			else {
				TutorialStart->SetImage("textures/StartButton.png", renderer);
				break;
			}
		}

		break;
	}

	default:
		break;
	}
}

void Scene0::Update(const float deltaTime) {
	//Code for room switching. leave for now
	
	if (poo.CheckRoomID() == 0) {
		Screennum = poo.CheckRoomID();
	}
	else if (poo.CheckRoomID() == 1) {
		Screennum = poo.CheckRoomID();
	}
	else if (poo.CheckRoomID() == 2) {
		Screennum = poo.CheckRoomID();
	} 
	else if (poo.CheckRoomID() == 3) {
		Screennum = poo.CheckRoomID();
	}

	//threat kill test
	wendigo->threatTimer(deltaTime);
	wendigo->threatMoving();
	if (wendigo->threatTimer(deltaTime) == true) {
		wendigo->kill();
	}	


	for (Threat* hordeMember : horde)
	{
		bool isTimeout = hordeMember->threatTimer(deltaTime);
		if(isTimeout == true) {
			hordeMember->kill();
		}
	}

	// Flash transition update
	if (isFlashing) {
		flashTimer += deltaTime;

		flashAlpha = 255.0f * (1.0f - (flashTimer / flashDuration)); // fade out over flash duration

		if (flashTimer >= flashDuration) { // end of flash
			isFlashing = false;
			flashAlpha = 0.0f;
		}
	}



	
} 



void Scene0::Render() const {
	SDL_RenderClear(renderer);
	// Convert from world coordinates to pixel coordinates using Scott's magical matrix
	Vec3 screenCoords;
	// Set up sprite's position and size
	SDL_FRect square;

	//Rb/Displays the correct differences per screen

	// Background 1
	screenCoords = projectionMatrix * Background1->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	if (Background1->GetSurface() != nullptr) {
		square.w = Background1->GetSurface()->w * 2.5; // we will scale the bird 
		square.h = Background1->GetSurface()->h * 2;
	}
	if (Screennum == 0) {
		SDL_RenderTextureRotated(renderer, Background1->GetTexture(), nullptr, &square, Background1->angleDeg, nullptr, SDL_FLIP_NONE);
	}


	// Background 2
	screenCoords = projectionMatrix * Background2->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	if (Background2->GetSurface() != nullptr) {
		square.w = Background2->GetSurface()->w * 2.5; // we will scale the bird 
		square.h = Background2->GetSurface()->h * 2;
	}
	if (Screennum == 1) {
		SDL_RenderTextureRotated(renderer, Background2->GetTexture(), nullptr, &square, Background2->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Background 3
	screenCoords = projectionMatrix * Background3->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	if (Background3->GetSurface() != nullptr) {
		square.w = Background3->GetSurface()->w * 2.5; // we will scale the bird 
		square.h = Background3->GetSurface()->h * 2;
	}
	if (Screennum == 2) {
		SDL_RenderTextureRotated(renderer, Background3->GetTexture(), nullptr, &square, Background3->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Background 4
	screenCoords = projectionMatrix * Background4->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	if (Background4->GetSurface() != nullptr) {
		square.w = Background4->GetSurface()->w * 2.5; // we will scale the bird 
		square.h = Background4->GetSurface()->h * 2;
	}
	if (Screennum == 3) {
		SDL_RenderTextureRotated(renderer, Background4->GetTexture(), nullptr, &square, Background4->angleDeg, nullptr, SDL_FLIP_NONE);
	}
 
	// Wendigo render test //
	screenCoords = projectionMatrix * wendigo->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = wendigo->GetSurface()->w * wendigo->radius; // scale based on radius for when it gets closer
	square.h = wendigo->GetSurface()->h * wendigo->radius;
	wendigo->rect.x = screenCoords.x;
	wendigo->rect.y = screenCoords.y;
	wendigo->rect.w = wendigo->GetSurface()->w * wendigo->radius;
	wendigo->rect.h = wendigo->GetSurface()->h * wendigo->radius;
	if (mouseTrue == false) {
		SDL_RenderTextureRotated(renderer, wendigo->GetTexture(), nullptr, &square, wendigo->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Render horde members //
	for(Threat* hordeMember : horde)
	{
		screenCoords = projectionMatrix * hordeMember->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = hordeMember->GetSurface()->w * hordeMember->radius;
		square.h = hordeMember->GetSurface()->h * hordeMember->radius;
		hordeMember->rect.x = screenCoords.x;
		hordeMember->rect.y = screenCoords.y;
		hordeMember->rect.w = hordeMember->GetSurface()->w * hordeMember->radius;
		hordeMember->rect.h = hordeMember->GetSurface()->h * hordeMember->radius;
		if (mouseTrue == false) {
			SDL_RenderTextureRotated(renderer, hordeMember->GetTexture(), nullptr, &square, hordeMember->angleDeg, nullptr, SDL_FLIP_NONE);
		}
	}


	
	//Switch Statement, Dispalys differences based off the screen the player is on
	switch (Screennum) { //Based on what number of the screen the player is on
	case 0:
		for (int R = 0; R < 2; R++) { //Displays differences 1-2
			screenCoords = projectionMatrix * DiffArray[R]->pos;
			square.x = screenCoords.x;
			square.y = screenCoords.y;
			square.w = DiffArray[R]->GetSurface()->w * 2;
			square.h = DiffArray[R]->GetSurface()->h * 2;
			SDL_RenderTextureRotated(renderer, DiffArray[R]->GetTexture(), nullptr, &square, DiffArray[R]->angleDeg, nullptr, SDL_FLIP_NONE);
		}
		break;
	case 1:
		for (int R = 2; R < 4; R++) {//Displays differences 3-4
			screenCoords = projectionMatrix * DiffArray[R]->pos;
			square.x = screenCoords.x;
			square.y = screenCoords.y;
			square.w = DiffArray[R]->GetSurface()->w * 2;
			square.h = DiffArray[R]->GetSurface()->h * 2;
			SDL_RenderTextureRotated(renderer, DiffArray[R]->GetTexture(), nullptr, &square, DiffArray[R]->angleDeg, nullptr, SDL_FLIP_NONE);
		}
		break;
	case 2:
		for (int R = 4; R < 6; R++) {//Displays differences 4-5
			screenCoords = projectionMatrix * DiffArray[R]->pos;
			square.x = screenCoords.x;
			square.y = screenCoords.y;
			square.w = DiffArray[R]->GetSurface()->w * 2;
			square.h = DiffArray[R]->GetSurface()->h * 2;
			SDL_RenderTextureRotated(renderer, DiffArray[R]->GetTexture(), nullptr, &square, DiffArray[R]->angleDeg, nullptr, SDL_FLIP_NONE);
		}
		break;
	case 3:
		for (int R = 6; R < 9; R++) { //Displays differences 5-8
			screenCoords = projectionMatrix * DiffArray[R]->pos;
			square.x = screenCoords.x;
			square.y = screenCoords.y;
			square.w = DiffArray[R]->GetSurface()->w * 2;
			square.h = DiffArray[R]->GetSurface()->h * 2;
			SDL_RenderTextureRotated(renderer, DiffArray[R]->GetTexture(), nullptr, &square, DiffArray[R]->angleDeg, nullptr, SDL_FLIP_NONE);
		}
		break;
	}

	// Folder
	screenCoords = projectionMatrix * inventoryFolder->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = inventoryFolder->GetSurface()->w * 0.06f;
	square.h = inventoryFolder->GetSurface()->h * 0.06f;
	screenCoords = projectionMatrix * inventoryFolder->pos;
	inventoryFolder->rect.x = screenCoords.x;
	inventoryFolder->rect.y = screenCoords.y;
	inventoryFolder->rect.w = inventoryFolder->GetSurface()->w * 0.06f;
	inventoryFolder->rect.h = inventoryFolder->GetSurface()->h * 0.06f;
	if (isFolderThere == true && mouseTrue == false) {
		SDL_RenderTextureRotated(renderer, inventoryFolder->GetTexture(), nullptr, &square, inventoryFolder->angleDeg, nullptr, SDL_FLIP_NONE);
	}


			// ARROWS //
	if (startgame == true) {
		// Up Arrow
		screenCoords = projectionMatrix * UpArrow->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = UpArrow->GetSurface()->w * 0.6f;
		square.h = UpArrow->GetSurface()->h * 0.6f;
		screenCoords = projectionMatrix * UpArrow->pos;
		UpArrow->rect.x = screenCoords.x;
		UpArrow->rect.y = screenCoords.y;
		UpArrow->rect.w = UpArrow->GetSurface()->w * 0.6f;
		UpArrow->rect.h = UpArrow->GetSurface()->h * 0.6f;
		if (!isUpArrow) {
			SDL_RenderTextureRotated(renderer, UpArrow->GetTexture(), nullptr, &square, UpArrow->angleDeg, nullptr, SDL_FLIP_NONE);
		}

		// Down Arrow
		screenCoords = projectionMatrix * DownArrow->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = DownArrow->GetSurface()->w * 0.6f;
		square.h = DownArrow->GetSurface()->h * 0.6f;
		DownArrow->rect.x = screenCoords.x;
		DownArrow->rect.y = screenCoords.y;
		DownArrow->rect.w = DownArrow->GetSurface()->w * 0.6f;
		DownArrow->rect.h = DownArrow->GetSurface()->h * 0.6f;
		if (!isDownArrow) {
			SDL_RenderTextureRotated(renderer, DownArrow->GetTexture(), nullptr, &square, DownArrow->angleDeg, nullptr, SDL_FLIP_NONE);
		}

		// Up Arrow Hover
		screenCoords = projectionMatrix * UpArrowHover->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = UpArrowHover->GetSurface()->w * 0.6f;
		square.h = UpArrowHover->GetSurface()->h * 0.6f;
		screenCoords = projectionMatrix * UpArrowHover->pos;
		UpArrowHover->rect.x = screenCoords.x;
		UpArrowHover->rect.y = screenCoords.y;
		UpArrowHover->rect.w = UpArrowHover->GetSurface()->w * 0.6f;
		UpArrowHover->rect.h = UpArrowHover->GetSurface()->h * 0.6f;
		if (isUpArrow) {
			SDL_RenderTextureRotated(renderer, UpArrowHover->GetTexture(), nullptr, &square, UpArrowHover->angleDeg, nullptr, SDL_FLIP_NONE);
		}

		// Down Arrow Hover
		screenCoords = projectionMatrix * DownArrowHover->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = DownArrowHover->GetSurface()->w * 0.6f;
		square.h = DownArrowHover->GetSurface()->h * 0.6f;
		DownArrowHover->rect.x = screenCoords.x;
		DownArrowHover->rect.y = screenCoords.y;
		DownArrowHover->rect.w = DownArrowHover->GetSurface()->w * 0.6f;
		DownArrowHover->rect.h = DownArrowHover->GetSurface()->h * 0.6f;
		if (isDownArrow) {
			SDL_RenderTextureRotated(renderer, DownArrowHover->GetTexture(), nullptr, &square, DownArrowHover->angleDeg, nullptr, SDL_FLIP_NONE);
		}
		////////////////////////////////


		// Noise Maker Button
		screenCoords = projectionMatrix * noiseMakerButton->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = noiseMakerButton->GetSurface()->w * 0.06f;
		square.h = noiseMakerButton->GetSurface()->h * 0.06f;
		noiseMakerButton->rect.x = screenCoords.x;
		noiseMakerButton->rect.y = screenCoords.y;
		noiseMakerButton->rect.w = noiseMakerButton->GetSurface()->w * 0.06f;
		noiseMakerButton->rect.h = noiseMakerButton->GetSurface()->h * 0.06f;
		SDL_RenderTextureRotated(renderer, noiseMakerButton->GetTexture(), nullptr, &square, noiseMakerButton->angleDeg, nullptr, SDL_FLIP_NONE);

		// Inventory Button
		screenCoords = projectionMatrix * inventoryButton->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = inventoryButton->GetSurface()->w * 0.05f;
		square.h = inventoryButton->GetSurface()->h * 0.05f;
		inventoryButton->rect.x = screenCoords.x;
		inventoryButton->rect.y = screenCoords.y;
		inventoryButton->rect.w = inventoryButton->GetSurface()->w * 0.05f;
		inventoryButton->rect.h = inventoryButton->GetSurface()->h * 0.05f;
		SDL_RenderTextureRotated(renderer, inventoryButton->GetTexture(), nullptr, &square, inventoryButton->angleDeg, nullptr, SDL_FLIP_NONE);

	}
	//RB/ IMPORTANT, LEAVE FLASHLIGHT AT THE BOTTOM OF THE RENDERER, SO IT WILL BE ON THE TOP LAYER OF EVERYTHING ELSE
	screenCoords = projectionMatrix * flashlight_player->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	if (Background4->GetSurface() != nullptr) {
		square.w = flashlight_player->GetSurface()->w * 7.0f;
		square.h = flashlight_player->GetSurface()->h * 7.0f;
	}
	if (!isFlashlight) {
		SDL_RenderTextureRotated(renderer, flashlight_player->GetTexture(), nullptr, &square, flashlight_player->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	screenCoords = projectionMatrix * flashlight_playerHover->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	if (flashlight_playerHover->GetSurface() != nullptr) {
		square.w = flashlight_playerHover->GetSurface()->w * 7.0f;
		square.h = flashlight_playerHover->GetSurface()->h * 7.0f;
	}
	if (isFlashlight) {
		SDL_RenderTextureRotated(renderer, flashlight_playerHover->GetTexture(), nullptr, &square, flashlight_playerHover->angleDeg, nullptr, SDL_FLIP_NONE);
	}

	// Flash effect // Flashy white screen when noise maker is used //on top of everything
	if(isFlashing && flashAlpha > 0.0f) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, (Uint8)flashAlpha);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_FRect fullScreen = { 0, 0, 1280, 720 };
		SDL_RenderFillRect(renderer, &fullScreen);
	}

	//Tutiorial screen
	if (LevelCount == 0 && startgame == false) {
		screenCoords = projectionMatrix * TutorialScreen->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = TutorialScreen->GetSurface()->w ;
		square.h = TutorialScreen->GetSurface()->h;
		TutorialScreen->rect.x = screenCoords.x;
		TutorialScreen->rect.y = screenCoords.y;
		TutorialScreen->rect.w = TutorialScreen->GetSurface()->w;
		TutorialScreen->rect.h = TutorialScreen->GetSurface()->h;
		SDL_RenderTextureRotated(renderer, TutorialScreen->GetTexture(), nullptr, &square, TutorialScreen->angleDeg, nullptr, SDL_FLIP_NONE);

		screenCoords = projectionMatrix * TutorialStart->pos;
		square.x = screenCoords.x;
		square.y = screenCoords.y;
		square.w = TutorialStart->GetSurface()->w * 0.6f;
		square.h = TutorialStart->GetSurface()->h * 0.6f;
		TutorialStart->rect.x = screenCoords.x;
		TutorialStart->rect.y = screenCoords.y;
		TutorialStart->rect.w = TutorialStart->GetSurface()->w * 0.6f;
		TutorialStart->rect.h = TutorialStart->GetSurface()->h * 0.6f;
		SDL_RenderTextureRotated(renderer, TutorialStart->GetTexture(), nullptr, &square, TutorialStart->angleDeg, nullptr, SDL_FLIP_NONE);
	}





	// Update the screen
	SDL_RenderPresent(renderer);
}

int Scene0::SceneSwitch()
{
	if (LevelCount == 9) {
		if (poo.CheckRoomID() == -1) {
			FrontDoorUsed = false;
			return 3;
		}
		if (poo.CheckRoomID() > 3) {
			FrontDoorUsed = true;
			return 3;
		}
	}
	if (poo.CheckRoomID() == -1) {
		FrontDoorUsed = false;
		return 1;
	}
	if (poo.CheckRoomID() > 3) {
		FrontDoorUsed = true;
		return 1;
	}

	if (startgame == 0){
		return 0;
	}
	if (startgame == 2) {
		return 2;
	}
}

// Sunny -- Noise Maker Audio Function
bool Scene0::NoiseMakerOn()
{
	if (noiseSound != nullptr) {
		MIX_PlayAudio(mixer, noiseSound);	
		return true;
	}
	else {
		cout << "Failed to play noise sound:" << SDL_GetError() << endl;
	}
	return false;
}
