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




void init(int width, int height) {
    //video = VideoWriter ("outcpp.avi",VideoWriter::fourcc('M','J','P','G'),10, Size(width,height));
}

void display(string window_name, vector<vector<Color>> &img, int frame) {
    int width = img[0].size();
    int height = img.size();

    Mat img_mat (height, width, CV_8UC3);

    for (int y = 0; (long unsigned int)y < height; y++){
        for (int x = 0; (long unsigned int)x < width; x++){
            img_mat.at<Vec3b>(Point(x,(height-1)-y)) = {img[y][x].b,img[y][x].g,img[y][x].r};
        }
    }

    //video.write(img_mat);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    imshow(window_name, img_mat);
    if (waitKey(1)==0) exit(0);

    //if(frame > 120) {
    //    video.release();
    //    exit(0);
    //}
}