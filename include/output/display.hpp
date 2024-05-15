#ifndef Display_H
#define Display_G

#include <string>
#include <vector>

#include "types/color.hpp"

using namespace std;
void display(string window_name, vector<vector<Color>> &img, int frame);
void fileout(string filename, vector<vector<Color>> &img, int frame, int frame_c, int fps);

#endif