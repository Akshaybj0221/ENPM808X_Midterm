# C++ Boilerplate
[![Build Status](https://travis-ci.org/Akshaybj0221/ENPM808X_Midterm.svg?branch=master)](https://travis-ci.org/Akshaybj0221/ENPM808X_Midterm)
[![Coverage Status](https://coveralls.io/repos/github/Akshaybj0221/ENPM808X_Midterm/badge.svg)](https://coveralls.io/github/Akshaybj0221/ENPM808X_Midterm)
---

##Google Spreadsheets Links Below:

The link to the defect log, time log, product backlog, Iteration backlog, release backlog table are as follows:

Product Backlog: https://docs.google.com/spreadsheets/d/1ARE-m1TVrMjwP5QnjJDIy7vjO3YFEOjuipjcBgkJD4w/edit?usp=sharing

Iteration Backlog: https://docs.google.com/spreadsheets/d/1hsRM5sYC3laXD_c4UtU0Pys1ZRHazFw-7FRlQcmtSgg/edit?usp=sharing

Release Backlog Table: https://docs.google.com/spreadsheets/d/1CuWvDiuVYU89Ndl6akPYEkMMkhjtW8jLH_CkdJijKRQ/edit?usp=sharing


Time Log: https://docs.google.com/spreadsheets/d/1ZnZWze3-v8BWkhG6UbG-DKi6_Gh3Hk_-zbDt4oEi1Eo/edit?usp=sharing

Defect Log: https://docs.google.com/spreadsheets/d/1d6eSZiVCmlSMt_dPw7nbapbw6CTz7TilsnyG3huVssA/edit?usp=sharing


## Overview

C++ based Motion Tracking vision system software:

This project is a vision system developed for the robot to track any moving object which is in the scope of robots camera periphery. There are so many applications to this project such as for intelligent planning of robot trajectory, survellience system, object tracking, movement tracking systems etc.

## Purpose
The purpose of this project is to impart the robot the capability to get some information about the motion of any object. This module can be further integrated with the robots motion planning module to help the robot plan its movement intelligently, relying less on other sensors and more on the vision system analogous to humans.

This type of module can also be integrated in many different security systems such as in surveillance cameras which are used to make sure whether an item is in its position or not (like a briefcase or a projectile).

## Main Features
The main features of the software are as follows:

- Real time motion detection.
- Real time motion tracking that can detect and track moving object
continuously.
- Marking and tagging of the moving object within the video feed.
- A standalone module which can be interfaced with different modules of the robot for further applications.
- Use of OpenCV and not ROS which makes software's integrated effective.

## Results

The software is very effective and fast in tracking any tagging motion simultaneously.
Its funtionality has been tested on multiple test videos and software has a success rate of 98%.

The working output of the software can be seen in the output folder of the repository or the link below:
https://github.com/Akshaybj0221/ENPM808X_Midterm.git

## License

MIT License

Copyright (c) [2017] [Akshay Bajaj]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Dependencies
This software needs external dependencies such as OpenCV. In order to add those dependencies, follow following instructions:

- Open the project in Eclipse.
- We have to tell OpenCV where the OpenCV headers and libraries are. For this, do the following:
- Go to Project–>Properties
- In C/C++ Build, click on Settings. At the right, choose the Tool Settings Tab. Here we will enter the headers and libraries info:
- In GCC C++ Compiler, go to Includes. In Include paths(-l) you should include the path of the folder where opencv was installed. In our example, this is /usr/local/include/opencv.
- Now go to GCC C++ Linker,there you have to fill two spaces:
- First in Library search path (-L) you have to write the path to where the opencv libraries reside, in my case the path is: /usr/local/lib
- Then in Libraries(-l) add the OpenCV libraries that you may need. Usually just the 3 first on the list below are enough (for simple applications) 
- Now you are done. Click OK
- Your project should be ready to be built. For this, go to Project->Build all
- If you check in your folder, there should be an executable there.
- Put the video file in the same directory as source file and Run.

For more queries check this link: https://docs.opencv.org/2.4/doc/tutorials/introduction/linux_eclipse/linux_eclipse.html#using-opencv-with-eclipse-plugin-cdt 

## How to build

- clone the project from the given github repository "https://github.com/Akshaybj0221/ENPM808X_Midterm.git".
- go in the project directory
- open terminal
- write cmake .
- write make

## How to run demo
- Run shell-app OR Run main.cpp from the app folder using the cpp executable command.

## How to run tests
- Run test.cpp in the ubuntu terminal from the test folder.
- The readme shows the test rate using travis.

## How to generate doxygen documentation
- Open terminal
- Install doxygen wizard in ubuntu using .
- Write doxywizard
- GUI will open, add the directory where you want the files to be generated and the project source directory.
- Press run wizard and the files will be generated.

- The doxygen files can be found in the folder "docs".

## Standard install via command-line
```
git clone --recursive https://github.com/dpiet/cpp-boilerplate
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Building for code coverage (for assignments beginning in Week 4)
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

