#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::string input;
		//Part 1
		/*std::vector<std::vector<int>> nums;
		std::vector<int> tNums;
		int temp = 0;*/

		//Part 2
		std::vector<long long> nums;
		while (std::getline(iFile, input)) {
			long long temp = 0;
			for (auto c : input) {
				if (isdigit(c)) {
					temp *= 10;
					temp += c - 48;
				}
				//Part 1
				/*else {
					if (temp != 0) {
						tNums.push_back(temp);
						temp = 0;
					}
				}*/
			}
			//Part 1
			/*tNums.push_back(temp);
			temp = 0;
			nums.push_back(tNums);
			tNums.clear();*/
			nums.push_back(temp);

		}

		//Part 1
		//std::vector<int> ways;
		//for (int i = 0; i < nums[0].size(); i++) {
		//	int wins = 0;
		//	int time = nums[0][i];
		//	int dist = nums[1][i];
		//	int nDist = 0;
		//	for (int j = 0; j <= time; j++) {
		//		nDist = j * (time - j);
		//		if (nDist > dist) {
		//			wins++;
		//		}
		//		nDist = 0;
		//	}
		//	ways.push_back(wins);
		//}

		//
		//int final = 1;
		//for (auto w : ways) {
		//	final *= w;
		//}
		//std::cout << "Product of ways to win: " << final << std::endl;

		//Part 2 - BRUTEFORCE
		long long time = nums[0];
		long long dist = nums[1];
		long long wins = 0;
		for (long long j = 0; j <= time; j++) {
			if ((j * (time - j)) > dist) {
				wins++;
			}
		}

		std::cout << "Ways to win: " << wins << std::endl;
	}
}
