#pragma once
#include <vector>
#include <string>
using namespace std;

enum Color {
	R, B, G, Y
};

class Cube {
private:
	Color front, back, left, right, top, bottom;

	vector<Color> original;

public:
	int orientation_counter = 0;
	Cube() {};
	Cube(Color front, Color back, Color left, Color right, Color top, Color bottom);
	Cube(const Cube& other);
	Color get_front() const;
	Color get_back() const;
	Color get_left() const;
	Color get_right() const;
	Color get_top() const;
	Color get_bottom() const;
	vector<Color> get_original() const;
	Cube copy();
	bool hasNext() const;
	void next();
	Cube  reverse();
	void reset();
	char enumToStr(Color c);

};