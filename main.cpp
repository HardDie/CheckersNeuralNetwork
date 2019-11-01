#include <iostream>
#include <map>
#include "grid.h"
#include "pool.h"
#include "study.h"
#include "game.h"

#include <random>
void MakeRandomStep( Grid &grid, GRID_VAL sign ) {
	std::random_device                   random_device;
	std::mt19937                         engine( random_device() );
	std::uniform_int_distribution< int > dist( 0, 8 );
	int                                  randValue;
	while ( true ) {
		randValue = dist( engine );
		if ( grid.MakeStep( randValue, sign ) ) {
			break;
		}
	}
}

void MakeAIStep( Study &study, Grid &grid, GRID_VAL sign ) {
	int step = study.GetStepForGrid( grid );
	std::cout << "Step: " << step << std::endl;
	if ( !grid.MakeStep( step, sign ) ) {
		std::cerr << __FUNCTION__ << "(): AI try make ERROR step\n";
		grid.Print();
		exit( -1 );
	}
}

int main( void ) {
	Grid  grid;
	Study study;
	Study study_second;

	int countStep = 0;

	while ( true ) {
		std::cout << "AI 1 step:\n";
		MakeAIStep( study_second, grid, GRID_X );
		// std::cout << "Random step:\n";
		// MakeRandomStep(grid, GRID_X);
		if ( Game::isGameOver( grid ) ) {
			study.LoseParty();
			study_second.ClearParty();
			std::cout << "Game counter: " << study_second.game_count
			          << std::endl;
			std::cout << "Lose\n";
			break;
		}
		countStep++;

		if ( countStep == 9 ) {
			study.LoseParty();
			study_second.ClearParty();
			std::cout << "Draw\n";
			countStep = 0;
			break;
		}

		std::cout << "AI 2 step:\n";
		MakeAIStep( study, grid, GRID_O );
		if ( Game::isGameOver( grid ) ) {
			study.WinParty();
			study_second.ClearParty();
			std::cout << "Game counter: " << study.game_count
			          << std::endl;
			std::cout << "Win\n";
			break;
		}
		countStep++;
	}

	std::cout << "Finish field:" << std::endl;
	grid.Print();

	return 0;
}
