#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <tclap/CmdLine.h>
#include <iostream>
#include <vector>
#include <string>
#include "global.hpp"


FILE* outputfile;
const cv::String WINDOWTITLE = "Object Tracking";

int dumptrackingdata(void) {
	std::cout << "STORING OUTPUT IN " << output << std::endl;
	outputfile = fopen(output.c_str(), "w+");
	fprintf(outputfile, "%s\n", trackeddata.c_str());
	fclose(outputfile);

	return 0;
}

int main(int argc, char* argv[]) {
	int initsuccess = 0;
	initsuccess += setMapping();
	initsuccess += handleargs(argc, argv);

	if (initsuccess > 0) {
		std::cout << "Initialization went wrong, returning... " << std::endl;
		return initsuccess;
	}

	//Get video from camera device (0). If specified otherwise, use a source.
	cv::VideoCapture vidcap(0);
	if(source != "default") vidcap.open(source);

	//Display window unless specified otherwise (-d)
	if(displaywindow) cv::namedWindow(WINDOWTITLE, cv::WINDOW_NORMAL);

	while (true) {
		if (elapsedms >= timelimit && timelimit > 0) {
			if (output == "default") break;
			dumptrackingdata();
			break;
		}

		cv::Mat frame;
		bool success = vidcap.read(frame);

		if (!success) {
			std::cout << "End of stream encountered OR camera stream stopped working, terminating... " << std::endl;
			if (output == "default") break;
			dumptrackingdata();
			break;
		};

		
		//cv::flip(frame, frame, 1); ---- > Uncomment to flip orientation horizontally, useful for webcamera applications.
		

		/* ---- > Uncomment to flip orientation upside-down, may be needed depending on camera type or how footage was recorded.
		int hgt = frame.rows / 2;
        int wdt = frame.cols / 2;

        cv::Mat matRotation = cv::getRotationMatrix2D(cv::Point(wdt, hgt), (0), 1);
        cv::warpAffine(frame, frame, matRotation, frame.size());
		*/
		
		//Convert BGR mat to HSV mat for thresholding
		cv::Mat hsvframe;
		cv::cvtColor(frame, hsvframe, cv::COLOR_BGR2HSV);

		//Apply HSV thresholding to a new matrix for contour and image moment calculation
		cv::Mat maskedframe;
		cv::inRange(hsvframe, cv::Scalar(lowhue, lowsat, lowval), cv::Scalar(highhue, highsat, highval), maskedframe);

		//The erosion and dilations are automatically configured with sizes of 5 for general purposes,
		//can easily be changed according to usage.
		if (morphologicmode) {
			//morphological opening
			erode(maskedframe, maskedframe, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
			dilate(maskedframe, maskedframe, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

			//morphological closing
			dilate(maskedframe, maskedframe, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
			erode(maskedframe, maskedframe, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		}

		//Image contour buffer
		std::vector<std::vector<cv::Point>> imgcontours;
		cv::findContours(maskedframe, imgcontours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

		//Used for the max contour limiter option
		int detectednum = 0;

		for (int n = 0; n < imgcontours.size(); n++) {
			if (detectednum >= maxcontourcount) break;
			cv::Moments imgmoments = cv::moments(imgcontours[n]);

			//Draw contours with blue, or any other color
			cv::drawContours(frame, imgcontours, (int)n, cv::Scalar(255, 0, 0), 2);

			if (imgmoments.m00 > areathreshold) {
				detectednum += 1;
				//Centroid {x, y} = { {M(1,0) / M(0,0)}, {M(0,1) / M(0,0)} }
				double centroidx = imgmoments.m10 / imgmoments.m00;
				double centroidy = imgmoments.m01 / imgmoments.m00;

				trackeddata += std::to_string(centroidx);
				trackeddata += ", ";
				trackeddata += std::to_string(centroidy);
				trackeddata += "\n";
				//Circle any identified centroids
				cv::circle(frame, cv::Point(centroidx, centroidy), 30, cv::Scalar(255, 255, 255), 2, 8, 0);
			}
		}

		if(displaywindow) cv::imshow(WINDOWTITLE, frame);

		if (cv::waitKey(30) == 27) { //Escape upon ESC key being pressed
			if(output == "default") break;

			dumptrackingdata();
			break;
		}

		//For timekeeping
		elapsedms += 30;
	}

	//Release video capture, destroy windows
	vidcap.release();
	cv::destroyAllWindows();
	return 0;
}