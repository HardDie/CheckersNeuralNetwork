#pragma once

#include "type_array.h"
#include <vector>

enum GRID_VAL {
  GRID_EMPTY = 0,
  GRID_X,
  GRID_O,
};

class Grid {
 public:
	Grid(void);
	Grid(const std::string &string);
	Grid(GRID_VAL val0, GRID_VAL val1,
	     GRID_VAL val2, GRID_VAL val3,
	     GRID_VAL val4, GRID_VAL val5,
	     GRID_VAL val6, GRID_VAL val7,
	     GRID_VAL val8);
	~Grid(void) {}

	bool MakeStep(int index,
	              GRID_VAL value);

	void Print(void) const;
	Grid RotateRigth(void) const;
	Grid Invert(void) const;
	bool operator==(const Grid& val) const;
	int operator[](int index) const;
	std::vector<int> GetIndexesEmptyElements(void) const;

	bool SaveToBinFile(std::ofstream& file) const;
	bool LoadFromBinFile(std::ifstream& file);

	static bool CompareGridsAllRotates(const Grid& grid1,
	                                   const Grid& grid2,
	                                   int& rotation);
 private:
	ArrayType gridVal_;
};
