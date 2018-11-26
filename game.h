#pragma once

#include "grid.h"

class Game {
 public:
	Game() {}
	~Game() {}

	static bool isGameOver(const Grid& grid);
};
