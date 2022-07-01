#include <map>
#include <iostream>

//Map color input from CLI to hue-value pairs representing
//lower and upper bounds relevant to identifying a certain color
std::map<std::string, std::pair<int, int>> clrmapping;

int setMapping(void) {
	clrmapping["Orange"] = std::make_pair(0, 22);
	clrmapping["Yellow"] = std::make_pair(22, 38);
	clrmapping["Green"] = std::make_pair(38, 75);
	clrmapping["Blue"] = std::make_pair(75, 130);
	clrmapping["Violet"] = std::make_pair(130, 160);
	clrmapping["Red"] = std::make_pair(160, 179);
	return 0;
}