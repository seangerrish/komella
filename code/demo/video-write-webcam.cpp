#include <iostream>	// for standard I/O
#include <string>   // for strings
#include <stdio.h>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>



using namespace std;
using namespace cv;

void help() {
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "This program shows how to write video files. You can extract the R or G or B color channel "
        << " of the input video.write "  << endl
        << "Usage:"                                                               << endl
        << "./video-write inputvideoName [ R | G | B] [Y | N]"                   << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}

void CaptureWebcam(Mat** frames, int* number_frames) {
    CvCapture* capture = NULL;
    Mat frame, frameCopy, image;

    *frames = new Mat[100];
    *number_frames = 100;

    // 0=default, -1=any camera, 1..99=your camera
    capture = cvCaptureFromCAM( CV_CAP_ANY );
    if (!capture) {
      cout << "No camera detected" << endl;
    }
    
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
    
    const int MAX_FRAMES = 50;
    if (capture) {
      cout << "In capture ..." << endl;
      for(int i=0; i < MAX_FRAMES; ++i) {
	if (i % 10 == 0) {
	  cout << "iteration" << i << endl;
	}
	IplImage* iplImg = cvQueryFrame( capture );
	frame = iplImg;
	frame.copyTo((*frames)[i]);

	if( frame.empty() ) {
	  break;
	}
	
	if( iplImg->origin == IPL_ORIGIN_TL ) {
	  frame.copyTo(frameCopy);
	} else {
	  flip(frame, frameCopy, 0);
	}

	cvShowImage( "result", iplImg );
	
	if( waitKey( 10 ) >= 0 ) {
	  break;
	  *number_frames = i;
	}
      }
      
    }
    cvReleaseCapture( &capture );
    cvDestroyWindow( "result" );
}

int main(int argc, char *argv[], char *window_name)
{
  int number_frames = 0;
  Mat* frames = NULL;
  CaptureWebcam(&frames, &number_frames);

  if (number_frames == 0) {
    cout << "No frames to process.  Exiting." << endl;
    return 0;
  }

  cout << "Processing video with" << number_frames << "frames." << endl;

  const string NAME = "saved_video.avi";
  int ex = CV_FOURCC('D','I','V','X');
  
  // Transform from int to char via Bitwise operators
  char EXT[] = {ex & 0XFF , (ex & 0XFF00) >> 8,(ex & 0XFF0000) >> 16,(ex & 0XFF000000) >> 24, 0};

  // Open the output
  VideoWriter outputVideo;
  outputVideo.open(NAME.c_str(), ex=ex, 30 /* fps */, frames[0].size(), true);
  cout << "name" << NAME << endl;
  cout << "ex" << " " << ex << endl;
  cout << "frames[0].size()" << frames[0].size() << endl;

  if (!outputVideo.isOpened()) {
    cout  << "Could not open the output video for write." << endl;
    return -1;
  }
  
  union { int v; char c[5];} uEx ;
  uEx.v = ex;                              // From Int to char via union
  uEx.c[4]='\0';
  
  int channel = 2;    // Select the channel to save
  switch('R') {
  case 'R' : {channel = 2; break;}
  case 'G' : {channel = 1; break;}
  case 'B' : {channel = 0; break;}
  }
  Mat src, res;
  vector<Mat> spl;
  
  // Show the image captured in the window and repeat
  for (int i=0; i < number_frames; ++i) {
    src = frames[i];              // read
    if( src.empty()) break;         // check if at end
    
    // Process - extract only the correct channel
    split(src, spl);
    for( int i =0; i < 3; ++i) {
      if (i != channel) {
	spl[i] = Mat::zeros(frames[0].size(), spl[0].type());
      }
    }
    merge(spl, res);
    
    //outputVideo.write(res); //save or
    outputVideo << res;
  }

  cout << "Finished writing" << endl;
  return 0;
}
