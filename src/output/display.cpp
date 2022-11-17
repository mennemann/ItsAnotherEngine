#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "display.hpp"
#include "../types/color.hpp"
#include <string>
#include <vector>

#include <iostream>

using namespace std;
using namespace cv;

bool inited = false;
VideoWriter video;


Mat convert(vector<vector<Color>> &img) {
    int width = img[0].size();
    int height = img.size();

    Mat m (height, width, CV_8UC3);

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            m.at<Vec3b>(Point(x,(height-1)-y)) = {img[y][x].b,img[y][x].g,img[y][x].r};
        }
    }

    return m; 
}

void display(string window_name, vector<vector<Color>> &img, int frame) {
    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, convert(img));
    if (waitKey(1)==0) exit(0);
}

void fileout(string filename, vector<vector<Color>> &img, int frame, int frame_c, int fps) {
    if (!inited) {
        video = VideoWriter (filename,VideoWriter::fourcc('M','J','P','G'),fps, Size(img[0].size(),img.size()));
        inited = true;
    }
    video.write(convert(img));
    if(frame > frame_c) {
        video.release();
        exit(0);
    }
}