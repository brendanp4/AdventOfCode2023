#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


int getLoc(std::string A, std::string B) {
	int d = 0;
	int j = -1;
	for (int i = 0; i < A.size(); i++) {
		if (A[i] != B[i]) {
			d++;
			j = i;
		}
	}
	if (d == 1) {
		return j;
	}
	return -1;
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
		std::vector<std::string> hGrid;
		std::vector<std::string> vGrid;
		bool first = true;
		while (std::getline(iFile, input)) {
			if (input[0] == '.' || input[0] == '#') {
				if (first) {
					vGrid.resize(input.size(), "");
					first = false;
				}
				hGrid.push_back(input);
				for (int i = 0; i < input.size(); i++) {
					vGrid[i] = input[i] + vGrid[i];
				}
			}
			else {
				//Part 1
				/*int hMirrors = 0;
				int vMirrors = 0;
				int hTemp = 0;
				for (int i = 0; i < hGrid.size() - 1; i++) {
					hTemp = 0;
					bool valid = false;
					if (hGrid[i] == hGrid[i + 1]) {
						valid = true;
						for (int j = i - 1; j >= 0; j--) {
							int t = i + 1 + (i - j);
							if (t >= hGrid.size()) {
								break;
							}
							if (hGrid[j] != hGrid[t]) {
								valid = false;
								break;
							}
						}
					}
					if (valid) {
						hMirrors += (i + 1);
					}
				}

				int vTemp = 0;
				for (int i = 0; i < vGrid.size() - 1; i++) {
					vTemp = 0;
					bool valid = false;
					if (vGrid[i] == vGrid[i + 1]) {
						valid = true;
						for (int j = i - 1; j >= 0; j--) {
							int t = i + 1 + (i - j);
							if (t >= vGrid.size()) {
								break;
							}
							if (vGrid[j] != vGrid[t]) {
								valid = false;
								break;
							}
						}
					}
					if (valid) {
						vMirrors += (i + 1);
					}
				}

				hGrid.clear();
				vGrid.clear();
				first = true;
				total += vMirrors + (hMirrors * 100);*/

				//Part 2

				//Find smudge vertical
				int hMirrors = 0;
				int vMirrors = 0;
				int hTemp = 0;
				bool smudge = false;
				for (int i = 0; i < hGrid.size() - 1; i++) {
					hTemp = 0;
					char temp;
					smudge = false;
					bool valid = false;
					int loc = getLoc(hGrid[i], hGrid[i + 1]);
					if (loc >= 0) {
						temp = hGrid[i][loc];
						hGrid[i][loc] = hGrid[i + 1][loc];
						smudge = true;
					}
					if (hGrid[i] == hGrid[i + 1]) {
						valid = true;
						for (int j = i - 1; j >= 0; j--) {
							int t = i + 1 + (i - j);
							if (t >= hGrid.size()) {
								break;
							}
							if (hGrid[j] != hGrid[t]) {
								if (!smudge) {
									loc = getLoc(hGrid[j], hGrid[t]);
									if (loc >= 0) {
										temp = hGrid[j][loc];
										hGrid[j][loc] = hGrid[t][loc];
										smudge = true;
									}
								}
								else {
									hGrid[i][loc] = temp;
									valid = false;
									smudge = false;
								}
								break;
							}
						}
						if (valid && smudge) {
							hMirrors += (i + 1);
						}
					}
					if (smudge) {
						break;
					}
				}
				if (!smudge) {
					int vTemp = 0;
					for (int i = 0; i < vGrid.size() - 1; i++) {
						vTemp = 0;
						char temp;
						smudge = false;
						bool valid = false;
						int loc = getLoc(vGrid[i], vGrid[i + 1]);
						if (loc >= 0) {
							temp = vGrid[i][loc];
							vGrid[i][loc] = vGrid[i + 1][loc];
							smudge = true;
						}
						if (vGrid[i] == vGrid[i + 1]) {
							valid = true;
							for (int j = i - 1; j >= 0; j--) {
								int t = i + 1 + (i - j);
								if (t >= vGrid.size()) {
									break;
								}
								if (vGrid[j] != vGrid[t]) {
									if (!smudge) {
										loc = getLoc(vGrid[j], vGrid[t]);
										if (loc >= 0) {
											temp = vGrid[j][loc];
											vGrid[j][loc] = vGrid[t][loc];
											smudge = true;
										}
									}
									else {
										vGrid[i][loc] = temp;
										valid = false;
									}
									break;
								}
							}
							if (valid && smudge) {
								vMirrors += (i + 1);
							}
						}

					}
				}

				hGrid.clear();
				vGrid.clear();
				first = true;
				total += vMirrors + (hMirrors * 100);
			}
		}

		std::cout << "Total: " << total << std::endl;
	}
	return 0;
}
