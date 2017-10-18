set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    test.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cpp-test PUBLIC gtest)

cmake_minimum_required(VERSION 2.8)
project( MotionTracker )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( MotionTracker ~/ENPM808X_Midterm/include/MotionTracker.cpp )
target_link_libraries( MotionTracker ${OpenCV_LIBS} )

target_link_libraries(main opencv_core opencv_highgui)