//
// Created by haiwei on 08/03/18.
//

#ifndef TAG_MAP_DETECT_MARKER_H
#define TAG_MAP_DETECT_MARKER_H

#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

using namespace cv;
using namespace std;

enum dictionaryId
{
    DICT_4x4_50 = 0,
    DICT_4x4_100 = 1,
    DICT_4x4_250 = 2,
    DICT_4x4_1000 = 3,

    DICT_5x5_50 = 4,
    DICT_5x5_100 = 5,
    DICT_5x5_250 = 6,
    DICT_5x5_1000 = 7,

    DICT_6x6_50 = 8,
    DICT_6x6_100 = 9,
    DICT_6x6_250 = 10,
    DICT_6x6_1000 = 11,

    DICT_7x7_50 = 12,
    DICT_7x7_100 = 13,
    DICT_7x7_250 = 14,
    DICT_7x7_1000 = 15,

    DICT_ARUCO_ORIGINAL = 16
};

vector<vector<Point2f>> detect_marker(cv::Mat image, cv::Ptr<cv::aruco::Dictionary> dictionary)
{

    vector< vector<Point2f> > corners, rejected;
    vector<int> ids;
    Ptr<cv::aruco::DetectorParameters> detectorParams;

    // detect markers
    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);
    return corners;
}


#endif //TAG_MAP_DETECT_MARKER_H
