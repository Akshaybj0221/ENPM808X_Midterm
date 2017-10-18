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
*   @file	main.cpp
*   @brief  This is the main file to run the Motion Tracker.
*
*   Run the vision system which tracks motion of the objects
*	Press 't' to start tracking (You can toggle by pressing 't' again)
*	Press 'p' to pause the video
*	Press 'esc' to terminate the program
*
*   @author	Akshay Bajaj
*   @date	2017/10/16
*/




#include"MotionTracker.h"
#include <iostream>
#include "stdafx.h"

using namespace std;

int main()
{
	MotionTracker obj;
	Mat frame1, frame2, thresholdImage;		///< set up the matrices that we will need the two frames we will be comparing
	bool trackingEnabled = false;
	bool pause = false;

	while (1) {

		VideoCapture capture;		///< we can loop the video by re-opening the capture every time the video reaches its last frame

		capture = obj.getVideo();													///< Call Get Video Function

		while (capture.get(CV_CAP_PROP_POS_FRAMES)<capture.get(CV_CAP_PROP_FRAME_COUNT) - 1) {

			capture.read(frame1);			///< read first frame

			capture.read(frame2);			///< copy second frame

			thresholdImage = obj.Processing(capture, frame1, frame2);		///< Call Processing function and get threshold value

			if (trackingEnabled) {									///< if tracking enabled, search for contours in our thresholded image
				obj.searchForMotion(thresholdImage, frame1); 			///< Call searchForMotion function	
			}
			imshow("Frame1", frame1);								///<s how our captured frame

																	///< check to see if a button has been pressed.
			trackingEnabled = obj.controlLoop(trackingEnabled, pause);	///< Call control loop function
		}

		capture.release();						///< release the capture before re-opening and looping again.
	}
	waitKey(0);
	return 0;
}