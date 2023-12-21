#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		int index = 0;

		std::string input;
		int sum = 0;
		std::vector<std::string> nums = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
		while (std::getline(iFile, input)) {
			std::vector<int> match(9, 0);
			int first = -1;
			int last = -1;
			for (auto c : input) {
				if (isdigit(c)) {
					if (first == -1) {
						first = c - 48;
					}
					last = c - 48;
					std::fill(match.begin(), match.end(), 0);
				}
				else {
					for (int i = 0; i < nums.size(); i++) {
						if (match[i] >= nums[i].size() || (c != nums[i][match[i]] && match[i] != 1)) {
							match[i] = 0;
						}
						if (match[i] < nums[i].size() && c == nums[i][match[i]]) {
							match[i]++;
							if (match[i] == nums[i].size()) {
								int num = i + 1;
								if (first == -1) {
									first = num;
								}
								last = num;
								match[i] = 0;
							}
						}
					}
				}
			}
			if (index < 100) {
				std::cout << "String: " << input << std::endl; 
				std::cout << "Number: " << first * 10 + last << std::endl << std::endl;
			}
			sum += (first * 10) + last;
			index++;
		}
		std::cout << "Calibration value: " << sum << std::endl;
	}

	return 0;
}
