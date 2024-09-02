#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main()
{

	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::string input;
		long long total = 0;
		std::vector<std::string> grid;
		while (std::getline(iFile, input)) {
			grid.push_back(input);
		}

		//Part 1
		/*int cols = grid[0].size();
		int rows = grid.size();
		std::vector<int> weights(cols, rows);

		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				if (grid[row][col] == '#') {
					weights[col] = rows - (row + 1);
				}
				else if (grid[row][col] == 'O') {
					total += weights[col];
					weights[col]--;
				}
			}
		}*/


		int cols = grid[0].size();
		int rows = grid.size();
		std::vector<int> weights;
		std::map<std::vector<std::string>, int> table;
		int des = 999999999;

		for (int i = 0; i < des; i++) {
			//Tilt north
			weights.clear();
			weights.resize(cols, rows);
			for (int row = 0; row < rows; row++) {
				for (int col = 0; col < cols; col++) {
					if (grid[row][col] == '#') {
						weights[col] = rows - (row + 1);
					}
					else if (grid[row][col] == 'O') {
						grid[row][col] = '.';
						grid[rows - weights[col]][col] = 'O';
						weights[col]--;
					}
				}
			}

			//Tilt west
			weights.clear();
			weights.resize(rows, cols);
			for (int col = 0; col < cols; col++)
			{
				for (int row = 0; row < rows; row++)
				{
					if (grid[row][col] == '#') {
						weights[row] = cols - (col + 1);
					}
					else if (grid[row][col] == 'O') {
						grid[row][col] = '.';
						grid[row][cols - weights[row]] = 'O';
						weights[row]--;
					}
				}
			}

			//Tilt south
			weights.clear();
			weights.resize(cols, 1);
			for (int row = rows - 1; row >= 0; row--) {
				for (int col = 0; col < cols; col++) {
					if (grid[row][col] == '#') {
						weights[col] = (rows - (row)) + 1;
					}
					else if (grid[row][col] == 'O') {
						grid[row][col] = '.';
						grid[rows - weights[col]][col] = 'O';
						weights[col]++;
					}
				}
			}

			//Tilt east
			weights.clear();
			weights.resize(rows, 1);
			for (int col = cols - 1; col >= 0; col--)
			{
				for (int row = 0; row < rows; row++)
				{
					if (grid[row][col] == '#') {
						weights[row] = (cols - col) + 1;
					}
					else if (grid[row][col] == 'O') {
						grid[row][col] = '.';
						grid[row][cols - weights[row]] = 'O';
						weights[row]++;
					}
				}
			}

			if (table.count(grid)) {
				std::cout << "Cycle found\n";
				int length = i - table[grid];
				std::cout << "\tCurrent iteration: " << i << std::endl;
				std::cout << "\tCycle length: " << length << std::endl;
				std::cout << "\tCycle start: " << table[grid] << std::endl << std::endl;
				if ((des - i) % length == 0) {
					break;
				}
			}
			else {
				table[grid] = i;
			}
		}

		//check load
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				if (grid[row][col] == 'O') {
					total += (rows - row);
				}
			}
		}

		std::cout << "\nTotal: " << total << std::endl;
	}
	return 0;
}
