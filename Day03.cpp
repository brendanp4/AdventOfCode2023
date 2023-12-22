#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


int main() {
	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::vector<std::vector<char>> engine;
		std::string input;
		while (std::getline(iFile, input)) {
			std::vector<char> temp;
			for (auto c : input) {
				temp.push_back(c);
			}
			engine.push_back(temp);

			
		}

		int sum = 0;

		std::map<std::pair<int, int>, std::vector<int>> gears;

		for (int i = 0; i < engine.size(); i++) {
			int temp = 0;
			bool part = false;
			std::map<std::pair<int, int>,int> temp_gears;
			for (int j = 0; j < engine[0].size(); j++) {
				if (isdigit(engine[i][j])) {
					temp *= 10;
					temp += engine[i][j] - 48;
					//Check if it's adjacent to any symbol
					if ((i - 1) >= 0) {
						if ((j - 1) >= 0) {
							if (!isdigit(engine[i - 1][j - 1]) && engine[i - 1][j - 1] == '*') {
								//adjacent symbol found
								part = true;
								std::pair<int, int> temp(i - 1, j - 1);
								temp_gears[temp]++;
							}
						}
						if (!isdigit(engine[i - 1][j]) && engine[i - 1][j] == '*') {
							//adjacent symbol found
							part = true;
							std::pair<int, int> temp(i - 1, j);
							temp_gears[temp]++;
						}
						if ((j + 1) < engine[0].size()) {
							if (!isdigit(engine[i - 1][j + 1]) && engine[i - 1][j + 1] == '*') {
								//adjacent symbol found
								part = true;
								std::pair<int, int> temp(i - 1, j + 1);
								temp_gears[temp]++;
							}
						}
					}
					if ((j - 1) >= 0) {
						if (!isdigit(engine[i][j - 1]) && engine[i][j - 1] == '*') {
							//adjacent symbol found
							part = true;
							std::pair<int, int> temp(i, j - 1);
							temp_gears[temp]++;
						}
					}
					if ((j + 1) < engine[0].size()) {
						if (!isdigit(engine[i][j + 1]) && engine[i][j + 1] == '*') {
							//adjacent symbol found
							part = true;
							std::pair<int, int> temp(i, j + 1);
							temp_gears[temp]++;
						}
					}
					if ((i + 1) < engine.size()) {
						if ((j - 1) >= 0) {
							if (!isdigit(engine[i + 1][j - 1]) && engine[i + 1][j - 1] == '*') {
								//adjacent symbol found
								part = true;
								std::pair<int, int> temp(i + 1, j - 1);
								temp_gears[temp]++;
							}
						}
						if (!isdigit(engine[i + 1][j]) && engine[i + 1][j] == '*') {
							//adjacent symbol found
							part = true;
							std::pair<int, int> temp(i + 1, j);
							temp_gears[temp]++;
						}
						if ((j + 1) < engine[0].size()) {
							if (!isdigit(engine[i + 1][j + 1]) && engine[i + 1][j + 1] == '*') {
								//adjacent symbol found
								part = true;
								std::pair<int, int> temp(i + 1, j + 1);
								temp_gears[temp]++;
							}
						}
					}
				}
				if(!isdigit(engine[i][j]) || j == engine[0].size() - 1) {
					//if (part) {
					//	sum += temp;
					//}
					if (temp) {
						for (auto const& p : temp_gears) {
							gears[p.first].push_back(temp);
						}
					}
					temp_gears.clear();
					temp = 0;
					part = false;
				}
			}
		}


		for (auto const& x : gears)
		{
			int gear_ratio = 0;
			if (x.second.size() == 2) {
				gear_ratio = x.second[0] * x.second[1];
			}
			sum += gear_ratio;
		}
		
		std::cout << "Sum of gear ratios: " << sum << std::endl;
	}

	return 0;
}
