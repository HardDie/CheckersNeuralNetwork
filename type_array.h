#pragma once
#include <array>

class ArrayType {
 public:
	ArrayType(void);
	~ArrayType(void) {}

	int operator[](int index) const;
	int& operator[](int index);
	bool operator==(const ArrayType &arr) const;

	bool SaveToBinFile(std::ofstream& file) const;
	bool LoadFromBinFile(std::ifstream& file);
 private:
	std::array<int, 9> arr_;
};
