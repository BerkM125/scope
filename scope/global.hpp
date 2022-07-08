#include <map>
#include <iostream>

extern int areathreshold;
extern int lowhue;
extern int highhue;
extern int lowval;
extern int highval;
extern int lowsat;
extern int highsat;
extern int elapsedms;
extern int timelimit;
extern int maxcontourcount;
extern bool displaywindow;
extern bool morphologicmode;
extern std::string source;
extern std::string imagesrc;
extern std::string output;
extern std::string trackeddata;
extern std::map<std::string, std::pair<int, int>> clrmapping;
extern int setMapping(void);
extern int handleargs(int argc, char* argv[]);