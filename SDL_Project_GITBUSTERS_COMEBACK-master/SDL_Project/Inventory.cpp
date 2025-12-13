#include "Inventory.h"
#include "Scene0.h"
#include "Entity.h"


//Rb/ sydney please add detials (comments)
Inventory::Inventory() :
	setPageNum(0),
	UnlockedPage2(false),
	UnlockedPage3(false),
	UnlockedPage4(false),
	UnlockedPage5(false),
	isBookUnlocked(false)
{}


Inventory::~Inventory() {}

void Inventory::getItemAlarm(bool alarm)
{
	if (alarm == true) {
		Inventory::openSlotAlarm();
	}
}

void Inventory::openSlotAlarm() {}

const char* Inventory::openSlotPage(int pageNum)
{
	switch (pageNum)
	{
	case 0: return "textures/FOLDER-Page1.jpg";
	case 1: return "textures/FOLDER-Page2.jpg";
	case 2: return "textures/FOLDER-Page3.jpg";
	case 3: return "textures/FOLDER-Page4.jpg";
	case 4: return "textures/FOLDER-Page5.jpg";
	default:
		return nullptr; // invalid page, or no texture
	}
}


void Inventory::UnlockSlotPage(int pageNum)
{
	//Sad/ collecting diffrent pages
	if (pageNum == 1) {
		std::cout << "Opening page " << pageNum << std::endl; 
		UnlockedPage2 = true;
	}
	else if (pageNum == 2) {
		std::cout << "Opening page " << pageNum << std::endl;
		UnlockedPage3 = true;
	}
	else if (pageNum == 3) {
		std::cout << "Opening page " << pageNum << std::endl;
		UnlockedPage4 = true;
	}
	else if (pageNum == 4) {
		std::cout << "Opening page " << pageNum << std::endl;
		UnlockedPage5 = true;
	}
	else {
		std::cout << "You Have Collected all the pages!" << std::endl;
	}
}

void Inventory::readBook(int pageNum)
{
	//sad/ open the menu and scroll through pages
	std::cout << "readBook called" << std::endl;
	UnlockSlotPage(pageNum);
}

bool Inventory::GetBookUnlocked(bool boolUnlocked)
{
	//sad/ Unlock Book Only
	return boolUnlocked = true;
}



