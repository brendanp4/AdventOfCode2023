#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int nextVal(const std::vector<int>& nums) {
	bool zeros = true;
	for (auto n : nums) {
		if (n != 0) {
			zeros = false;
		}
	}
	if (zeros) {
		return 0;
	}

	std::vector<int> temp;
	for (int i = 0; i < nums.size() - 1; i++) {
		temp.push_back(nums[i + 1] - nums[i]);
	}

	//Part 1
	//return nums[nums.size() - 1] + nextVal(temp);

	//Part 2
	return nums[0] - nextVal(temp);

}

int main()
{

	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::vector<std::vector<int>> nums;
		std::string input;
		while (std::getline(iFile, input)) {
			std::vector<int> tNums;
			int temp = 0;
			bool negative = false;
			for (auto c : input) {
				if (c == '-') {
					negative = true;
				}
				else {
					if (isdigit(c)) {
						temp *= 10;
						temp += c - 48;
					}
					else {
						if (negative) {
							temp *= -1;
							negative = false;
						}
						tNums.push_back(temp);
						temp = 0;
					}
				}
			}
			if (negative) {
				temp *= -1;
				negative = false;
			}
			tNums.push_back(temp);
			nums.push_back(tNums);

		}
		int total = 0;
		for (auto v : nums) {
			total += nextVal(v);
		}
		std::cout << "Total: " << total << std::endl;

	}

}
