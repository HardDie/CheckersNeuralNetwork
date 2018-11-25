#pragma once

#include <vector>

class Pool {
 public:
	Pool();
	Pool(const std::vector<int> &pool);
	~Pool();

	bool AddStep(int value);
	bool WasGoodStep(void);
	bool WasBadStep(void);
	void Sort(void);
	int GetStep(void);

	void Print(void) const;
 private:
	std::vector<int> stepsPool_;
	int returnedValue_;
};
