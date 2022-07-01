#include <iostream>
#include <tclap/CmdLine.h>
#include "global.hpp"

int handleargs(int argc, char* argv[]) {
	try {
		TCLAP::CmdLine cmd("Simplified computer vision CLI tool", ' ', "1.0");
		TCLAP::ValueArg<std::string> areaArg("a", "area",
			"Minimum contour area threshold for color identification or tracking",
			false, "600", "integer");
		TCLAP::ValueArg<std::string> colorArg("c", "color",
			"Isolated color choice from Orange, Yellow, Green, Blue, Violet, and Red",
			false, "Blue", "string");
		TCLAP::ValueArg<std::string> contourArg("n", "contourcount",
			"Maximum number of contours to track/identify at the same time",
			false, "10", "integer");
		TCLAP::ValueArg<std::string> sourceArg("v", "videosource",
			"Video stream or recording destination path (by default, the source is a default webcamera)",
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
		cmd.add(timeArg);
		// Parse the argv array.
		cmd.parse(argc, argv);

		// Get the value parsed by each arg.
		std::string areastr = areaArg.getValue();
		std::string contourstr = contourArg.getValue();
		std::string timestr = timeArg.getValue();
		source = sourceArg.getValue();
		output = outputArg.getValue();
		morphologicmode = morphoArg.getValue();
		displaywindow = displayArg.getValue();
		areathreshold = std::stoi(areastr);
		maxcontourcount = std::stoi(contourstr);
		timelimit = std::stoi(timestr);

		if (clrmapping.find(colorArg) == clrmapping.end()) {
			std::cout << "Not a viable color, returning... " << std::endl;
			return 1;
		}
		std::pair<int, int> bounds = clrmapping[colorArg];

		lowhue = bounds.first;
		highhue = bounds.second;
	}
	catch (TCLAP::ArgException& e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return 1;
	}
	return 0;
}