#ifndef TIME_SERIES_STATE__STREAM_H__
#define TIME_SERIES_STATE__STREAM_H__

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>
#include <stdio.h>
#include <deque>

using namespace std;
using namespace cv;
using boost::posix_time::milliseconds;
using boost::thread;

namespace komella {

typedef pair<int, Mat*> Frame;
typedef deque<Frame> FrameList;
class InputStream;

class InputStream : public thread {
 public:
  static void RunForever(InputStream* instance,
			 CvCapture** capture,
			 bool* active,
			 FrameList** frames_in,
			 boost::mutex* lock) {
    IplImage* captured;
    Mat* copy;
    int count = 1;
    boost::this_thread::interruption_enabled();
    while (true) {
      if (count % 100000 == 0) {
	printf("count...%d, %d\n", count, *active);
      }
      count += 1;
      if (boost::this_thread::interruption_requested()) {
	printf("internal thread halting.\n");
	break;
      }
      if (count > 1000000) {
	boost::this_thread::yield();
	break;
      }
      if (!*active) {
	// frames and capture are not ready until 
	// active_ is true.
	instance->yield();
	// printf("yielding until ready.\n");
	continue;
      }
      FrameList& frames = **frames_in;

      captured = cvQueryFrame(*capture);
      if (captured == NULL) {
	printf("Fail.\n");
	instance->yield();
	continue;
      } else {
	printf("interruption enabled: %d\ninterrupted: %d\n",
	       boost::this_thread::interruption_enabled(),
	       boost::this_thread::interruption_requested());
	printf("Succeed.\n");
      }

      copy = new Mat(captured, true);
      if (frames.size() % 11 == 0) {
	printf("iteration %d\n", frames.size());
      }
      lock->lock();
      frames.push_back(Frame(frames.size(),
			     copy));
      if (frames.size() > 25) {
	copy = frames[0].second;
	delete copy;
	frames.pop_front();
      }
      lock->unlock();
    
      instance->yield();
    }
  }

  static void DoNothing() { }

  InputStream()
    : frames_(new FrameList()),
      capture_(cvCaptureFromCAM(CV_CAP_ANY)),
      active_(false),
      thread(RunForever,
	     this,
	     &capture_,
	     &active_,
	     &frames_,
	     &lock_) {
    active_ = true;
  }

  ~InputStream() {
    printf("deleting object.\n");
    for (int i=0; i < frames_->size(); ++i) {
      delete (*frames_)[i].second;
    }
    delete frames_;
    cvReleaseCapture(&capture_);
  }

  Frame operator[] (int i) {
    return (*frames_)[i];
  }

  // Returns a pointer reference to the last frame.
  Frame* GetLastFrame() {
    if (frames_->size()) {
      return &(frames_->back());
    }
    return NULL;
  }

  void StopCamera() {
    active_ = false;
  }

  void StartCamera() {
    active_ = true;
  }

 private:
  boost::mutex lock_;

  bool active_;
    
  CvCapture* capture_;

  // A vector with time millis and Mat*s.
  FrameList* frames_;

};


class OutputStream {
 public:
  OutputStream()
    : displayed_image_() {
    cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
  }

  ~OutputStream() {
    cvDestroyWindow("result");
  }

  // Output a pointer of this Mat to the output stream.  The contents
  // of mat are copied to the video buffer, so the caller maintains
  // ownership of mat.
  void operator <<(Mat* mat) {
    printf("Displaying..\n");

    displayed_image_ = mat->clone();
    cvShowImage("result", &displayed_image_);
    if( waitKey( 2 ) >= 0 ) {
      return;
    }

  }

 private:
  boost::mutex lock_;

  // Saved as long as the image is displayed.
  IplImage displayed_image_;

  // A vector with time millis and Mat*s.
  FrameList* frames_;

};


}

#endif
