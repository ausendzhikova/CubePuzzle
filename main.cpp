#include <iostream>
#include <queue>
#include <stdexcept>
#include "CubesStorage.hpp"
#include <assert.h>

using namespace std;

bool uniq_helper(const Cube& a, const Cube& b) {
	if (a.get_front() == b.get_front() && a.get_back() == b.get_back() && a.get_left() == b.get_left() && a.get_right() == b.get_right()) {
		return false;
	}

	// When we want to take only unique solutions---- > we don't care about cube's orientation - which side is front, back, left and right

	/*if (a.get_front() == b.get_front() && a.get_back() == b.get_back() && a.get_left() == b.get_right() && a.get_right() == b.get_right()) {
		return false;
	}
	if (a.get_front() == b.get_back() && a.get_back() == b.get_front() && a.get_left() == b.get_left() && a.get_right() == b.get_right()) {
		return false;
	}
	if (a.get_front() == b.get_back() && a.get_back() == b.get_front() && a.get_left() == b.get_right() && a.get_right() == b.get_left()) {
		return false;
	}
	if (a.get_front() == b.get_left() && a.get_back() == b.get_right() && a.get_left() == b.get_back() && a.get_right() == b.get_front()) {
		return false;
	}
	if (a.get_front() == b.get_right() && a.get_back() == b.get_left() && a.get_left() == b.get_back() && a.get_right() == b.get_front()) {
		return false;
	}
	if (a.get_front() == b.get_right() && a.get_back() == b.get_left() && a.get_left() == b.get_front() && a.get_right() == b.get_back()) {
		return false;
	}
	if (a.get_front() == b.get_left() && a.get_back() == b.get_right() && a.get_left() == b.get_front() && a.get_right() == b.get_back()) {
		return false;
	}*/
	return true;
}


bool is_uniq(vector<CubesStorage>& solutions, CubesStorage new_sol) {
	int size = solutions.size();
	if (size == 0) {
		return true;
	}

	for (int i = 0; i < size; i++) {
		bool is_uniq = false;
		for (int j = 0; j < 4; j++) {
			Cube cur = solutions[i].get_cube(j);
			Cube sol = new_sol.get_cube(j);
			if(!uniq_helper(sol,cur)){
				is_uniq = false;
			}
			else {
				is_uniq = true;
				break;
			}

		}
		if (!is_uniq) {
			return false;
		}
	}
	return true;
}

void add_solution(queue<CubesStorage>& q,vector<CubesStorage>& solutions, CubesStorage& current,const Cube& new_sol) {
	CubesStorage current2 = CubesStorage(&current, &new_sol);
	if (current2.get_cubes().size() == 4) {
		if (is_uniq(solutions, current2)) {
			solutions.push_back(current2);
		}
	}
	else {
		q.push(current2);
	}
}

vector<CubesStorage> bfs(vector<Cube> cubes) {
	int solutions_count = 0;
	queue<CubesStorage> q;
	vector<CubesStorage> solutions;

	for (int i = 0; i < cubes.size(); i++) {
		cubes[i].reset();
	}
	while (cubes[0].hasNext()) {
		cubes[0].next();
		Cube cube = cubes[0].copy();
		CubesStorage temp = CubesStorage(nullptr, &cube);
		q.push(temp);
		//If want to check variants with reverse left and right side or variants with reverse front and back side, otherwise the next 3 lines are unnecessary
		Cube reverse_cube = cubes[0].reverse();
		temp = CubesStorage(nullptr, &reverse_cube);
		q.push(temp);
	}

	cubes[0].reset();

	while (!q.empty()) {
		CubesStorage current = q.front();
		q.pop();
		Cube next_cube = cubes[current.get_cubes().size()];
		while (next_cube.hasNext()) {
			next_cube.next();

			/*if (!current.is_valid(next_cube)) {
				Cube reverse_cube = next_cube.reverse();
				next_cube = reverse_cube;
			}*/

			Cube reverse_cube = next_cube.reverse();

			if (current.is_valid(next_cube)) {
				solutions_count++;
				add_solution(q, solutions, current, next_cube);
			}

			if (current.is_valid(reverse_cube)) {
				solutions_count++;
				add_solution(q, solutions, current, reverse_cube);
			}

		}
		cubes[current.get_cubes().size()].reset();
	}

	return solutions;
}


Color strToEnum(char c) {

	switch (c) {
	case 'R':
		return Color(R);
	case 'B':
		return Color(B);
	case 'G':
		return Color(G);
	case 'Y':
		return Color(Y);
	default:
		throw invalid_argument("Unknown color\n");
	}
}



//test function
bool function1(const string& str) {
	if (str.length() != 7) {
		throw invalid_argument("Wrong number of color for this cube\n");
	}
	return true;
}

