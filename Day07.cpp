#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

std::vector<char> cards{ 'A', 'K', 'Q','T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
std::map<char, int> strength;

bool compare(std::pair<std::pair<std::string,int>, int> A, std::pair<std::pair<std::string, int>, int> B) {
	if (A.first.second == B.first.second) {

		for (int i = 0; i < A.first.first.size(); i++) {
			if (A.first.first[i] != B.first.first[i]) {
				return strength[A.first.first[i]] > strength[B.first.first[i]];
			}
		}
	}
	return A.first.second > B.first.second;
}

int main()
{
	for (int i = 0; i < cards.size(); i++) {
		strength[cards[i]] = i;
	}
	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		std::string input;
		//Part 2
		std::vector<std::pair<std::pair<std::string,int>,int>> hands;
		while (std::getline(iFile, input)) {
			bool space = false;
			std::pair<std::string, int> ranks("",0);
			std::pair<std::pair<std::string,int>, int> temp(ranks,0);
			int rank = 0;
			int max = 0;
			int jCount = 0;
			std::map<char, int> tMap;
			for (auto c : input) {
				if (c == ' ') {
					space = true;
				}
				else {
					if (!space) {
						temp.first.first += c;
						tMap[c]++;
						if (tMap[c] > max) {
							max = tMap[c];
						}
						if (c == 'J') {
							jCount++;
						}
					}
					else {
						if (isdigit(c)) {
							temp.second *= 10;
							temp.second += c - 48;
						}
					}
				}
			}
			switch (tMap.size()) {
			case 1:
				rank = 1;
				break;
			case 2:
				//max == 4 ? rank = 2 : rank = 3;
				if (max == 4) {
					rank = 2;
				}
				else {
					rank = 3;
				}
				if (jCount) {
					rank = 1;
				}
				break;
			case 3:
				//max == 3 ? rank = 4 : rank = 5;
				if (max == 3) {
					rank = 4;
					if (jCount) {
						rank = 2;
					}
				}
				else {
					rank = 5;
					if (jCount == 1) {
						rank = 3;
					}
					if (jCount == 2) {
						rank = 2;
					}
				}
				break;
			case 4:
				rank = 6;
				if (jCount) {
					rank = 4;
				}
				break;
			default:
				rank = 7;
				if (jCount) {
					rank = 6;
				}
				break;
			}
			temp.first.second = rank;
			hands.push_back(temp);

		}
		std::cout << "Presorted\n";
		for (auto hand : hands) {
			std::cout << hand.first.first << " " << hand.first.second << " " << hand.second << std::endl;
		}
		std::sort(hands.begin(), hands.end(), compare);
		std::cout << "\n\nSorted\n";
		for (auto hand : hands) {
			std::cout << hand.first.first << " " << hand.first.second << " " << hand.second << std::endl;
		}

		long long winnings = 0;
		long long index = 1;
		for (auto hand : hands) {
			winnings += (index * long long(hand.second));
			index++;
		}
		std::cout << "Total winnings: " << winnings << std::endl;
	}
}
