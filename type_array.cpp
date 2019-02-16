#include "type_array.h"

#include <iostream>
#include <fstream>

ArrayType::ArrayType(void) :
	arr_({0})
{
}

int ArrayType::operator[](int index) const {
	if (index < 0 || index > 8) {
		std::cerr << __FUNCTION__
		          << "(): Try get invalid array element\n";
		exit(-1);
	}

	return arr_[index];
}

int& ArrayType::operator[](int index) {
	if (index < 0 || index > 8) {
		std::cerr << __FUNCTION__
		          << "(): Try get invalid array element\n";
		exit(-1);
	}

	return arr_[index];
}

bool ArrayType::operator==(const ArrayType &arr) const {
	return arr_ == arr.arr_;
}

bool ArrayType::SaveToBinFile(std::ofstream& file) const {
	for (int i = 0; i < 9; i++) {
		file.write((char *)&arr_[i], sizeof(arr_[i]));
	}
	return true;
}

bool ArrayType::LoadFromBinFile(std::ifstream& file) {
	for (int i = 0; i < 9; i++) {
		file.read((char *)&arr_[i], sizeof(arr_[i]));
	}
	return true;
}
