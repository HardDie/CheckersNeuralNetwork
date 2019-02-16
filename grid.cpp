#include <iostream>
#include "grid.h"

static const char GRID_STR[3] = { '-', 'X', 'O' };

Grid::Grid(void) {
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
	for (int i = 0; i < 9; i++) {
		std::cout << GRID_STR[gridVal_[i]] << " ";
		index++;
		if (index == 3) {
			index = 0;
			std::cout << std::endl;
		}
	}
}

Grid Grid::RotateRigth(void) const {
	Grid retGrid(
	    (GRID_VAL)gridVal_[6], (GRID_VAL)gridVal_[3], (GRID_VAL)gridVal_[0],
	    (GRID_VAL)gridVal_[7], (GRID_VAL)gridVal_[4], (GRID_VAL)gridVal_[1],
	    (GRID_VAL)gridVal_[8], (GRID_VAL)gridVal_[5], (GRID_VAL)gridVal_[2]);
	return retGrid;
}

Grid Grid::Invert(void) const {
	Grid retGrid;
	for (int i = 0; i < 9; i++) {
		if (gridVal_[i] == GRID_X) {
			retGrid.MakeStep(i, GRID_O);
		} else if (gridVal_[i] == GRID_O) {
			retGrid.MakeStep(i, GRID_X);
		}
	}
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

bool Grid::SaveToBinFile(std::ofstream& file) const {
	return gridVal_.SaveToBinFile(file);
}

/**
 * На вход подается открытый файл на моменте начала Grid данных
 * от этого момента вычитывается H*W символов, зависит от размера
 * поля, и смещенный дескриптор возвращается назад
 */
bool Grid::LoadFromBinFile(std::ifstream& file) {
	return gridVal_.LoadFromBinFile(file);
}

bool Grid::CompareGridsAllRotates(
    const Grid& grid1,
    const Grid& grid2,
    int& rotation) {
	// 0 rotate
	if (grid1 == grid2) {
		rotation = 0;
		return true;
	}
	// 90 rotate
	Grid flipGrip = grid1.RotateRigth();
	if (grid2 == flipGrip) {
		rotation = 90;
		return true;
	}
	// 180 rotate
	flipGrip = flipGrip.RotateRigth();
	if (grid2 == flipGrip) {
		rotation = 180;
		return true;
	}
	// 270 rotate
	flipGrip = flipGrip.RotateRigth();
	if (grid2 == flipGrip) {
		rotation = 270;
		return true;
	}
	return false;
}
