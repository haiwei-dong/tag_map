//
// Created by haiwei on 12/03/18.
//

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

#include "../include/dictionary_definition.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    bool showImage = 1; //show the generated marker
    bool saveImage = 1; //save the generated marker
    string marker_file = "/home/haiwei/CLionProjects/data/marker.png";

    int dictionaryId = DICT_6x6_250; //Type of the dictionary
    int markerId = 23; //Marker id in the dictionary
    int markerSize = 200; //Marker size in pixels
    int boarderBits = 1; //Number of bits in marker borders

    Ptr<aruco::Dictionary> dictionary
            = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));
    Mat markerImg;
    aruco::drawMarker(dictionary, markerId, markerSize, markerImg, boarderBits);

    if(saveImage)
    {
        imwrite(marker_file, markerImg);
    }

    if(showImage)
    {
        imshow("marker", markerImg);
        waitKey(0);
    }
}