bool function2(const string& str) {
	if (str.length() != 6) {
		throw invalid_argument("Wrong number of color for this cube\n");
	}
	return true;
}

bool function3(int size) {
	if (size != 4) {
		throw size;
	}
	return true;
}

//input                      old output ---------> new ouput
//BGRYBB,BYRGBR,YBYRGG,GBRGYR -----> 8    --------> 8
//RBGYBY,RGGYBB,YBRGYR,YGBRRR -----> 8    --------> 8
//BBBBBB,RRRRRR,YYYYYY,GGGGGG -----> 1    --------> 1
//BGYRBG,BGYRBG,BGYRBG,BGYRBG -----> 72   --------> 96
//YGYBGR,BRRYYG,RBYGRB,YGGGBR -----> 48   --------> 48
//BBYYGG,BBRRYY,BBRRGG,RRYYGG -----> 24   --------> 24
//BBBBYY,RRRRYY,GGGGYY,YYYYYY -----> 1    --------> 1
//BBBBYY,RRRRYY,GGGGBB,YYYYBB -----> 3    --------> 3
//BBRRGG,YYBBYY,GGRRBB,YYGGRR -----> 12   --------> 12
//BBBBBB,YYYBBB,GGGBBB,RRRBBB -----> 0    --------> 0
//RGBYRR,YRYBGG,RYBGRB,GRBGYR -----> 14   --------> 16
//BBGRYR,GBYYYR,YGGRBB,GBYRGR -----> 0    --------> 0
//BBGGRR,BBGGRR,BBYYRR,BBYYRR -----> 16   --------> 16
//BGRYBY,BGRYBY,BGRYBY,BGRYBY -----> 48   --------> 96
//BRGBRG,BRGBRG,BRYBRY,BRYBRY -----> 32   --------> 48
//RRBYGB,YYYBRY,RRBGBY,BGGRGY -----> 37   --------> 48
//BBYYGR,BBYYGR,BBYYGR,BBYYGR -----> 74   --------> 96
//BBBYYY,RRRYYY,GGGYYY,YYYBBB -----> 0    --------> 0
//BBBYYY,RRRGGG,BBBRRR,YYYGGG -----> 10   --------> 10

void function4(vector<Cube> cubes, vector<CubesStorage> q) {
	if (cubes[0].get_original() == vector<Color>{B, G, R, Y, B, B}&& cubes[1].get_original() == vector<Color>{B, Y, R, G, B, R}&&
		cubes[2].get_original() == vector<Color>{Y, B, Y, R, G, G}&& cubes[3].get_original() == vector<Color>{G, B, R, G, Y, R}) {
		assert(q.size() == 8);
	}

	if (cubes[0].get_original() == vector<Color>{R, B, G, Y, B, Y}&& cubes[1].get_original() == vector<Color>{R, G, G, Y, B, B}&&
		cubes[2].get_original() == vector<Color>{Y, B, R, G, Y, R}&& cubes[3].get_original() == vector<Color>{Y, G, B, R, R, R}) {
		assert(q.size() == 8);
	}

	if (cubes[0].get_original() == vector<Color>{B, B, B, B, B, B}&& cubes[1].get_original() == vector<Color>{R, R, R, R, R, R}&&
		cubes[2].get_original() == vector<Color>{Y, Y, Y, Y, Y, Y}&& cubes[3].get_original() == vector<Color>{G, G, G, G, G, G}) {
		assert(q.size() == 1);
	}

}

int main() {
	vector<Cube> cubes;

	for (int i = 0; i < 4; i++) {
		char c = ' ';
		string colors = "";
		while (c != ',' && i != 3) {
			cin >> c;
			colors += c;

		}

		if (i == 3) {
			cin >> colors;
			try {
				function2(colors);
			}
			catch (const invalid_argument& e) {
				printf("Wrong number of colors for cube %d\n", i + 1);
				break;
			}
		}
		else {
			try {
				function1(colors);
			}
			catch (const invalid_argument& e) {
				printf("Wrong number of colors for cube %d\n", i + 1);
				break;
			}
		}

		try {
			Cube cube = Cube(strToEnum(colors[0]), strToEnum(colors[1]), strToEnum(colors[2]), strToEnum(colors[3]), strToEnum(colors[4]), strToEnum(colors[5]));
			cubes.push_back(cube);
		}
		catch (const invalid_argument& e) {
			printf("Color of %d cube is unknown\n", i + 1);
			break;
		}
	}

	//SOLVE PUZZLE AND PRINT SOLUTIONS
	vector<CubesStorage> solutions = bfs(cubes);

	auto solutions_count = solutions.size();

	cout << solutions_count << endl;

	for (auto sol : solutions) {
		cout << sol << "\n";

	}
	return 0;
}