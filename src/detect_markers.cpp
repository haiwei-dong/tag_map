//
// Created by haiwei on 12/03/18.
//

#include <iostream>

#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

#include "../include/dictionary_definition.h"

using namespace std;
using namespace cv;

string camera_parameter_filename = "/home/haiwei/CLionProjects/data/out_camera_data.xml";
string detector_parameter_filename = "/home/haiwei/CLionProjects/data/detector_params.yml";
string image_file = "/home/haiwei/CLionProjects/data/single_marker.jpg";

bool readCameraParameters(string filename, Mat &camMatrix, Mat &distCoeffs)
{
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["camera_matrix"] >> camMatrix;
    fs["distortion_coefficients"] >> distCoeffs;
    return true;
}

bool readDetectorParameters(string filename, Ptr<aruco::DetectorParameters> &params)
{
    FileStorage fs(filename, FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["adaptiveThreshWinSizeMin"] >> params->adaptiveThreshWinSizeMin;
    fs["adaptiveThreshWinSizeMax"] >> params->adaptiveThreshWinSizeMax;
    fs["adaptiveThreshWinSizeStep"] >> params->adaptiveThreshWinSizeStep;
    fs["adaptiveThreshConstant"] >> params->adaptiveThreshConstant;
    fs["minMarkerPerimeterRate"] >> params->minMarkerPerimeterRate;
    fs["maxMarkerPerimeterRate"] >> params->maxMarkerPerimeterRate;
    fs["polygonalApproxAccuracyRate"] >> params->polygonalApproxAccuracyRate;
    fs["minCornerDistanceRate"] >> params->minCornerDistanceRate;
    fs["minDistanceToBorder"] >> params->minDistanceToBorder;
    fs["minMarkerDistanceRate"] >> params->minMarkerDistanceRate;
    fs["cornerRefinementMethod"] >> params->cornerRefinementMethod;
    fs["cornerRefinementWinSize"] >> params->cornerRefinementWinSize;
    fs["cornerRefinementMaxIterations"] >> params->cornerRefinementMaxIterations;
    fs["cornerRefinementMinAccuracy"] >> params->cornerRefinementMinAccuracy;
    fs["markerBorderBits"] >> params->markerBorderBits;
    fs["perspectiveRemovePixelPerCell"] >> params->perspectiveRemovePixelPerCell;
    fs["perspectiveRemoveIgnoredMarginPerCell"] >> params->perspectiveRemoveIgnoredMarginPerCell;
    fs["maxErroneousBitsInBorderRate"] >> params->maxErroneousBitsInBorderRate;
    fs["minOtsuStdDev"] >> params->minOtsuStdDev;
    fs["errorCorrectionRate"] >> params->errorCorrectionRate;
    return true;
}

int main(int argc, char* argv[])
{
    int dictionaryId = DICT_6x6_250;; //dictionary
    bool showRejected = 0; //show rejected candidates too
    bool estimatePose = 1; //camera instrinsic parameters. Needed for camera pose
    float markerLength = 0.34; // Marker side length (in meters). Needed for correct scale in camera pose
    int camId; // camera id if input does not come from video

    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
    bool readOk = readDetectorParameters(detector_parameter_filename, detectorParams);
    if(!readOk)
    {
        cerr << "Invalid detector parameters file" << endl;
        return 0;
    }
    detectorParams->cornerRefinementMethod = aruco::CORNER_REFINE_SUBPIX; // do corner refinement in markers

    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

    Mat camMatrix, distCoeffs;
    if(estimatePose)
    {
        bool readOk = readCameraParameters(camera_parameter_filename, camMatrix, distCoeffs);
        if(!readOk)
        {
            cerr << "Invalid camera file" << endl;
            return 0;
        }
    }

    Mat image, imageCopy;
    image = imread(image_file, cv::IMREAD_COLOR);

    vector<int> ids;
    vector< vector<cv::Point2f> > corners, rejected;
    vector<Vec3d> rvecs, tvecs;

    // detect markers
    aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);

    cout<<camMatrix<<endl;
    cout<<distCoeffs<<endl;

    // estimate pose
    if(estimatePose && ids.size() > 0)
    {
        aruco::estimatePoseSingleMarkers(corners, markerLength, camMatrix, distCoeffs, rvecs, tvecs);
    }

    // draw results
    image.copyTo(imageCopy);
    if(ids.size() > 0)
    {
        aruco::drawDetectedMarkers(imageCopy, corners, ids);

        if(estimatePose)
        {
            for(unsigned int i=0; i<ids.size(); i++)
            {
                aruco::drawAxis(imageCopy, camMatrix, distCoeffs, rvecs[i], tvecs[i], markerLength*0.5f);
            }
        }
    }

    if(showRejected && rejected.size() > 0)
    {
        aruco::drawDetectedMarkers(imageCopy, rejected, noArray(), Scalar(100, 0, 255));
    }

    imshow("out", imageCopy);
    waitKey(0);


    return 0;
}