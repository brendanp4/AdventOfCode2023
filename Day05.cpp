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
		std::vector<long long> seeds;

		std::getline(iFile, input);
		long long temp = 0;
		for (auto c : input) {
			if (isdigit(c)) {
				temp *= 10;
				temp += c - 48;
			}
			else if (c == ' ') {
				seeds.push_back(temp);
				temp = 0;
			}
		}
		seeds.push_back(temp);
		temp = 0;


		std::vector<std::vector<std::vector<long long>>> maps;
		std::vector<std::vector<long long>> tMap;
		while (std::getline(iFile, input)) {
			if (isdigit(input[0])) {
				std::vector<long long> nums;
				for (auto c : input) {
					if (isdigit(c)) {
						temp *= 10;
						temp += c - 48;
					}
					else {
						nums.push_back(temp);
						temp = 0;
					}
				}
				nums.push_back(temp);
				temp = 0;
				tMap.push_back(nums);
			}
			else {
				if (!tMap.empty()) {
					maps.push_back(tMap);
					tMap.clear();
				}
			}
		}
		maps.push_back(tMap);

		//Part 1
		/*std::vector<long long> final;
		for (int i = 0; i < seeds.size(); i += 1) {
			long long tSeed = seeds[i];
			for (const auto map : maps) {
				for (const auto line : map) {
					if (tSeed >= line[1] && tSeed < line[1] + line[2]) {
						tSeed = line[0] + (tSeed - line[1]);
						break;
					}
				}
			}
			final.push_back(tSeed);
		}*/

		//Part 2 - BRUTE FORCE
		/*std::vector<long long> final;
		for (int i = 0; i < seeds.size(); i += 2) {
			std::cout << "Batch number: " << i << std::endl;
			for (long long j = seeds[i]; j <= seeds[i] + seeds[i + 1]; j++) {
				long long tSeed = j;
				for (const auto map : maps) {
					for (const auto line : map) {
						if (tSeed >= line[1] && tSeed < line[1] + line[2]) {
							tSeed = line[0] + (tSeed - line[1]);
							break;
						}
					}
				}
				final.push_back(tSeed);
			}
		}*/

		//Part 2 - OPTIMIZED
		//std::vector<long long> final;
		//std::vector<std::pair<long long, long long>> ranges;
		//for (int i = 0; i < seeds.size(); i += 2) {
		//	std::pair<long long, long long> range(seeds[i], seeds[i] + seeds[i + 1] - 1);
		//	ranges.push_back(range);
		//}

		//for (int j = 0; j < ranges.size(); j++) {
		//	std::pair<long long, long long> tRange = ranges[j];

		//	std::cout << "=======================================================================\nSeed range: " << tRange.first << ", " << tRange.second << std::endl;
		//	std::cout << "=======================================================================\n";

		//	for (const auto map : maps) {
		//		std::cout << "Looking at map...\n------------------------------------------------------------------------------------------------------------\n\n";
		//		for (const auto line : map) {
		//			std::cout << "	Comparing to range: " << line[1] << ", " << line[1] + line[2] - 1 << std::endl;
		//			//Check if tRange has any overlap with the map range
		//			if (tRange.first >= line[1] && tRange.first < line[1] + line[2]) {
		//				if (tRange.second < line[1] + line[2]) {
		//					tRange.first = line[0] + (tRange.first - line[1]);
		//					tRange.second = line[0] + (tRange.second - line[1]);
		//					std::cout << "Range is fully inside\n";
		//					std::cout << "New range: " << tRange.first << ", " << tRange.second << std::endl << std::endl;
		//				}
		//				else {
		//					std::pair<long long, long long> aRange(line[1] + line[2], tRange.second);
		//					ranges.push_back(aRange);
		//					tRange.second = line[1] + line[2];
		//					tRange.first = line[0] + (tRange.first - line[1]);
		//					tRange.second = line[0] + (tRange.second - line[1]);
		//					std::cout << "Half in half out on left side\n";
		//					std::cout << "New range left: " << tRange.first << ", " << tRange.second << std::endl;
		//					std::cout << "Add range right: " << aRange.first << ", " << aRange.second << std::endl << std::endl;
		//				}
		//				break;
		//			}
		//			else if (tRange.second >= line[1] && tRange.second < line[1] + line[2]) {
		//				std::pair<long long, long long> aRange(tRange.first, line[1] - 1);
		//				ranges.push_back(aRange);
		//				tRange.first = line[1];
		//				tRange.first = line[0] + (tRange.first - line[1]);
		//				tRange.second = line[0] + (tRange.second - line[1]);
		//				std::cout << "Half in half out on right side\n";
		//				std::cout << "New range right: " << tRange.first << ", " << tRange.second << std::endl;
		//				std::cout << "Add range left: " << aRange.first << ", " << aRange.second << std::endl << std::endl;
		//				break;
		//			}
		//			else if (tRange.first < line[1] && tRange.second >= line[1] + line[1]) {
		//				std::pair<long long, long long> alRange(tRange.first, line[1] - 1);
		//				std::pair<long long, long long> ahRange(line[1] + line[2], tRange.second);
		//				ranges.push_back(alRange);
		//				ranges.push_back(ahRange);
		//				tRange.first = line[1];
		//				tRange.second = line[1] + line[2];
		//				tRange.first = line[0] + (tRange.first - line[1]);
		//				tRange.second = line[0] + (tRange.second - line[1]);
		//				break;
		//			}


		//		}
		//	}
		//	std::cout << "Final seed range: " << tRange.first << ", " << tRange.second << std::endl << std::endl;
		//	final.push_back(tRange.first);
		//}
		//	

		//Part 2 - OPTIMIZED fixed
		std::vector<long long> final;
		std::vector<std::pair<long long, long long>> ranges;
		for (int i = 0; i < seeds.size(); i += 2) {
			std::pair<long long, long long> range(seeds[i], seeds[i] + seeds[i + 1] - 1);
			ranges.push_back(range);
		}

		for (int j = 0; j < ranges.size(); j++) {
			std::vector<std::pair<long long, long long>> newRanges;
			newRanges.push_back(ranges[j]);


			int length = newRanges.size();
			int tLength = 0;
			for (const auto map : maps) {
				
				for (int k = 0; k < length; k++) {
					std::pair<long long, long long> tRange = newRanges[k];
					std::cout << "=======================================================================\nSeed range: " << tRange.first << ", " << tRange.second << std::endl;
					std::cout << "=======================================================================\n";

					for (const auto line : map) {
						long long low = line[1];
						long long high = line[1] + line[2] - 1;
						std::cout << "	Comparing to range: " << low << ", " << high << std::endl;


						if (tRange.first >= low && tRange.first <= high) {
							if (tRange.second <= high) {
								tRange.first = line[0] + (tRange.first - low);
								tRange.second = line[0] + (tRange.second - low);
								newRanges[k] = tRange;
								std::cout << "Range is fully inside\n";
								std::cout << "New range: " << tRange.first << ", " << tRange.second << std::endl << std::endl;
								std::cout << "dang\n";
							}
							else {
								std::pair<long long, long long> aRange(high + 1, tRange.second);
								newRanges.push_back(aRange);
								tRange.second = high;
								tRange.first = line[0] + (tRange.first - low);
								tRange.second = line[0] + (tRange.second - low);
								newRanges[k] = tRange;

								length += 1;
								std::cout << "\n\n------------------------------------------------------------------------------------->\n";
								std::cout << "Half in half out on left side\n";
								std::cout << "New range: " << tRange.first << ", " << tRange.second << std::endl;
								std::cout << "Add range right: " << aRange.first << ", " << aRange.second << std::endl << std::endl;
								std::cout << "------------------------------------------------------------------------------------->\n\n";
							}
							break;
						}
						else if (tRange.second >= low && tRange.second <= high) {
							std::pair<long long, long long> aRange(tRange.first, low - 1);
							newRanges.push_back(aRange);
							tRange.first = low;
							tRange.first = line[0] + (tRange.first - low);
							tRange.second = line[0] + (tRange.second - low);
							newRanges[k] = tRange;

							length += 1;
							std::cout << "\n\n<-------------------------------------------------------------------------------------\n";
							std::cout << "Half in half out on right side\n";
							std::cout << "New range: " << tRange.first << ", " << tRange.second << std::endl;
							std::cout << "Add range left: " << aRange.first << ", " << aRange.second << std::endl << std::endl;
							std::cout << "<-------------------------------------------------------------------------------------\n\n";

							break;
						}
						else if (tRange.first < low && tRange.second > high) {
							std::pair<long long, long long> alRange(tRange.first, low - 1);
							std::pair<long long, long long> ahRange(high + 1, tRange.second);
							newRanges.push_back(alRange);
							newRanges.push_back(ahRange);
							tRange.first = low;
							tRange.second = high;
							tRange.first = line[0] + (tRange.first - low);
							tRange.second = line[0] + (tRange.second - low);
							newRanges[k] = tRange;

							std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
							std::cout << "Range larger than test range\n";
							std::cout << "New range: " << tRange.first << ", " << tRange.second << std::endl;
							std::cout << "Add range left: " << alRange.first << ", " << alRange.second << std::endl << std::endl;
							std::cout << "Add range right: " << ahRange.first << ", " << ahRange.second << std::endl << std::endl;
							std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";



							length += 2;
							break;
						}


					}
				}
			}
			for (auto r : newRanges) {
				if (r.first == 0) {
					int huh = 0;
				}
				final.push_back(r.first);
			}
		}



		int min = INT_MAX;
		std::cout << "Values\n";

		for (auto s : final) {
			if (s < min) {
				min = s;
			}
			std::cout << s << std::endl;
		}
		std::cout << "Closest location: " << min << std::endl;
	}
}
