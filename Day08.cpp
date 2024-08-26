#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


int GCD(int a, int b) {
	int R;
	while ((a % b) > 0) {
		R = a % b;
		a = b;
		b = R;
	}
	return b;

}


int main()
{

	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::vector<std::string> starts;
		std::map<std::string, std::pair<std::string, std::string>> map;
		std::string directions;
		std::getline(iFile, directions);
		std::string input;
		while (std::getline(iFile, input)) {
			std::string temp = "";
			std::vector<std::string> inputs;
			for (auto c : input) {
				if (isupper(c) || isdigit(c)) {
					temp += c;
				}
				else {
					if (!temp.empty()) {
						inputs.push_back(temp);
						temp.clear();
					}
				}
			}
			map[inputs[0]].first = inputs[1];
			map[inputs[0]].second = inputs[2];
			if (inputs[0][2] == 'A') {
				starts.push_back(inputs[0]);
			}
		}
		//Part 1
		//std::string cur = "AAA";
		//int steps = 0;
		//while (cur != "ZZZ") {
		//	char dir = directions[steps % directions.size()];
		//	dir == 'L' ? cur = map[cur].first : cur = map[cur].second;
		//	steps++;
		//}
		//std::cout << "Took " << steps << " to reach ZZZ\n\n";

		////Part 2 - BRUTEFORCE
		////std::string cur = "AAA";
		//int steps = 0;
		//bool found = false;
		//while (!found) {
		//	std::cout << "Step: " << steps + 1 << std::endl;
		//	found = true;
		//	char dir = directions[steps % directions.size()];
		//	for (auto& cur : starts) {
		//		std::cout << cur << " --> ";
		//		dir == 'L' ? cur = map[cur].first : cur = map[cur].second;
		//		if (cur[2] != 'Z') {
		//			found = false;
		//		}
		//		std::cout << cur << std::endl << std::endl;
		//	}
		//	steps++;
		//}
		//std::cout << "Took " << steps << " for all starting positions to reach **Z\n\n";

		////Part 2 - BRUTEFORCE - Another way
		//std::vector<int> allSteps;
		//for (auto& cur : starts) {
		//	int steps = 0;
		//	while (cur[2] != 'Z') {
		//		char dir = directions[steps % directions.size()];
		//		dir == 'L' ? cur = map[cur].first : cur = map[cur].second;
		//		steps++;
		//	}
		//	allSteps.push_back(steps);
		//}
		//int steps = 1;
		//bool found = false;
		//while (!found) {
		//	if (steps % 100 == 0) {
		//		std::cout << "On step: " << steps << std::endl;
		//	}
		//	found = true;
		//	for (auto s : allSteps) {
		//		if (steps % s != 0) {
		//			found = false;
		//			break;
		//		}
		//	}
		//	steps++;
		//}
		//std::cout << "Took " << steps - 1 << " for all starting positions to reach **Z\n\n";

		//Part 2 - OPTIMIZED
		std::vector<int> allSteps;
		for (auto& cur : starts) {
			int steps = 0;
			while (cur[2] != 'Z') {
				char dir = directions[steps % directions.size()];
				dir == 'L' ? cur = map[cur].first : cur = map[cur].second;
				steps++;
			}
			allSteps.push_back(steps);
		}
	

		////Find greatest common denominator of all step values
		int gcd = GCD(allSteps[0],allSteps[1]);
		for (int i = 2; i < allSteps.size(); i++) {
			gcd = GCD(gcd, allSteps[i]);
		}
		
		//Find least common multiple
		long long lcm = (long long(allSteps[0]) * long long(allSteps[1])) / long long(gcd);
		for (int i = 2; i < allSteps.size(); i++) {
			lcm = (lcm * long long(allSteps[i])) / long long(gcd);
		}
		

		
		std::cout << "Took " << lcm << " for all starting positions to reach **Z\n\n";


	}

}
