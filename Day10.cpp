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
		std::vector<std::string> grid;
		std::string input;
		std::pair<int, int> start;
		int row = 0;
		while (std::getline(iFile, input)) {
			grid.push_back(input);
			for (int i = 0; i < input.size(); i++)
			{
				if (input[i] == 'S') {
					start.first = row;
					start.second = i;
				}
			}
			row++;
		}

		//Get connections
		std::vector<std::pair<int, int>> connections;

		enum comp
		{
			Up,
			Down,
			Left,
			Right
		}dir;
		std::vector<comp> tds;

		//Check above
		if (start.first > 0) {
			char adj = grid[start.first - 1][start.second];
			if (adj == '|' || adj == 'F' || adj == '7') {
				connections.push_back(std::pair<int,int>(start.first - 1, start.second));
				dir = Up;
				tds.push_back(dir);
			}
		}
		//Check below
		if (start.first < grid.size() - 1) {
			char adj = grid[start.first + 1][start.second];
			if (adj == '|' || adj == 'L' || adj == 'J') {
				connections.push_back(std::pair<int, int>(start.first + 1, start.second));
				dir = Down;
				tds.push_back(dir);
			}
		}
		//Check left
		if (start.second > 0) {
			char adj = grid[start.first][start.second - 1];
			if (adj == '-' || adj == 'L' || adj == 'F') {
				connections.push_back(std::pair<int, int>(start.first, start.second - 1));
				dir = Left;
				tds.push_back(dir);

			}
		}
		//Check right
		if (start.second < grid[0].size() - 1) {
			char adj = grid[start.first][start.second + 1];
			if (adj == '-' || adj == '7' || adj == 'J') {
				connections.push_back(std::pair<int, int>(start.first, start.second + 1));
				dir = Right;
				tds.push_back(dir);

			}
		}

		std::pair<int, int> beg = connections[1];
		
		std::vector<std::pair<int, int>> path;
		if (tds[0] < 2 && tds[1] > 1) {
			path.push_back(start);
		}
		if (tds[1] < 2 && tds[0] > 1) {
			path.push_back(start);
		}
		

		int length = 0;
		while (beg != start) {
			if (grid[beg.first][beg.second] != '|' && grid[beg.first][beg.second] != '-') {
				path.push_back(beg);
			}
			switch (grid[beg.first][beg.second])
			{
			case '|':
				if (dir == Up) {
					beg.first--;
				}
				else {
					beg.first++;
					dir = Down;
				}
				break;
			case '-':
				if (dir == Left) {
					beg.second--;
				}
				else {
					beg.second++;
					dir = Right;
				}
				break;
			case 'F':
				if (dir == Up) {
					beg.second++;
					dir = Right;
				}
				else {
					beg.first++;
					dir = Down;
				}				
				break;
			case '7':
				if (dir == Up) {
					beg.second--;
					dir = Left;
				}
				else {
					beg.first++;
					dir = Down;
				}
				break;
			case 'L':
				if (dir == Down) {
					beg.second++;
					dir = Right;
				}
				else {
					beg.first--;
					dir = Up;
				}
				break;
			case 'J':
				if (dir == Down) {
					beg.second--;
					dir = Left;
				}
				else {
					beg.first--;
					dir = Up;
				}
				break;

			default:
				std::cerr << "Error";
				return 1;
 			}
			length++;
		}

		//Part 1
		std::cout << "Farthest point: " << (length + 1) / 2 << std::endl;

		//Part 2 - Shoelace algorithm
		int xSum = 0;
		int ySum = 0;
		for (int i = 0; i < path.size(); i++) {
			std::pair<int, int> l1 = path[i];
			std::pair<int, int> l2;
			if (i == path.size() - 1) {
				l2 = path[0];
			}
			else {
				l2 = path[i + 1];
			}

			xSum += (l1.second * l2.first);
			ySum += (l1.first * l2.second);
		}

		int diff = abs(xSum - ySum);

		int area = ((diff / 2) + 1) - ((length + 1) / 2);

		std::cout << "Area: " << area << std::endl;

		
	}
	return 0;
}
