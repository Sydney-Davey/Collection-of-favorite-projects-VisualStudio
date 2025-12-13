#include "Threat.h"
#include <SDL3/SDL.h>


Threat::Threat()
{
	threatName = "unknown";
	spwanChance = 0;
	isThreatActive = false;
	startTime = 12.0f;
	currentTime = startTime;
	threatSize = this->radius;
}

Threat::Threat(string name, int chance, bool isThreatActive_, float StartTime_, float currentTime_, float threatSize_)
{
	threatName = name;
	spwanChance = chance;
	isThreatActive = isThreatActive_;
	startTime = StartTime_;
	currentTime = currentTime_;
	threatSize = threatSize_;
}

void Threat::spwanThreat()
{
	// Generate a random number between 0 and 9
	int randomValue = SDL_rand(10);

	if (randomValue < spwanChance) {
		this->pos = Vec3(3.0f, 15.0f, 0.0f);
		std::cout << "Threat " << threatName << " has spawned!" << std::endl;
		isThreatActive = true;
	}
	else {
		// Move the threat off-screen if it doesn't spawn
		std::cout << "No threat spawned this time." << std::endl;
		isThreatActive = false;
	}
}

// Function to handle the Timer before threat killing 
bool Threat::threatTimer(float deltatime)
{

	if(isThreatActive) { 

		// If the threat is stunned, decrease the stun timer
		if (stunTimer > 0.0f) {
			stunTimer -= deltatime;
			cout << "Stun remaining: " << stunTimer << "(Timer paused)" << endl;
			return false; // Player is safe while stunned
		}

		if (currentTime > 0) {
			currentTime -= deltatime; // Decrease the timer by delta time
			cout << currentTime << endl;
		}
			
	}


	if (isThreatActive && currentTime <= 0) {
		return true; // Player is killed
	}
	else {
		return false; // Player is safe
	}
}

void Threat::threatMoving() {
	if (!isThreatActive) { // do nothing if threat is not active
		threatReset();
	}

	// start moving the threat based on the current time
	if (currentTime <= 9 && currentTime > 6) {
		this->pos = Vec3(18.0f, 15.0f, 0.0f);

		//increase size as it gets closer
		this->radius = threatSize + 0.5f;
	
	}
	else if (currentTime <= 6 && currentTime > 3) {
		this->pos = Vec3(2.0f, 15.0f, 0.0f);

		//increase size as it gets closer
		this->radius = threatSize + 1.0f;
		

	}
	else if (currentTime <= 3 && currentTime > 0) {
		this->pos = Vec3(4.0f, 15.0f, 0.0f);

		//increase size as it gets closer
		this->radius = threatSize + 1.5f;
	}
}

// Function to handle Killing machanics
void Threat::kill()
{
		std::cout << "Player has been killed by " << threatName << "! Game Over." << std::endl;
		threatReset(); 

		// TODO: Implement game over logic here (e.g., reset game, show game over screen, etc.)
		SDL_Quit();
}

//reset threat to inactive state 
void Threat::threatReset()
{
	isThreatActive = false;
	currentTime = startTime;
	this->radius = threatSize;
	this->pos = Vec3(-100.0f, -100.0f, 0.0f); // Move threat off-screen
}

void Threat::stunThreat()
{	// Activate stun only if the threat is active and not already stunned
	if (isThreatActive && stunTimer <= 0.0f) {
		stunTimer = stunDuration;
		std::cout << "Threat has been STUNNED! Timer paused." << std::endl;
	}
}





