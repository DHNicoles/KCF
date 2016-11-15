#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "kcftracker.hpp"



using namespace std;
using namespace cv;

int main(int argc, char* argv[]){



	bool HOG = true;
	bool FIXEDWINDOW = false;
	bool MULTISCALE = true;
	bool SILENT = true;
	bool LAB = false;

	/*for(int i = 0; i < argc; i++){
		if ( strcmp (argv[i], "hog") == 0 )
			HOG = true;
		if ( strcmp (argv[i], "fixed_window") == 0 )
			FIXEDWINDOW = true;
		if ( strcmp (argv[i], "singlescale") == 0 )
			MULTISCALE = false;
		if ( strcmp (argv[i], "show") == 0 )
			SILENT = false;
		if ( strcmp (argv[i], "lab") == 0 ){
			LAB = true;
			HOG = true;
		}
		if ( strcmp (argv[i], "gray") == 0 )
			HOG = false;
	}*/
	
	// Create KCFTracker object
	KCFTracker tracker(HOG, FIXEDWINDOW, MULTISCALE, LAB);

	// Frame readed
	Mat frame;

	// Tracker results
	Rect result;

	// Frame counter
	int nFrames = 0;

	// set input video
	std::string video = "K:\\ÈËÈº\\2082-3_70.mov";
	VideoCapture cap(video);

	// get bounding box
	cap >> frame;
	cap >> frame;
	cap >> frame;

	while (!frame.empty()){
		resize(frame, frame, Size(768, 432));
		// First frame, give the groundtruth to the tracker
		if (nFrames == 0) {
			tracker.init( Rect(210, 300, 40, 40), frame );
			rectangle(frame, Rect(57, 188, 88, 80), Scalar(0, 255, 255), 1, 8);

		}
		// Update
		else{
			result = tracker.update(frame);
			rectangle( frame, Point( result.x, result.y ), Point( result.x+result.width, result.y+result.height), Scalar( 0, 255, 255 ), 1, 8 );
			
		}

		nFrames++;

		imshow("Image", frame);
		waitKey(10);
		cap >> frame;
		resize(frame, frame, Size(768, 432));
	}


}
