#include "types/color.hpp"
#include <string>
#include <vector>


using namespace std;
void display(string window_name, vector<vector<Color>> &img, int frame);
void fileout(string filename, vector<vector<Color>> &img, int frame, int frame_c, int fps);