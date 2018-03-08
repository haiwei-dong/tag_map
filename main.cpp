//
// Created by haiwei on 08/03/18.
//

#include <iostream>

// for displaying and saving cv images
#include <opencv2/highgui.hpp>

#include "include/create_marker.h"
#include "include/detect_marker.h"

using namespace std;

int main(int argc, char** argv)
{
    cv::Mat markerImg = haiwei_tech::create_marker(haiwei_tech::DICT_6x6_250, 23, 200, 1);

    bool showImage = 1; // show generated image

    if(showImage) {
        cv::imshow("marker", markerImg);
        cv::waitKey(0);
    }

    cv::imwrite("/home/haiwei/marker.png", markerImg);

    vector<vector<cv::Point2f>> markerCorners;
    Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    //markerCorners = detect_marker(markerImg, dictionary);


    //cv::Mat outputImage;
    //cv::aruco::drawDetectedMarkers(markerImg, markerCorners, markerIds);

    //cv::imshow("image", outputImage);


    return 0;
}
