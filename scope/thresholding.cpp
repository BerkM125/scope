#include <iostream>
#include <string>

//Area threshold, only contours with this area (image
//moment ( M(0,0) ) ) are regarded when calculating a 
//centroid/centroids.
int areathreshold = 600;

//Automatically configured for blue.
int lowhue = 75;
int highhue = 130;

//Automatically configured for values between 200-255.
int lowval = 200;
int highval = 255;

//Automatically configured for saturations between 150-255.
int lowsat = 150;
int highsat = 255;

//Timing variables
int elapsedms = 0;
int timelimit = -1;

//Upper-bound for contour tracking, no more than this number of
//centroids will be displayed/tracked on-screen at a given moment.
int maxcontourcount = 10;

//Pretty obvious what this is
bool displaywindow = true;

//Applying morphological opening and closing
bool morphologicmode = true;

//CLI variables
std::string source = "default";
std::string output = "default";

//String used to temporarily store all centroid data
std::string trackeddata = "";