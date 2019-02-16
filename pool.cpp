#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "pool.h"

/********************
 *     Static
 ********************/

static std::random_device random_device;
static std::mt19937 engine(random_device());

static int rotateValue90Degree(int value) {
	switch(value) {
	case 0: return 6;
	case 1: return 3;
	case 2: return 0;
	case 3: return 7;
	case 4: return 4;
	case 5: return 1;
	case 6: return 8;
	case 7: return 5;
	case 8: return 2;
	default:
		std::cerr << __FUNCTION__
		          << "(): Wrong value for rotation!\n";
		exit(-1);
	}
}

static int rotateValue180Degree(int value) {
	switch(value) {
	case 0: return 8;
	case 1: return 7;
	case 2: return 6;
	case 3: return 5;
	case 4: return 4;
	case 5: return 3;
	case 6: return 2;
	case 7: return 1;
	case 8: return 0;
	default:
		std::cerr << __FUNCTION__
		          << "(): Wrong value for rotation!\n";
		exit(-1);
	}
}

static int rotateValue270Degree(int value) {
	switch(value) {
	case 0: return 2;
	case 1: return 5;
	case 2: return 8;
	case 3: return 1;
	case 4: return 4;
	case 5: return 7;
	case 6: return 0;
	case 7: return 3;
	case 8: return 6;
	default:
		std::cerr << __FUNCTION__
		          << "(): Wrong value for rotation!\n";
		exit(-1);
	}
}

/********************
 *     Public
 ********************/

Pool::Pool(void) :
	returnedValue_(-1),
	stepsMap_({0})
{
}

Pool::Pool(const std::vector<int> &pool) :
	returnedValue_(-1),
	stepsMap_({0})
{
}

Pool::~Pool(void) {
	if (returnedValue_ != -1) {
		std::cerr << __FUNCTION__
		          << "(): Remove pool without save progress!\n";
	}
}

bool Pool::AddStep(int value, int weight) {
	if (value < 0 || value > 8) {
		std::cerr << __FUNCTION__
		          << "(): Invalid step!\n";
		return false;
	}

	if (weight <= 0) {
		std::cerr << __FUNCTION__
		          << "(): Invalid weight!\n";
		return false;
	}

	stepsMap_[value] += weight;
	return true;
}

bool Pool::WasGoodStep(void) {
	if (returnedValue_ == -1) {
		std::cerr << __FUNCTION__
		          << "(): Try save empty value!\n";
		return false;
	}

	this->AddStep(returnedValue_);
	returnedValue_ = -1;
	return true;
}

bool Pool::WasBadStep(void) {
	if (returnedValue_ == -1) {
		std::cerr << __FUNCTION__
		          << "(): Try save empty value!\n";
		return false;
	}

	returnedValue_ = -1;
	return true;
}

int Pool::GetStep(int degree) {
	int countObjects = 0;
	for (int i = 0; i < 9; i++) {
		countObjects += stepsMap_[i];
	}

	if (!countObjects) {
		std::cerr << __FUNCTION__
		          << "(): No available steps in pool!\n";
		exit(-1);
	}

	std::uniform_int_distribution<int> dist(0, countObjects - 1);
	int randValue = dist(engine);

	int tmpRange = 0;
	for (int i = 0; i < 9; i++) {
		// Search value at correct range
		if (randValue >= tmpRange &&
		    randValue < tmpRange + stepsMap_[i]) {
			returnedValue_ = i;
			break;
		}
		tmpRange += stepsMap_[i];
	}

	switch(degree) {
	case 0: return returnedValue_;
	case 90: return rotateValue90Degree(returnedValue_);
	case 180: return rotateValue180Degree(returnedValue_);
	case 270: return rotateValue270Degree(returnedValue_);
	default:
		std::cerr << __FUNCTION__
		          << "(): Wrong degree!\n";
		exit(-1);
	}
}

void Pool::Print(void) const{
	for (int i = 0; i < 9; i++) {
		std::cout << i << "(" << stepsMap_[i] << ") ";
	}

	std::cout << "last(" << returnedValue_ << ")" << std::endl;
}

bool Pool::SaveToBinFile(std::ofstream& file) const {
	for (int i = 0; i < 9; i++) {
		int weight = GetMapValue(i);
		file.write((char*)&weight, sizeof(weight));
	}
	return true;
}

bool Pool::LoadFromBinFile(std::ifstream& file) {
	for (int i = 0; i < 9; i++) {
		int weight;
		file.read((char*)&weight, sizeof(weight));
		if (weight) {
			this->AddStep(i, weight);
		}
	}
	return true;
}

/********************
 *     Private
 ********************/

int Pool::GetMapValue(int index) const {
	try {
		return stepsMap_.at(index);
	} catch(...) {
		// If element not exist, just return 0;
		return 0;
	}
}
