#pragma once
#include <iostream>
#include "Entity.h"
#include "Level.h"
using namespace std;

class Threat : public Entity {
private:
	float startTime;
	float currentTime; //timer for threat to kill player
	float threatSize; //size of the threat
	float stunTimer = 0.0f; //timer for Wendigo stun duration when flashlight is shined on it
	const float stunDuration = 2.0f; //duration of the stun in seconds

public:
	bool isThreatActive; //is the threat currently active in the game
	string threatName; //name of the threat
	int spwanChance; //chance of threat appearing from 0-10
	
	Threat(); //default constructor
	Threat(string name, int chance, bool isThreatActive_, float StartTime_, float currentTime_, float threatSize_); //parameterized constructor

	void spwanThreat(); //function to spawn the threat
	bool threatTimer(float deltatime); //player got killed and end game
	void threatMoving();
	void kill();
	void threatReset();
	void stunThreat();
};
