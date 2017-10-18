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
*   @file	MotionTracker.cpp
*   @brief  This is the file where all the variables and funtions are defined
*
*   @author	Akshay Bajaj
*   @date	2017/10/14
*/



#include "stdafx.h"
#include <opencv/highgui.h>
#include <iostream>
#include <stdlib.h>
#include "MotionTracker.h"
using namespace std;


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

VideoCapture MotionTracker::getVideo() {

	VideoCapture get;								///< video capture object.
	get.open("bouncingBall.avi");				///< adding video file

	if (!get.isOpened()) {
		cout << "ERROR ACQUIRING VIDEO FEED\n";
		getchar();
		return -1;
	}
	return get;
}


Mat MotionTracker::Processing(VideoCapture capture, Mat frame1, Mat frame2) {

	Mat grayImage1, grayImage2;							///< their grayscale images (needed for absdiff() function)

	Mat differenceImage;								///< resulting difference image

	Mat thresholdImage;									///< thresholded difference image (for use in findContours() function)

	cv::cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);			///< convert frame1 to gray scale for frame differencing

	cv::cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);			///< convert frame2 to gray scale for frame differencing

	cv::absdiff(grayImage1, grayImage2, differenceImage);			///< perform frame differencing with the sequential images. This will output an "intensity image"
																	///< do not confuse this with a threshold image, we will need to perform thresholding afterwards.

	cv::threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);			///< threshold intensity image at a given sensitivity value

	cv::blur(thresholdImage, thresholdImage, cv::Size(BLUR_SIZE, BLUR_SIZE));			///< blur the image to get rid of the noise. This will output an intensity image

	cv::threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);			///< threshold again to obtain binary image from blur output

	return thresholdImage;
}


void MotionTracker::tagging(Rect objectBoundingRectangle, Mat &cameraFeed) {
	int xpos = objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
	int ypos = objectBoundingRectangle.y + objectBoundingRectangle.height / 2;

	///< update the objects positions by changing the 'theObject' array values
	theObject[0] = xpos, theObject[1] = ypos;
	///< make some temp x and y variables so we dont have to type out so much
	int x = theObject[0];
	int y = theObject[1];

	///< draw some crosshairs around the object
	circle(cameraFeed, Point(x, y), 20, Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);

	///< write the position of the object to the screen
	putText(cameraFeed, "Tracking object at (" + std::to_string(x) + "," + std::to_string(y) + ")", Point(x, y), 1, 1, Scalar(255, 0, 0), 2);
}


void MotionTracker::searchForMotion(Mat thresholdImage, Mat &cameraFeed) {
	///< notice how we use the '&' operator for objectDetected and cameraFeed. This is because we wish
	///< to take the values passed into the function and manipulate them, rather than just working with a copy.
	///< eg. we draw to the cameraFeed to be displayed in the main() function.
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	///< these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	///< find contours of filtered image using openCV findContours function
	///< findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );// retrieves all contours
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);// retrieves external contours

	if (contours.size() > 0)objectDetected = true;		///< if contours vector is not empty, we have found some objects
	else objectDetected = false;

	if (objectDetected) {
		///< the largest contour is found at the end of the contours vector
		///< we will simply assume that the biggest contour is the object we are looking for.
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size() - 1));
		///< make a bounding rectangle around the largest contour then find its centroid
		///< this will be the object's final estimated position.
		objectBoundingRectangle = boundingRect(largestContourVec.at(0));
		tagging(objectBoundingRectangle, cameraFeed);
	}
}


bool MotionTracker::controlLoop(bool trackingEnabled, bool pause) {

	///< this 10ms delay is necessary for proper operation of this program
	///< if removed, frames will not have enough time to referesh and a blank 
	///< image will appear.
	switch (waitKey(10)) {

	case 27:																///< 'esc' key has been pressed, exit program.
		exit(EXIT_FAILURE);
	case 116:																///< 't' has been pressed. this will toggle tracking
		trackingEnabled = !trackingEnabled;
		if (trackingEnabled == false) cout << "Tracking disabled." << endl;
		else cout << "Tracking enabled." << endl;
		break;
	case 112:																///< 'p' has been pressed. this will pause/resume the code.
		pause = !pause;
		if (pause == true) {
			cout << "Code paused, press 'p' again to resume" << endl;
			while (pause == true) {
				///< stay in this loop until 
				switch (waitKey()) {
				case 112:
					///< change pause back to false
					pause = false;
					cout << "Code Resumed" << endl;
					break;
				}
			}
		}
	}
	return trackingEnabled;
}
