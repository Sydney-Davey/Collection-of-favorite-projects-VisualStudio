#pragma once
#include <iostream>
#include "Entity.h"

class Difference : public Entity { //Class Difference, child of Entity
public:
	using Entity::Entity;//inherate all that good stuf from entity
	
	//Difference variables
	bool DiffItem = false; //is the item different or not

	void SetImage(const char* filename, const char* filenameDiff, SDL_Renderer* renderer); //Set image function, now using two images, for differences
	

};
