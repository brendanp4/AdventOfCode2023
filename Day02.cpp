#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const int MAX_R = 12;
const int MAX_G = 13;
const int MAX_B = 14;

int main() {
	std::ifstream iFile;
	iFile.open("C:\\Users\\brend\\Documents\\input.txt", std::ios::in);
	if (iFile.fail()) {
		std::cerr << "File not found\n";
	}
	else {
		int sum = 0;
		std::string input;
		while (std::getline(iFile, input)) {

			int r = 0;
			int g = 0;
			int b = 0;

			int temp = 0;

			int index = 0;

			bool game = false;
			bool possible = true;

			int i = 0;
			for (auto c : input) {
				if (c == ':') {
					game = true;
				}
				if (isdigit(c)) {
					if (!game) {
						index *= 10;
						index += c - 48;
					}
					else {
						temp *= 10;
						temp += c - 48;
					}
				}
				else {
					//if (c == ';') {
					//	r = 0;
					//	b = 0;
					//	g = 0;
					//	temp = 0;
					//}
					if (temp != 0) {
						if (i + 5 < input.size() && input.substr(i + 1, 5) == "green") {
							g = std::max(g, temp);
							//g += temp;
							//if (g > MAX_G) {
							//	possible = false;
							//	break;
							//}
						}
						if (i + 4 < input.size() && input.substr(i + 1, 4) == "blue") {
							b = std::max(b, temp);
							//b += temp;
							//if (b > MAX_B) {
							//	possible = false;
							//	break;
							//}
						}
						if (i + 3 < input.size() && input.substr(i + 1, 3) == "red") {
							r = std::max(r, temp);
							//r += temp;
							//if (r > MAX_R) {
							//	possible = false;
							//	break;
							//}
						}
						temp = 0;
					}
				}
				i++;
			}
			int power = r * b * g;
			sum += power;
			//if (possible) {
			//	sum += index;
			//}
			
		}
		std::cout << "Sum of power values: " << sum << std::endl;
	}

	return 0;
}
