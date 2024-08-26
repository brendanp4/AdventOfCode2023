#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int shortestPath(std::pair<int, int> beg, std::pair<int, int> end) {
	return abs(beg.first - end.first) + abs(beg.second - end.second);
}

int main()
{

	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::vector<std::string> grid;
		std::vector<std::pair<int, int>> galaxies;
		std::string input;
		int row = 0;
		while (std::getline(iFile, input)) {
			grid.push_back(input);
			int col = 0;
			for (auto c : input) {
				if (c == '#') {
					galaxies.push_back(std::pair<int, int>(row, col));
				}
				col++;
			}
			row++;
		}

		//Find empty rows
		std::vector<int> rows;
		for (int i = 0; i < grid.size(); i++) {
			bool found = false;
			for (auto g : galaxies) {
				if (g.first == i) {
					found = true;
				}
			}
			if (!found) {
				rows.push_back(i);
			}
		}
		//Find empty cols
		std::vector<int> cols;
		for (int i = 0; i < grid[0].size(); i++) {
			bool found = false;
			for (auto g : galaxies) {
				if (g.second == i) {
					found = true;
				}
			}
			if (!found) {
				cols.push_back(i);
			}
		}
		
		int factor = 1000000 - 1;
		for (int i = 0; i < rows.size(); i++) {
			for (auto& g : galaxies) {
				if (g.first > (rows[i] + (i * factor))) {
					g.first += factor;
				}
			}
		}
		for (int i = 0; i < cols.size(); i++) {
			for (auto& g : galaxies) {
				if (g.second > (cols[i] + (i * factor))) {
					g.second += factor;
				}
			}
		}

		long long sum = 0;
		for (int i = 0; i < galaxies.size(); i++) {
			for (int j = i + 1; j < galaxies.size(); j++) {
				if (i == 0 && j == 6) {
					int ayy = 1;
				}
				sum += long long(shortestPath(galaxies[i], galaxies[j]));
			}
		}

		std::cout << "Sum of all shortest paths: " << sum << std::endl;

	}
	return 0;
}
