#ifndef TIME_SERIES_STATE__STREAM_H__
#define TIME_SERIES_STATE__STREAM_H__

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;
using namespace cv;

namespace komella {

typedef pair<int, Mat*> Frame;
typedef deque<Frame> FrameList;

class InputStream : public boost::thread {
 public:
  static void RunForever(CvCapture* capture,
			 bool* active,
			 FrameList* frames,
			 boost::mutex* lock) {
    while (active) {
      Mat* image = new Mat(cvQueryFrame(capture));
      lock->lock();
      frames->push_back(Frame(frames->size(),
			      image));
      lock->unlock();
    }
  }

  InputStream()
    : frames_(new FrameList()),
      capture_(cvCaptureFromCAM(CV_CAP_ANY)),
      active_(false),
      boost::thread(RunForever, capture_,
		    &active_,
		    frames_,
		    &lock_) {
  }

  ~InputStream() {
    lock_.lock();
    for (int i=0; i < frames_->size(); ++i) {
      delete (*frames_)[i].second;
    }
    delete frames_;
    lock_.unlock();

    cvReleaseCapture(&capture_);
  }

  Frame GetLastFrame() {
    return *frames_->end();
  }

  void StopCamera() {
    active_ = false;
  }

  void StartCamera();

 private:
  boost::mutex lock_;

  bool active_;
    
  CvCapture* capture_;

  // A vector with time millis and Mat*s.
  FrameList* frames_;

};


class OutputStream {
 public:
  OutputStream() {
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
  }

  ~OutputStream() {
    cvDestroyWindow("result");
  }

  void operator <<(Mat* mat) {
    cvShowImage("result", mat);
  }

  void StopCamera();

  void StartCamera();

 private:
  boost::mutex lock_;
    
  // A vector with time millis and Mat*s.
  FrameList* frames_;

};


}

#endif
