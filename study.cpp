#include <iostream>
#include <fstream>
#include "study.h"

CaseObject::CaseObject(const Pool& pool,
                       const Grid& grid) {
	pool_ = pool;
	grid_ = grid;
}

Study::Study() {
	LoadFromFile("brain.bin");
}

void Study::WinParty(void) {
	for (auto el: vActiveObjects_) {
		el->pool_.WasGoodStep();
		el->pool_.Sort();
	}
	vActiveObjects_.clear();
	SaveToFile("brain.bin");
}

void Study::LoseParty(void) {
	for (auto el: vActiveObjects_) {
		el->pool_.WasBadStep();
	}
	vActiveObjects_.clear();
}

int Study::GetStepForGrid(const Grid& grid) {
	int ret;
	int rotation;
	/* First of all try find grid in
	 * existense array of elements */
	for (int i = 0; i < vObjects_.size(); i++) {
		if (Grid::CompareGridsAllRotates(grid, vObjects_[i].grid_, rotation) ||
		    Grid::CompareGridsAllRotates(grid.Invert(), vObjects_[i].grid_,
		                                 rotation)) {
			std::cout << "Pool: \n";
			vObjects_[i].pool_.Print();
			std::cout << "For grid: \n";
			grid.Print();
			std::cout << std::endl;
			ret = vObjects_[i].pool_.GetStep(rotation);
			vActiveObjects_.push_back(&vObjects_[i]);
			return ret;
		}
	}
	std::cout << "Not find grid, create new:" << std::endl;
	grid.Print();
	std::cout << std::endl;
	/* If not find exist grid
	 * create new pair grid and pool */
	Pool newPool(grid.GetIndexesEmptyElements());
	ret = newPool.GetStep();
	CaseObject newObject(newPool, grid);
	vObjects_.push_back(newObject); // Inside create clones some objects
	vActiveObjects_.push_back(&vObjects_.back());

	// Clean objects before delete
	newPool.WasBadStep();
	newObject.pool_.WasBadStep();
	return ret;
}

void Study::Print(void) const {
	for (int i = 0; i < vObjects_.size(); i++) {
		std::cout << "Index: " << i << std::endl;
		std::cout << "Grid:" << std::endl;
		vObjects_[i].grid_.Print();
		std::cout << "Pool: ";
		vObjects_[i].pool_.Print();
		std::cout << std::endl;
	}
}

bool Study::SaveToFile(std::string fileName) const {
	// Before clean file
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open()) {
		std::cerr << __FUNCTION__
		          << "(): Can't open file for save Study data!\n";
		return false;
	}
	file.close();

	// After save all objects
	for (const CaseObject &obj: vObjects_) {
		obj.pool_.SaveToFile(fileName);
		obj.grid_.SaveToFile(fileName);
	}
	return true;
}

bool Study::LoadFromFile(std::string fileName) {
	std::ifstream file;
	std::string pool, grid;
	file.open("brain.bin");
	if (!file.is_open()) {
		std::cerr << __FUNCTION__
		          << "(): Can't open file for load Study data!\n";
		return false;
	}
	while (getline(file, pool) &&
	       getline(file, grid)) {
		Pool newPool(pool);
		Grid newGrid(grid);

		vObjects_.push_back(CaseObject(newPool, newGrid));
	}

	file.close();
	return true;
}
