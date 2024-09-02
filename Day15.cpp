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
		int total = 0;
		std::string input;
		std::vector<std::string> hashes;
		std::string temp = "";
		while (std::getline(iFile, input)) {
			for (auto c : input) {
				if (c == ',') {
					hashes.push_back(temp);
					temp.clear();
				}
				else {
					temp += c;
				}
			}
		}
		if (!temp.empty()) {
			hashes.push_back(temp);
		}
		
		//Part 1
		/*for (auto h : hashes) {
			int tHash = 0;
			for (auto c : h) {
				tHash += int(c);
				tHash *= 17;
				tHash %= 256;
			}
			total += tHash;
		}*/

		//Part 2

		//Populate HASHMAP
		std::vector<std::vector<std::string>> map;
		map.resize(256);
		for (auto h : hashes) {
			int label = 0;
			int labelLength = 0;
			for (auto c : h) {
				if (c == '=' || c == '-') {
					break;
				}
				label += int(c);
				label *= 17;
				label %= 256;
				labelLength++;
			}

			if (h[h.size() - 2] == '=') {
				bool found = false;
				for (int i = 0; i < map[label].size(); i++) {
					if (map[label][i].substr(0, map[label][i].size() - 2) == h.substr(0, labelLength)) {
						map[label][i] = h;
						found = true;
						break;
					}
				}
				if (!found) {
					map[label].push_back(h);
				}
			}
			else {
				for (int i = 0; i < map[label].size(); i++) {
					if (map[label][i].substr(0, map[label][i].size() - 2) == h.substr(0, labelLength)) {
						map[label].erase(map[label].begin() + i);
					}
				}
			}

		}

		//Calculate focusing power
		for (int i = 0; i < map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				int power = i + 1;
				power *= (j + 1);
				power *= (map[i][j][map[i][j].size() - 1] - 48);
				std::cout << "Power of lense: " << map[i][j] << std::endl;
				std::cout << "\t" << power << std::endl;
				total += power;
			}
		}

		std::cout << "\nTotal: " << total << std::endl;
	}
	return 0;
}
