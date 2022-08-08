#pragma once
#include <vector>
#include <iostream>
#include "Cube.hpp"

using namespace std;


class CubesStorage {
private:
	vector<Cube> cubes;

public:
	CubesStorage() {};
	CubesStorage(vector<Cube> cubes);
	CubesStorage(const CubesStorage* other, const Cube* cube);
	Cube get_cube(int pos);
	vector<Cube> get_cubes() const;
	bool is_valid(const Cube& next);
	friend ostream& operator<<(std::ostream& out, const CubesStorage& obj);
}; 