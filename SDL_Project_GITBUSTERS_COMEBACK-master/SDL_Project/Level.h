#pragma once
#include <iostream>
#include <vector>
#include "Difference.h"


	class Level {
	private:
		int Lvl_count; //how many loops the player has been on, what level this is
		int num_diffs; //how many differences are present in the level
		int RoomID; //what "room" of the level is the player at
	public: 
		bool diff_pres; //tracks if their are differences in this level or not


	public:
		Level(); //default constructor
		Level(int lvl, int num_diff, bool diff);//constructor
		void move(int space); //moves the player depending on the amount of spaces entered
		int CheckRoomID();
		int CheckLevelID();
		void setDifferences();
		void generate_Differences(std::vector<Difference*> DiffArray); //generates differences across the level states
	};

