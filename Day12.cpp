#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

//Part 1 - Recursive solution
//int getAns(std::string spring, std::vector<int> nums) {
//	std::string temp = spring;
//	int ans = 0;
//	int hashes = 0;
//	int qs = 0;
//	bool take = false;
//	for (int i = 0; i < temp.size(); i++) {
//		if (temp[i] == '#') {
//			if (take) {
//				return 0;
//			}
//			hashes++;
//		}
//		if (!nums.empty() && hashes == nums[0]) {
//			nums.erase(nums.begin());
//			temp = temp.substr(i + 1, std::string::npos);
//			i = -1;
//			hashes = 0;
//			take = true;
//			continue;
//		}
//		if (temp[i] == '.') {
//			take = false;
//			if (hashes) {
//				return 0;
//			}
//		}
//		if (temp[i] == '?') {
//			temp[i] = '.';
//			ans += getAns(temp, nums);
//
//			if (!take) {
//				temp[i] = '#';
//				ans += getAns(temp, nums);
//			}
//			qs++;
//			take = false;
//			break;
//		}
//	}
//	//std::cout << "Spring: " << spring << std::endl;
//	if (!qs && !hashes && nums.empty()) {
//		//std::cout << "Returning: " << 1 << std::endl << std::endl;
//		return 1;
//	}
//	//std::cout << "Returning: " << ans << std::endl << std::endl;
//	return ans;
//}

//Part 2 - Recursive with memoization
std::map<std::pair<std::string, std::vector<int>>, long long> table;

long long getAns(std::string spring, std::vector<int> nums) {
	std::string temp = spring;
	long long ans = 0;
	int hashes = 0;
	int qs = 0;
	bool take = false;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i] == '#') {
			if (take) {
				return 0;
			}
			hashes++;
		}
		if (!nums.empty() && hashes == nums[0]) {
			nums.erase(nums.begin());
			temp = temp.substr(i + 1, std::string::npos);
			i = -1;
			hashes = 0;
			take = true;
			continue;
		}
		if (temp[i] == '.') {
			take = false;
			if (hashes) {
				return 0;
			}
		}
		if (temp[i] == '?') {
			temp[i] = '.';
			if (table.count(std::pair<std::string, std::vector<int>>(temp, nums))) {
				ans += table[std::pair<std::string, std::vector<int>>(temp, nums)];
			}
			else {
				table[std::pair<std::string, std::vector<int>>(temp, nums)] = getAns(temp, nums);
				ans += table[std::pair<std::string, std::vector<int>>(temp, nums)];
			}
			

			if (!take) {
				temp[i] = '#';
				if (table.count(std::pair<std::string, std::vector<int>>(temp, nums))) {
					ans += table[std::pair<std::string, std::vector<int>>(temp, nums)];
				}
				else {
					table[std::pair<std::string, std::vector<int>>(temp, nums)] = getAns(temp, nums);
					ans += table[std::pair<std::string, std::vector<int>>(temp, nums)];
				}
			}
			qs++;
			take = false;
			break;
		}
	}
	if (!qs && !hashes && nums.empty()) {
		return 1;
	}
	return ans;
}

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
		while (std::getline(iFile, input)) {
			std::string springs;
			std::vector<int> nums;
			int temp = 0;
			bool space = false;
			std::vector<int> qs;
			int index = 0;
			for (auto c : input) {
				//Part 1
				/*if (c == '?') {
					qs.push_back(index);
					c = '.';
				}*/
				if (c == ' ') {
					space = true;
				}
				else {
					if (!space) {
						springs += c;
					}
					else {
						if (isdigit(c)) {
							temp *= 10;
							temp += c - 48;
						}
						else {
							nums.push_back(temp);
							temp = 0;
						}
					}
				}
				index++;
			}
			nums.push_back(temp);

			//Part 2
			std::string tString = springs;
			for (int i = 0; i < 4; i++) {
				tString += '?';
				tString += springs;
			}
			springs = tString;
			
			std::vector<int> tNums = nums;
			for (int i = 0; i < 4; i++) {
				tNums.insert(tNums.end(), nums.begin(), nums.end());
			}
			nums = tNums;
			
			index = 0;
			for (auto& c : springs) {
				if (c == '?') {
					qs.push_back(index);
					//c = '.';
				}
				index++;
			}
			table.clear();
			long long tTotal = getAns(springs, nums);
			std::cout << "Spring: " << springs << std::endl;
			std::cout << "Ways: " << tTotal << std::endl << std::endl;
			total += tTotal;
			
			////Part 1
			//int ps = pow(2, qs.size());
			//for (int i = 0; i < ps; i++) {
			//	std::string tempSpring = springs;
			//	int j = i;
			//	int place = 0;
			//	while (j > 0) {
			//		if (j & 1) {
			//			tempSpring[qs[place]] = '#';
			//		}
			//		place++;
			//		j >>= 1;
			//	}
			//	/*if (CheckMatch(tempSpring, nums)) {
			//		total++;
			//	}*/
			//	//std::cout << "Spring: " << tempSpring << std::endl;
			//	if (Possible(tempSpring, nums)) {
			//		tTotal++;
			//		//std::cout << "\tvalid\n";
			//	}
			//}
			//total += tTotal;
			//std::cout << "Ways: " << tTotal << std::endl;
			//int lol = 5;
		}
		std::cout << "Total: " << total << std::endl;
	}
	return 0;
}
