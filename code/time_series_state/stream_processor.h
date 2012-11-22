#ifndef TIME_SERIES_STATE__STREAM_PROCESSOR_H__
#define TIME_SERIES_STATE__STREAM_PROCESSOR_H__

#include <boost/thread/thread.hpp>

//class Thread;
#include "stream.h"
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

  void Start();

  void InitializeState();

 private:
  bool initialized_;
  
  Mat* background_image_;

  thread* thread_image_;

  InputStream* thread_input_stream_;

  thread* thread_pose_;

  thread* thread_feature_extractor_;

  OutputStream* output_stream_;

  Pose* pose_;
  
  void FindBackgroundImage(InputStream* input);

  void FindSilhouette(Silhouette* silhouette);

  void EstimateGradients();
};

}


#endif
