//
// Created by haiwei on 08/03/18.
//

/*
 *  int dictionaryId: Type of the dictionary
    int markerId: Marker id in the dictionary
    int markerSize: Marker size in pixels
    int borderBits: Number of bits in marker borders
 */

#ifndef TAG_MAP_CREATE_MARKER_H
#define TAG_MAP_CREATE_MARKER_H

#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>

namespace haiwei_tech
{
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

    cv::Mat create_marker(int dictionaryId, int markerId, int markerSize, int borderBits)
    {
        cv::Ptr<cv::aruco::Dictionary> dictionary =
                cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

        cv::Mat markerImg;
        cv::aruco::drawMarker(dictionary, markerId, markerSize, markerImg, borderBits);

        return markerImg;
    }

}

#endif //TAG_MAP_CREATE_MARKER_H
