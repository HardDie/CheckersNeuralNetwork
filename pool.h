#pragma once

#include <vector>

class Pool {
 public:
	Pool(void);
	Pool(const std::string& string);
	Pool(const std::vector<int> &pool);
	~Pool(void);

	bool AddStep(int value);
	bool WasGoodStep(void);
	bool WasBadStep(void);
	void Sort(void);
	int GetStep(void);

	void Print(void) const;
	bool SaveToFile(std::string fileName) const;
 private:
	std::vector<int> stepsPool_;
	int returnedValue_;
};
