#include <iostream>
#include <fstream>
#include "study.h"

CaseObject::CaseObject(const Pool& pool,
                       const Grid& grid) {
	pool_ = pool;
	grid_ = grid;
}

Study::Study() {
	game_count = 0;
	LoadFromFile("brain.bin");
	vObjects_.reserve(20);
}

void Study::WinParty(void) {
	for (auto el: vActiveObjects_) {
		el->pool_.WasGoodStep();
	}
	vActiveObjects_.clear();
	game_count++;
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
	for (size_t i = 0; i < vObjects_.size(); i++) {
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
	CaseObject newObject(newPool, grid);
	vObjects_.push_back(newObject); // Inside create clones some objects
	vActiveObjects_.push_back(&vObjects_.back());
	ret = vActiveObjects_.back()->pool_.GetStep();

	return ret;
}

void Study::Print(void) const {
	for (size_t i = 0; i < vObjects_.size(); i++) {
		std::cout << "Index: " << i << std::endl;
		std::cout << "Grid:" << std::endl;
		vObjects_[i].grid_.Print();
		std::cout << "Pool: ";
		vObjects_[i].pool_.Print();
		std::cout << std::endl;
	}
}

bool Study::SaveToFile(std::string fileName) const {
	// Open and clean file
	std::ofstream file(fileName, std::ios::binary | std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << __FUNCTION__
		          << "(): Can't open file for save Study data!\n";
		return false;
	}

	// Write played game counter
	file.write((char*)&game_count, sizeof(game_count));
	// Write size to file
	std::size_t len = vObjects_.size();
	file.write((char*)&len, sizeof(len));

	// Save all objects to file
	for (const CaseObject &obj: vObjects_) {
		obj.pool_.SaveToBinFile(file);
		obj.grid_.SaveToBinFile(file);
	}
	file.close();
	return true;
}

bool Study::LoadFromFile(std::string fileName) {
	std::ifstream file(fileName, std::ios::binary);
	std::size_t len;

	if (!file.is_open()) {
		std::cerr << __FUNCTION__
		          << "(): Can't open file for load Study data!\n";
		return false;
	}

	file.read((char*)&game_count, sizeof(game_count));
	file.read((char*)&len, sizeof(len));
	for (size_t i = 0; i < len; i++) {
		Pool newPool;
		Grid newGrid;
		newPool.LoadFromBinFile(file);
		newGrid.LoadFromBinFile(file);
		vObjects_.push_back(CaseObject(newPool, newGrid));
	}

	file.close();
	return true;
}
