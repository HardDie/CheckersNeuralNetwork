#include <iostream>
#include <algorithm>
#include <random>
#include "pool.h"

static std::random_device random_device;
static std::mt19937 engine(random_device());

Pool::Pool() :
	returnedValue_(-1)
{
}

Pool::Pool(const std::vector<int> &pool) :
	returnedValue_(-1),
	stepsPool_(pool)
{
}

Pool::~Pool() {
	if (returnedValue_ != -1) {
		std::cerr << __FUNCTION__
		          << "(): Remove pool without save progress!\n";
	}
}

bool Pool::AddStep(int value) {
	if (value < 0 || value > 8) {
		std::cerr << __FUNCTION__
		          << "(): Invalid step!\n";
		return false;
	}

	stepsPool_.push_back(value);
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

void Pool::Sort(void) {
	std::sort(stepsPool_.begin(), stepsPool_.end());
}

int Pool::GetStep(void) {
	std::uniform_int_distribution<int> dist(0, stepsPool_.size() - 1);
	int randValue = dist(engine);
	returnedValue_ = stepsPool_[randValue];
	return returnedValue_;
}

void Pool::Print(void) const {
	size_t len = stepsPool_.size();
	for (size_t i = 0; i < len; i++) {
		std::cout << stepsPool_[i] << " ";
	}
	std::cout << "last(" << returnedValue_ << ")" << std::endl;
}
