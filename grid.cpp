#include <iostream>
#include <fstream>
#include "grid.h"

static const char GRID_STR[3] = { '-', 'X', 'O' };

Grid::Grid(void) {
	gridVal_.fill(GRID_EMPTY);
}

Grid::Grid(const std::string &string) {
	std::string s = string;
	std::string delimiter = " ";
	size_t pos = 0;
	std::string token;

	int index = 0;
	while ((pos = s.find(delimiter))
	       != std::string::npos) {
		token = s.substr(0, pos);

		if (token == "0") {
			gridVal_[index++] = GRID_EMPTY;
		} else if (token == "1") {
			gridVal_[index++] = GRID_X;
		} else if (token == "2") {
			gridVal_[index++] = GRID_O;
		} else {
			std::cerr << __FUNCTION__
			          << "(): Wrong grid element value!\n";
		}

		s.erase(0,
		    pos + delimiter.length());
	}

	if (index != 9) {
		std::cerr << __FUNCTION__
		          << "(): Not enough elements in input string!\n";
	}
}

Grid::Grid(GRID_VAL val0, GRID_VAL val1,
           GRID_VAL val2, GRID_VAL val3,
           GRID_VAL val4, GRID_VAL val5,
           GRID_VAL val6, GRID_VAL val7,
           GRID_VAL val8) {
	gridVal_[0] = val0;
	gridVal_[1] = val1;
	gridVal_[2] = val2;
	gridVal_[3] = val3;
	gridVal_[4] = val4;
	gridVal_[5] = val5;
	gridVal_[6] = val6;
	gridVal_[7] = val7;
	gridVal_[8] = val8;
}

bool Grid::MakeStep(int index,
                    GRID_VAL value) {
	if (index < 0 || index > 8) {
		std::cerr << __FUNCTION__
		          << "(): Wrong index!\n";
		return false;
	}

	if (gridVal_[index] != GRID_EMPTY) {
		std::cerr << __FUNCTION__
		          << "(): Grid value already set!\n";
		return false;
	}

	gridVal_[index] = value;
	return true;
}

void Grid::Print(void) const {
	int index = 0;
	for (GRID_VAL v: gridVal_) {
		std::cout << GRID_STR[v] << " ";
		index++;
		if (index == 3) {
			index = 0;
			std::cout << std::endl;
		}
	}
}

Grid Grid::RotateRigth(void) const {
	Grid retGrid(
	    gridVal_[6], gridVal_[3], gridVal_[0],
	    gridVal_[7], gridVal_[4], gridVal_[1],
	    gridVal_[8], gridVal_[5], gridVal_[2]);
	return retGrid;
}

bool Grid::operator==(const Grid& val) const {
	return val.gridVal_ == gridVal_;
}

int Grid::operator[](int index) const {
	if (index < 0 || index > 8) {
		std::cerr << __FUNCTION__
		          << "(): Try get invalid grid element\n";
		return -1;
	}
	return gridVal_[index];
}

std::vector<int> Grid::GetIndexesEmptyElements(void) const {
	std::vector<int> retVector;
	for (int i = 0; i < 9; i++) {
		if (gridVal_[i] == GRID_EMPTY) {
			retVector.push_back(i);
		}
	}
	return retVector;
}

bool Grid::SaveToFile(std::string fileName) const {
	std::ofstream file;
	file.open(fileName, std::ios::app);
	if (!file.is_open()) {
		std::cerr << __FUNCTION__
		          << "(): Can't open file for save grid\n";
		return false;
	}
	for (GRID_VAL value: gridVal_) {
		file << value << " ";
	}
	file << std::endl;
	file.close();
	return true;
}

bool Grid::CompareGridsAllRotates(
    const Grid& grid1,
    const Grid& grid2) {
	// 0 rotate
	if (grid1 == grid2) {
		return true;
	}
	// 90 rotate
	Grid flipGrip = grid1.RotateRigth();
	if (grid2 == flipGrip) {
		return true;
	}
	// 180 rotate
	flipGrip = flipGrip.RotateRigth();
	if (grid2 == flipGrip) {
		return true;
	}
	// 270 rotate
	flipGrip = flipGrip.RotateRigth();
	if (grid2 == flipGrip) {
		return true;
	}
	return false;
}
