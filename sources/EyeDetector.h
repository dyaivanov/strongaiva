#ifndef EYE_DETECTOR_H
#define EYE_DETECTOR_H

#include <iostream>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <queue>
#include <stdio.h>
#include <math.h>

#include "facekeypoint.h" //29.07.2022

#pragma once

const int EYE_PROCESSING_FRAME_WIDTH = 70;
const int PUPIL_IRIS_PROCESSING_FRAME_WIDTH = 150;
const bool IRIS_THRUST_ONLY_TWO_EYES = true;
const bool PUPIL_THRUST_ONLY_TWO_EYES = true;
const int IRIS_PUPIL_RATIO_POSSIBLE_ERROR = 3;
const float LEFT_RIGHT_SIGHT_KOEF = 1.9f; // 1.8f //коэфициент чувствительности поворота глаз 2.2f 30.07.2022

class EyeDetector {
private:
    void FillEyeAround(cv::Mat &_eyeROIUnscaled, cv::Rect &eye, bool left_eye); //30.07.2022
    void calculateEye(cv::Point &dstPoint, cv::Mat &face, cv::Rect &eye, bool left_eye); //30.07.2022
	void testPossibleCentersFormula(int x, int y, const cv::Mat &weight, double gx, double gy, cv::Mat &out);
	void checkEyesDirection();
	void calculateGradientsAndMagnitudes(cv::Mat &im, cv::Mat &gmX, cv::Mat &gmY, cv::Mat &mags);
    void detectIris(cv::Mat &face, cv::Rect &eyeRegion, cv::Point &pupilCenter, int &outRadius);
	void detectPupil(cv::Mat &face, cv::Rect &eyeRegion, cv::Point &pupilCenter, int &irisRadius, int &outRadius);
	void scaleToFastSize(int target_width, const cv::Mat &src, cv::Mat &dst);
	bool inMat(cv::Point p, int rows, int cols);
	double computeDynamicThreshold(const cv::Mat &mat, double stdDevFactor);
	cv::Point unscalePoint(int target_width, cv::Point p, cv::Rect origSize);
    cv::Rect findBoundingBoxFromShapes(/*dlib::full_object_detection*/cFaceKeyPoint &points, int index1, int index2, int paddingX, int paddingY); //29.07.2022
	cv::Mat computeMatXGradient(const cv::Mat &mat);	
	cv::Mat floodKillEdges(cv::Mat &mat);
	cv::Mat matrixMagnitude(const cv::Mat &matX, const cv::Mat &matY);

	cv::Mat erodeKernel3;
	int eyesDirection;
	int leftEyeIrisRadius;
	int rightEyeIrisRadius;
	int leftEyePupilRadius;
	int rightEyePupilRadius;
	int pupilIrisRatio;
	float mdArr[2][EYE_PROCESSING_FRAME_WIDTH * 2 + 1][EYE_PROCESSING_FRAME_WIDTH * 2 + 1];	
    bool findEyes(cv::Mat faceROI);

    int currentGazeDirection;
    /*dlib::full_object_detection*/cFaceKeyPoint faceDetails; //29.07.2022
public:
    cv::Point leftPupil;
    cv::Point rightPupil;
    cv::Rect leftEyeRegion;
    cv::Rect rightEyeRegion;

    const int DIR_BRIGHTNESS_PROBLEM = -2;
    const int DIR_UNKNOWN = -1;
    const int DIR_UP = 1;
    const int DIR_UP_RIGHT = 2;
    const int DIR_RIGHT = 3;
    const int DIR_DOWN_RIGHT = 4;
    const int DIR_DOWN = 5;
    const int DIR_DOWN_LEFT = 6;
    const int DIR_LEFT = 7;
    const int DIR_UP_LEFT = 8;
    const int DIR_CENTER = 9;

    EyeDetector();
	~EyeDetector();
    void processing(cv::Mat &inputFace, /*dlib::full_object_detection*/cFaceKeyPoint &inputFaceDeatils); //29.07.2022
	int getGazeDirection();
	int getPupilIrisRatio();

    cv::Mat l_eye_debug;
    cv::Mat r_eye_debug;
    //void GetDebugIm(cv::Mat &_l_eye, cv::Mat &_r_eye) //30.07.2022
    //{
    //    _l_eye = l_eye_debug;
    //    _r_eye = r_eye_debug;
    //}

    void destroy() {
		delete this;
	}	
};
#endif
