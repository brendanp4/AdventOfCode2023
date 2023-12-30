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
		int sum = 0;
		std::string input;
		bool winning = false;
		bool yours = false;
		std::vector<int> copies;
		copies.resize(218, 1);
		int i = 0;
		while (std::getline(iFile, input)) {
			std::map<int, int> winning_numbers;
			std::vector<int> your_numbers;
			int temp = 0;
			int card = 0;
			for (auto c : input) {
				if (c == ':') {
					winning = true;
					card = temp;
					temp = 0;
				}
				if (c == '|') {
					winning = false;
					yours = true;
					temp = 0;
				}
				if (isdigit(c)) {
					temp *= 10;
					temp += c - 48;
				}
				if (isspace(c)) {
					if (winning && temp > 0) {
						winning_numbers[temp]++;
					}
					else if (yours && temp > 0) {
						your_numbers.push_back(temp);
					}
					temp = 0;
				}
			}
			//Part 1------------------------------------------------------------
			//your_numbers.push_back(temp);
			//temp = 0;
			//for (auto n : your_numbers) {
			//	if (winning_numbers.count(n)) {
			//		temp++;
			//	}
			//}
			//sum += pow(2, temp - 1);
			//Part 2------------------------------------------------------------
			your_numbers.push_back(temp);
			temp = 0;
			for (auto n : your_numbers) {
				if (winning_numbers.count(n)) {
					temp++;
				}
			}
			int match = temp;
			for (int j = 1; j <= match; j++)
			{
				copies[i + j] += copies[i];
			}



			i++;
		}

		
		for (size_t i = 0; i < copies.size(); i++)
		{
			sum += copies[i];
		}

		std::cout << "Total cards: " << sum << std::endl;
	}

	return 0;
}
