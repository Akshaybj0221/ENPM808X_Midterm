
//#ifndef MOTIONTRACKER_H_
//#define MOTIONTRACKER_H_


/*
* MotionTracker.h
*
*  Created on: Oct 10, 2017
*      Author: Akshay
*/

#ifndef INCLUDE_MOTIONTRACKER_HPP_
#define INCLUDE_MOTIONTRACKER_HPP_
#include "/home/viki/Desktop/OpenCV/opencv-3.2.0/include/opencv2/opencv.hpp"
using namespace cv;


class MotionTracker {
protected:
	const static int SENSITIVITY_VALUE = 20;
	const static int BLUR_SIZE = 10;
	int theObject[2] = { 0,0 };
	Rect objectBoundingRectangle = Rect(0, 0, 0, 0);
	bool objectDetected = false;						//some boolean variables for added functionality
	bool trackingEnabled = false;
	bool pause = false;									//pause and resume code
	Mat frame1, frame2;									//set up the matrices that we will need the two frames we will be comparing
	Mat grayImage1, grayImage2;							//their grayscale images (needed for absdiff() function)
	Mat differenceImage;								//resulting difference image
	Mat thresholdImage;									//thresholded difference image (for use in findContours() function)

public:
	VideoCapture getVideo();
	Mat Processing(VideoCapture, Mat, Mat);
	void tagging(Rect objectBoundingRectangle, Mat & cameraFeed);
	void searchForMotion(Mat thresholdImage, Mat & cameraFeed);
	bool controlLoop(bool, bool);
};
#endif /* INCLUDE_MOTIONTRACKER_HPP_ */

