#ifndef TIME_SERIES_STATE__STREAM_PROCESSOR_H__
#define TIME_SERIES_STATE__STREAM_PROCESSOR_H__

#include <boost/thread/thread.hpp>

//class Thread;
#include "stream.h"
#include "layout/layout_constructor.h"
#include <boost/thread.hpp>

using boost::thread;

namespace komella {

class Pose;
class Inference;
class Hypothesis;

class Silhouette;

class StreamProcessor {
 public:
  StreamProcessor(InputStream* input_stream,
		  OutputStream* output_stream);

  ~StreamProcessor();

  void Start();

  void InitializeState();

  // Sets the background image using the back of frames_;
  // Returns true if successful.
  bool SetBackgroundImage();

  bool HandleOneImage(Pose* last_pose,
		      Pose** new_pose,
		      Mat** foreground_image_);

 private:
  bool initialized_;
  
  // Manages the background image.
  Background* background_;

  // Saved as long as the image is displayed.
  Mat* foreground_image_;

  Mat* smoothed_image_;

  thread* thread_image_;

  InputStream* thread_input_stream_;

  thread* thread_pose_;

  thread* thread_feature_extractor_;

  OutputStream* output_stream_;

  Pose* pose_;
  
  void EstimateGradients();
};

}


#endif
