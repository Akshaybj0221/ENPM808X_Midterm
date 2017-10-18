/********************************************************************
*                                                                  *
* Copyright (C) 2017 by Akshay Bajaj                              *
*                                                                  *
********************************************************************/


/** @file test.cpp
*  @brief Implementation of unit test for Motion Tracker
*
*  This file contains implementation of unit test for
*  MotionTracker.
*
*  @author Akshay Bajaj
*  @date   2017/10/10
*/

#include <gtest/gtest.h>
#include "MotionTracker.h"

/**
*   @brief  Test the getVideo parameter function of
*           MotionTracker
*
*   @param  none
*   @return get
*/
TEST(testGetVideoreturnValue, should_not_be_null) {
	MotionTracker mt;
	VideoCapture val = mt.getVideo();
	val = 0;
	ASSERT_TRUE(val = 0);
}


/**
*   @brief  Test the Processing parameter function of
*           MotionTracker
*
*   @param  capture, frame1, frame2
*   @return thresholdImage
*/
TEST(testProcessing, return_value_notNull) {
	MotionTracker mt;
	VideoCapture capture;
	Mat frame1;
	Mat frame2;
	Mat val;
	val = mt.Processing(capture, frame1, frame2);
	ASSERT_TRUE(val > 0);
}
