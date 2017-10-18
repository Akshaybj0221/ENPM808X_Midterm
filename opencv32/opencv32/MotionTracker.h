/****************************************************************************************
*																						*												*                       *
*																						*
* MIT License																			*
*																						*
* Copyright (c) [2017] [Akshay Bajaj]													*
*																						*
* Permission is hereby granted, free of charge, to any person obtaining a copy          *
* of this software and associated documentation files (the "Software"), to deal         *
* in the Software without restriction, including without limitation the rights          *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell             *
* copies of the Software, and to permit persons to whom the Software is                 *
* furnished to do so, subject to the following conditions:                              *
*															                            *
* The above copyright notice and this permission notice shall be included in all        *
* copies or substantial portions of the Software.                                       *
*																						*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR			*
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,				*
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE			*
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER				*
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,			*
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE			*
* SOFTWARE.																				*
*																						*
****************************************************************************************/

/**
*   @file	MotionTracker.h
*   @brief  	This is a motion tracker, vision system which tracks and tags moving object.
*				It looks for an object which has a shape similar to that of a ball and tracks it.
				It also gives the location of the moving object.
*
*   Feed the input video using getVideo funtion of the program
*
*   @author	Akshay Bajaj
*   @date	2017/10/10
*/


#ifndef INCLUDE_MOTIONTRACKER_HPP_
#define INCLUDE_MOTIONTRACKER_HPP_
#include <opencv2/opencv.hpp>
using namespace cv;


class MotionTracker {
protected:
	const static int SENSITIVITY_VALUE = 20;
	const static int BLUR_SIZE = 10;
	int theObject[2] = { 0,0 };
	Rect objectBoundingRectangle = Rect(0, 0, 0, 0);
	bool objectDetected = false;						///< some boolean variables for added functionality
	bool trackingEnabled = false;
	bool pause = false;									///< pause and resume code
	Mat frame1, frame2;									///< set up the matrices that we will need the two frames we will be comparing
	Mat grayImage1, grayImage2;							///< their grayscale images (needed for absdiff() function)
	Mat differenceImage;								///< resulting difference image
	Mat thresholdImage;									///< thresholded difference image (for use in findContours() function)

public:
	VideoCapture getVideo();
	Mat Processing(VideoCapture, Mat, Mat);
	void tagging(Rect objectBoundingRectangle, Mat & cameraFeed);
	void searchForMotion(Mat thresholdImage, Mat & cameraFeed);
	bool controlLoop(bool, bool);
};
#endif /* INCLUDE_MOTIONTRACKER_HPP_ */