#pragma once
#include <iostream>
#include "Entity.h"

class Inventory {
private:
	int setPageNum;
	bool UnlockedPage2;
	bool UnlockedPage3;
	bool UnlockedPage4;
	bool UnlockedPage5;
	bool isBookUnlocked;

public:
	Inventory(); //default constructor
	~Inventory(); //destructor
	void getItemAlarm(bool alarm);
	const char* openSlotPage(int pageNum);
	void openSlotAlarm();
	void UnlockSlotPage(int pageNum);
	void readBook(int pageNum);
	bool GetBookUnlocked(bool boolUnlocked); 
};


