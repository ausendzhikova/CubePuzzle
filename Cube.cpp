#include "Cube.hpp"


Cube::Cube(Color front, Color back, Color left, Color right, Color top, Color bottom) {
	for (int i = 0; i < 6; i++) {
		original.push_back(Color());
	}
	this->front = original[0]=front;
	this->back = original[1]=back;
	this->left = original[2]=left;
	this->right = original[3]=right;
	this->top = original[4]=top;
	this->bottom = original[5]=bottom;
}

Cube::Cube(const Cube& other) {
	this->front = other.front;
	this->back = other.back;
	this->left = other.left;
	this->right = other.right;
	this->top = other.top;
	this->bottom = other.bottom;
	this->orientation_counter = other.orientation_counter;
	this->original = other.original;
}

Color Cube::get_front() const {
	return this->front;
}

Color Cube::get_back() const {
	return this->back;
}

Color Cube::get_left() const {
	return this->left;
}

Color Cube::get_right() const {
	return this->right;
}

Color Cube::get_top() const {
	return this->top;
}

Color Cube::get_bottom() const {
	return this->bottom;
}

vector<Color> Cube::get_original() const {
	return this->original;
}

Cube Cube::copy() {
	return Cube(*this);
}

bool Cube::hasNext() const {
	return orientation_counter < 12;
}

void Cube::next() {
	if (orientation_counter > 11) {
		//no more rotations ----> nothing to do
		return;
	}
	 if (orientation_counter % 4 != 0) {
		//Rotate - swap front,back,left,right side
		Color temp = front;
		front = left;
		left = back;
		back = right;
		right = temp;
	}
	else if (orientation_counter == 4 || orientation_counter == 8 ) {
		//orientation_counter == 4 ------> rotate cube so that we see top,bottom,left,right
		// orientation_counter==8 -------> front,back,top,bottom
		Color temp = top;
		top = left;
		left = bottom;
		bottom = right;
		right = temp;
	}
	else if (orientation_counter == 0) {
		//Original position
		reset();
	}
	orientation_counter++;
}


Cube Cube::reverse() {
	if (orientation_counter == 0 || orientation_counter % 2 == 0) {
		Cube temp = Cube(back, front, left, right, bottom, top);
		temp.orientation_counter = this->orientation_counter;
		return temp;
	} 
	Cube temp = Cube(front, back, right, left, bottom, top);
	temp.orientation_counter = this->orientation_counter;
	return temp;
}


  
void Cube::reset() {
	front = original[0];
	back = original[1];
	left = original[2];
	right = original[3];
	top = original[4];
	bottom = original[5];
	orientation_counter = 0;
}


char Cube::enumToStr(Color c) {
	switch (c) {
	case R:
		return 'R';
	case B:
		return 'B';
	case G:
		return 'G';
	case Y:
		return 'Y';
	}
}