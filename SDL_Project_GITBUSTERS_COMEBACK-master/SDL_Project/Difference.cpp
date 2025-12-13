#include "Difference.h"

void Difference::SetImage(const char* filename, const char* filenameDiff, SDL_Renderer* renderer) { //Rb/ Two images to swap between depending on Diff
	if (DiffItem == false) { //if the item is not different at all
		surface = IMG_Load(filename); //load up it's default sprite
		if (surface == nullptr) { //if sprite does not exist or is corrputed
			std::cerr << "Oh fuck, problem in Difference.pp::setImage If false statement" << std::endl; //prints out error message
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}
	else if (DiffItem == true) { // if the item is different
		surface = IMG_Load(filenameDiff); //load up it's different sprite
		if (surface == nullptr) { //if sprite does not exist or is corrputed
			std::cerr << "Oh shit, problem in Difference.pp::setImage If true statement" << std::endl; //prints out error message
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}
}
