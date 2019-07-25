#pragma once
#include <vector>
#include "pool.h"
#include "grid.h"

class CaseObject {
 public:
	CaseObject() {}
	CaseObject(const Pool& pool, const Grid& grid);
	~CaseObject() {}

	Pool pool_;
	Grid grid_;
};

class Study {
 public:
	Study();
	~Study() {}

	void WinParty(void);
	void LoseParty(void);
	int GetStepForGrid(const Grid& grid);

	void Print(void) const;
	int game_count;
 private:
	std::vector<CaseObject> vObjects_;
	/**
	 * Store list last used objects
	 * then fast clean and make decision
	 */
	std::vector<CaseObject*> vActiveObjects_;

	bool SaveToFile(std::string fileName) const;
	bool LoadFromFile(std::string fileName);
};
