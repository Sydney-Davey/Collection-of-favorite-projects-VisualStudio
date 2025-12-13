#include "Level.h"

Level::Level() { //Default constructor
	Lvl_count = 0;
	num_diffs = 0;
	diff_pres = false;
	RoomID = 0;
} //sets all values to null and continues

Level::Level(int lvl, int num_diff, bool diff) { //constructor
	Lvl_count = lvl; //Level number
	num_diffs = num_diff; //how many differences
	diff_pres = diff; //is their differences present?
	RoomID = 0; //What room the play is on

}

void Level::move(int space) { //Movment system between rooms 
	if (RoomID > 4) { //if room count goes about 3 (5 rooms) or below 0 (the start)
		RoomID = 0; //Reset to the begining
	}
	else { //if roomID is below 5
		if (space == 1) { //move the player forward if 1
			RoomID += 1; //Updates room count
		}
		else if (space == 0) {//move the player backwards if 0
			RoomID -= 1; //decreases room count
		}
		else { //scream at the developer if they put in anything besides a 1 or 0
			std::cout << "What are you doing? Error in level::move" << std::endl; //print screaming message to yell at already upset dev
			exit; //Gtfo
		}
	}
}

int Level::CheckRoomID() { //Sends room id down

	return RoomID; //Returns the room that the player is currently on
}

int Level::CheckLevelID() { //Sends the level Id

	return Lvl_count; //returns the leve count;
}

void Level::setDifferences() { //sets
	//Does Level contain differences?
	int RandomChance; //Random function, used for testing
	int Min_diffs; // Maximum differences for level
	int Diffs_pres; //How many differences are present in the level (Random)
	
	//Rb/ FIRST LEVEL (TUTORIAL)
	if (Lvl_count == 0) { //Tutorial, Do not change
		diff_pres = false; //Always false
	}
	//RB/ LEVEL'S 1,2,3,4, 2/10 ODDS FOR DIFFERENCE
	if (Lvl_count >= 1 && Lvl_count <= 4) { //If level is between 1 - 4...
		RandomChance = (rand() % 9); //Roll a chance of 2/10 for it to have differences.
		if (RandomChance <= 1) { //If random chance is 0 or 1...
			//differences present...
			diff_pres = true; //Differences present = true

			Min_diffs = 5; //The minimum amount of differences allowed for these levels is 5...
			Diffs_pres = (rand() % 3); //The maximum is 7, so roll a number between 0-3 to see what gets added to the minimum
			Diffs_pres += Min_diffs; //add the two together

			num_diffs = Diffs_pres; //Chance the number of differences to match the amount of differences we rolled
		}

		else {//if random chance is above 2/10...
			//no differences present
			diff_pres = false;
		}
	}

	//RB/ LEVEL'S 5,6,7, 4/10 ODDS FOR DIFFERENCE
	if (Lvl_count == 5 - 7) { //if level is between 5 - 7...
		RandomChance = (rand() % 9); //roll a chance of 4/10 for it to have differences
		if (RandomChance <= 3) { //if random chance is below 4/10...
			//differences present...
			diff_pres = true; //Differences present = true

			Min_diffs = 1; //The minimum amount of differences allowed for these levels is 1...
			Diffs_pres = (rand() % 2); //The maximum is 3, so roll a number between 0-2 to see what gets added to the minimum
			Diffs_pres += Min_diffs; //add the two together

			num_diffs = Diffs_pres; //Chance the number of differences to match the amount of differences we rolled
		}
		else { //if random chance is above 4/10...
			//no differences present
			diff_pres = false; //Differences present = false
		}
	}

	//RB/ LEVEL 8, 6/10 ODDS FOR DIFFERENCE
	if (Lvl_count == 8) { //If level is 8...
		RandomChance = (rand() % 9);  //roll a chance of 6/10 for it to have differences
		if (RandomChance <= 5) { //if random chance is below 4/10...
			//differences present...
			diff_pres = true; //Differences present = true

			Min_diffs = 1; //The minimum amount of differences allowed for these levels is 1...
			Diffs_pres = (rand() % 1); //The maximum is 2, so roll a number between 0-1 to see what gets added to the minimum
			Diffs_pres += Min_diffs; //add the two together

			num_diffs = Diffs_pres; //Chance the number of differences to match the amount of differences we rolled
		}
		else { //if random chance is below 6/10...
			//no differences present
			diff_pres = false; //Differences present = false
		}
	}

	//Rb/ LEVEL 9, DIFFERENCES ALWAYS PRESENT
	if (Lvl_count == 9) { //if level 9...
		diff_pres = true; //differences are always present...
		num_diffs = 1; //there is only one difference
	}
}

void Level::generate_Differences(std::vector<Difference*> DiffArray) { //RUBY : WORK IN PROGRESS/DO NOT TOUCH, LEST YOU BECOME APART OF THE HORDE!
	for (int d = 0; d < DiffArray.size(); d++) { //loops for all entries of our array
		DiffArray[d]->DiffItem = false; //Resets all values back to false, just in case
	}
	if (diff_pres == true) { //if the level has differences
	
		for (int i = 0; i < num_diffs && DiffArray.size(); i++) { //Loops for amount of differences present, and amount differences in the level.

			int O = (rand() % DiffArray.size());// generates which difference will actually be different
			//std::cout << R << std::endl; //used for testing randomness, delete later
			if (DiffArray[O]->DiffItem == true) { // If the difference selecected is already set to true
				i--; //Do nothing, remove 1 from loop to get a different item to make different
			}
			else if (DiffArray[O]->DiffItem == false) { //if the item isn't different
				DiffArray[O]->DiffItem = true; //make it different
			}

		}
	}



}

