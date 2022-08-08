#include "CubesStorage.hpp"

CubesStorage::CubesStorage(vector<Cube> cubes) {
	for (int i = 0; i < cubes.size(); i++) {
		this->cubes.push_back(cubes[i]);
	}
}

CubesStorage::CubesStorage(const CubesStorage* other, const Cube* cube) {
	if (other == nullptr) {
		this->cubes.push_back(*cube);
	}
	else if (cube == nullptr) {
		cout << "No cube to add.\n";
	}
	else {
		int size = other->cubes.size();
		for (int i = 0; i < size; i++) {
			this->cubes.push_back(other->cubes[i]);
		}
		this->cubes.push_back(*cube);
	}
}

Cube CubesStorage::get_cube(int pos) {
	if (pos < cubes.size()) {
		return cubes[pos];
	}
	return Cube();
}

bool CubesStorage::is_valid(const Cube& next) {
	
	int size = this->cubes.size();
	bool is_valid = true;
	for (int i = 0; i < size; i++) {
		is_valid = true;
		if (cubes[i].get_left() != next.get_left() && cubes[i].get_right() != next.get_right()
			&& cubes[i].get_back() != next.get_back() && cubes[i].get_front() != next.get_front()) {
			is_valid = true;
		}
		else {
			is_valid = false;
			break;
		}
	
	}
	if (is_valid) {
		return true;
	}
	return false;
}


vector<Cube> CubesStorage::get_cubes() const {
	return this->cubes;
}


ostream& operator<<(std::ostream& out, const CubesStorage& obj) {
	for (auto c : obj.cubes) {
		out << c.enumToStr(c.get_front()) << " " << c.enumToStr(c.get_back()) << " ";
		out << c.enumToStr(c.get_left()) << " " << c.enumToStr(c.get_right()) << " ";
		out << c.enumToStr(c.get_top()) << " " << c.enumToStr(c.get_bottom()) << endl;
	}
	return out;
}


