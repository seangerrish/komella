#include <iostream>	// for standard I/O
#include <string>   // for strings
#include <stdio.h>

#include "time_series_state/stream_processor.h"
#include "time_series_state/stream.h"

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using komella::StreamProcessor;
using komella::InputStream;
using komella::OutputStream;

using namespace std;
using namespace cv;

int main(int n, char** c, char* window_name) {
  InputStream input_stream;
  OutputStream output_stream;

  printf("starting camera.\n");
  input_stream.StartCamera();

  printf("starting processor.\n");
  StreamProcessor processor(&input_stream,
			    &output_stream); 
  printf("sleeping for 1 seconds.\n");
  printf("initializing state..\n");

  processor.InitializeState();
  processor.Start();
  sleep(10);

  printf("Halting.\n");
  // input_stream.StopCamera();
  input_stream.interrupt();
  input_stream.join();
  printf("Interrupted.\n");

  return 0;
}
