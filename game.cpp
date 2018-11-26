#include "game.h"

bool Game::isGameOver(const Grid& grid) {
	if (grid[0] != GRID_EMPTY &&
	    grid[0] == grid[1] &&
	    grid[1] == grid[2]) {
		return true;
	}
	if (grid[3] != GRID_EMPTY &&
	    grid[3] == grid[4] &&
	    grid[4] == grid[5]) {
		return true;
	}
	if (grid[6] != GRID_EMPTY &&
	    grid[6] == grid[7] &&
	    grid[7] == grid[8]) {
		return true;
	}

	if (grid[0] != GRID_EMPTY &&
	    grid[0] == grid[3] &&
	    grid[3] == grid[6]) {
		return true;
	}
	if (grid[1] != GRID_EMPTY &&
	    grid[1] == grid[4] &&
	    grid[4] == grid[7]) {
		return true;
	}
	if (grid[2] != GRID_EMPTY &&
	    grid[2] == grid[5] &&
	    grid[5] == grid[8]) {
		return true;
	}

	if (grid[0] != GRID_EMPTY &&
	    grid[0] == grid[4] &&
	    grid[4] == grid[8]) {
		return true;
	}
	if (grid[6] != GRID_EMPTY &&
	    grid[6] == grid[4] &&
	    grid[4] == grid[2]) {
		return true;
	}

	return false;
}
