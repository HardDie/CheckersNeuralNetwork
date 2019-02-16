#pragma once

#include "type_array.h"
#include <map>

class Pool {
 public:
	Pool(void);
	Pool(const std::vector<int> &pool);
	~Pool(void);

	bool AddStep(int value, int weight = 1);
	bool WasGoodStep(void);
	bool WasBadStep(void);
	int GetStep(int degree = 0);

	void Print(void) const;

	bool SaveToBinFile(std::ofstream& file) const;
	bool LoadFromBinFile(std::ifstream& file);
 private:

	ArrayType stepsMap_;
	int returnedValue_;
};
