#pragma once

#include <vector>
#include <map>

class Pool {
 public:
	Pool(void);
	Pool(const std::string& string);
	Pool(const std::vector<int> &pool);
	~Pool(void);

	bool AddStep(int value);
	bool WasGoodStep(void);
	bool WasBadStep(void);
	int GetStep(int degree = 0);

	void Print(void) const;
	bool SaveToFile(std::string fileName) const;

	bool SaveToBinFile(std::ofstream& file) const;
	bool LoadFromBinFile(std::ifstream& file);
 private:
	int GetMapValue(int index) const;

	std::vector<int> stepsPool_;
	std::map<int, int> stepsMap_;
	int returnedValue_;
};
