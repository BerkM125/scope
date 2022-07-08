#include <iostream>
#include <tclap/CmdLine.h>
#include "global.hpp"

std::pair<int, int> parserange(std::string argv) {
	std::vector<int> parsedbuffer;
	char str[8];
	strcpy(str, argv.c_str());
	char* split = strtok(str, "_");

	while (split != NULL) {
		parsedbuffer.push_back(strtol(split, NULL, 10));
		split = strtok(NULL, "_");
	}
	return std::make_pair(parsedbuffer[0], parsedbuffer[1]);
}

int handleargs(int argc, char* argv[]) {
	try {
		TCLAP::CmdLine cmd("Simplified computer vision CLI tool", ' ', "1.0");
		TCLAP::ValueArg<std::string> areaArg("a", "area",
			"Minimum contour area threshold for color identification or tracking",
			false, "600", "integer");
		TCLAP::ValueArg<std::string> colorArg("c", "color",
			"Isolated color choice from Orange, Yellow, Green, Blue, Violet, and Red",
			false, "Default", "string");

		TCLAP::ValueArg<std::string> hueArg("e", "hue",
			"Set a custom hue (HSV) isolation range instead of using automatically configured colors in the program",
			false, "75_130", "lowerbound_upperbound");
		TCLAP::ValueArg<std::string> satArg("s", "saturation",
			"Set a custom saturation (HSV) isolation range instead of using automatically configured colors in the program",
			false, "200_255", "lowerbound_upperbound");
		TCLAP::ValueArg<std::string> valArg("z", "value",
			"Set a custom value (HSV) isolation range instead of using automatically configured colors in the program",
			false, "200_255", "lowerbound_upperbound");

		TCLAP::ValueArg<std::string> contourArg("n", "contourcount",
			"Maximum number of contours to track/identify at the same time",
			false, "10", "integer");
		TCLAP::ValueArg<std::string> sourceArg("v", "videosource",
			"Video stream or recording destination path (by default, the source is a default webcamera)",
			false, "default", "string");
		TCLAP::ValueArg<std::string> imageSourceArg("i", "imagesource",
			"Image destination path (by default, the program will revert to a video source / webcamera)",
			false, "default", "string");
		TCLAP::ValueArg<std::string> outputArg("o", "output",
			"Path to centroid coordinate data dump if looking to record tracking data",
			false, "default", "string");
		TCLAP::ValueArg<std::string> timeArg("t", "timelimit",
			"Time limit, image processing will end after this much time passes (milliseconds)",
			false, "-1", "integer");
		TCLAP::SwitchArg morphoArg("m", "morphomode",
			"Choose whether or not to apply morphological opening/closing (-m to prevent)",
			cmd, true);
		TCLAP::SwitchArg displayArg("d", "display",
			"Choose whether or not to display a window with video and image processing footage (-d to hide)",
			cmd, true);



		cmd.add(areaArg);
		cmd.add(colorArg);
		cmd.add(contourArg);
		cmd.add(sourceArg);
		cmd.add(outputArg);
		cmd.add(imageSourceArg);
		cmd.add(timeArg);
		cmd.add(hueArg);
		cmd.add(valArg);
		cmd.add(satArg);
		// Parse the argv array.
		cmd.parse(argc, argv);

		// Get the value parsed by each arg.
		std::string areastr = areaArg.getValue();
		std::string contourstr = contourArg.getValue();
		std::string timestr = timeArg.getValue();
		imagesrc = imageSourceArg.getValue();
		source = sourceArg.getValue();
		output = outputArg.getValue();
		morphologicmode = morphoArg.getValue();
		displaywindow = displayArg.getValue();
		areathreshold = std::stoi(areastr);
		maxcontourcount = std::stoi(contourstr);
		timelimit = std::stoi(timestr);

		std::pair<int, int> hueRange = parserange(hueArg.getValue());
		std::pair<int, int> satRange = parserange(satArg.getValue());
		std::pair<int, int> valRange = parserange(valArg.getValue());

		lowhue = hueRange.first; highhue = hueRange.second;
		lowsat = satRange.first; highsat = satRange.second;
		lowval = valRange.first; highval = valRange.second;

		//std::cout << lowhue << " " << highhue << std::endl;

		if (colorArg.getValue() != "Default") {
			if (clrmapping.find(colorArg) == clrmapping.end()) {
				std::cout << "Not a viable color, returning... " << std::endl;
				return 1;
			}
			std::pair<int, int> bounds = clrmapping[colorArg];

			lowhue = bounds.first;
			highhue = bounds.second;
		}
	}
	catch (TCLAP::ArgException& e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return 1;
	}
	return 0;
}