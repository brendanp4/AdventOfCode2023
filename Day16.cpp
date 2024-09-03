#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include<set>

std::map<std::vector<int>, std::set<std::pair<int, int>> > totals;

bool comp(const std::pair<int, int> A, const std::pair<int, int> B) {
	if (A.first == B.first) {
		return A.second < B.second;
	}
	return A.first < B.first;
}

int GetEnergy(std::vector<std::string> grid, std::vector<int> start) {
	std::set<std::pair<int, int>> energy;
	std::vector<std::vector<int>> beams = { start };
	int total = 0;

	bool going = true;
	bool repeat = true;
	std::map<std::vector<int>, int> map;
	while (going && repeat) {
		going = false;
		repeat = false;
		int length = beams.size();
		for (int i = 0; i < length; i++) {
			std::vector<int> beam = beams[i];
			if (beam[0] < 0 || beam[0] >= grid.size() || beam[1] < 0 || beam[1] >= grid[0].size()) {
				continue;
			}

			if (totals.count(beam)) {
				std::cout << "Repeat ;)\n\n";
				std::set<std::pair<int, int>> tEnergy;
				std::set<std::pair<int, int>> tBeam = totals[beam];
				std::set_union(energy.begin(), energy.end(), tBeam.begin(), tBeam.end(), std::inserter(tEnergy, tEnergy.begin()));
			}

			going = true;
			if (!map.count(beam)) {
				map[beam]++;
				repeat = true;
			}
			energy.emplace(beam[0], beam[1]);
			switch (grid[beam[0]][beam[1]])
			{
			case '.':
				beam[0] += beam[2];
				beam[1] += beam[3];
				break;
			case '-':
				if (beam[3] == 0) {
					std::vector<int> temp = { beam[0], beam[1] - 1, 0, -1 };
					beams.push_back(temp);
					beam[1] += 1;
					beam[2] = 0;
					beam[3] = 1;
				}
				else {
					beam[0] += beam[2];
					beam[1] += beam[3];
				}
				break;
			case '|':
				if (beam[2] == 0) {
					std::vector<int> temp = { beam[0] - 1, beam[1], -1, 0 };
					beams.push_back(temp);
					beam[0] += 1;
					beam[2] = 1;
					beam[3] = 0;
				}
				else {
					beam[0] += beam[2];
					beam[1] += beam[3];
				}
				break;
			case '/':
				beam[2] *= -1;
				beam[3] *= -1;
				std::swap(beam[2], beam[3]);
				beam[0] += beam[2];
				beam[1] += beam[3];
				break;
			case '\\':
				std::swap(beam[2], beam[3]);
				beam[0] += beam[2];
				beam[1] += beam[3];
				break;
			default:
				break;
			}
			beams[i] = beam;
		}
	}

	total = energy.size();
	totals[start] = energy;
	return total;
}

int main()
{

	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		int total = 0;
		std::string input;
		std::vector<std::string> grid;
		while (std::getline(iFile, input)) {
			grid.push_back(input);
		}

		//Part 1
		/*std::vector<std::string> energized = grid;
		std::vector<int> start = { 0,0,0,1 };
		std::vector<std::vector<int>> beams = { start };
		
		bool going = true;
		bool repeat = true;
		std::map<std::vector<int>, int> map;
		while (going && repeat) {
			going = false;
			repeat = false;
			int length = beams.size();
			for (int i = 0; i < length; i++) {
				std::vector<int> beam = beams[i];
				if (beam[0] < 0 || beam[0] >= grid.size() || beam[1] < 0 || beam[1] >= grid[0].size()) {
					continue;
				}
				going = true;
				if (!map.count(beam)) {
					map[beam]++;
					repeat = true;
				}
				energized[beam[0]][beam[1]] = '#';
				switch (grid[beam[0]][beam[1]])
				{
				case '.':
					beam[0] += beam[2];
					beam[1] += beam[3];
					break;
				case '-':
					if (beam[3] == 0) {
						std::vector<int> temp = { beam[0], beam[1] - 1, 0, -1 };
						beams.push_back(temp);
						beam[1] += 1;
						beam[2] = 0;
						beam[3] = 1;
					}
					else {
						beam[0] += beam[2];
						beam[1] += beam[3];
					}
					break;
				case '|':
					if (beam[2] == 0) {
						std::vector<int> temp = { beam[0] - 1, beam[1], -1, 0 };
						beams.push_back(temp);
						beam[0] += 1;
						beam[2] = 1;
						beam[3] = 0;
					}
					else {
						beam[0] += beam[2];
						beam[1] += beam[3];
					}
					break;
				case '/':
					beam[2] *= -1;
					beam[3] *= -1;
					std::swap(beam[2], beam[3]);
					beam[0] += beam[2];
					beam[1] += beam[3];
					break;
				case '\\':
					std::swap(beam[2], beam[3]);
					beam[0] += beam[2];
					beam[1] += beam[3];
					break;
				default:
					break;
				}
				beams[i] = beam;
			}
		}

		for (int i = 0; i < energized.size(); i++) {
			std::cout << energized[i] << std::endl;
			for (int j = 0; j < energized[i].size(); j++) {
				if (energized[i][j] == '#') {
					total++;
				}
			}
		}*/

		//Part 2
		int max = 0;
		for (int i = 0; i < grid[0].size(); i++) {
			std::cout << "Working on col " << i << std::endl;
			int temp = GetEnergy(grid, { 0,i,1,0 });
			if (temp > max) {
				max = temp;
			}
			temp = GetEnergy(grid, { int(grid.size() - 1),i,-1,0 });
			if (temp > max) {
				max = temp;
			}
		}
		for (int i = 0; i < grid.size(); i++) {
			std::cout << "Working on row " << i << std::endl;
			int temp = GetEnergy(grid, { i,0,0,1 });
			if (temp > max) {
				max = temp;
			}
			temp = GetEnergy(grid, { i,int(grid[0].size() - 1),0,-1});
			if (temp > max) {
				max = temp;
			}
		}

		std::cout << "\nTotal: " << max << std::endl;
	}
	return 0;
}
