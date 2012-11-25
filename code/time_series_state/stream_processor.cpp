#include "stream_processor.h"

#include "layout/layout_constructor.h"
//#include "time_series_state/stream_processor.h"
using boost::thread;

namespace komella {

  StreamProcessor::StreamProcessor(InputStream* input_stream,
				   OutputStream* output_stream)
  : initialized_(false),
    background_(new Background()),
    smoothed_image_(NULL),
    foreground_image_(NULL),
    thread_image_(new thread()),
    thread_pose_(new thread()),
    thread_feature_extractor_(new thread()),
    thread_input_stream_(input_stream),
    output_stream_(output_stream) {
}

StreamProcessor::~StreamProcessor() {
  delete background_;
  delete foreground_image_;
  delete thread_image_;
  delete thread_pose_;
  delete thread_feature_extractor_;
}

bool StreamProcessor::HandleOneImage(Pose* last_pose,
				     Pose** new_pose,
				     Mat** foreground_image) {
    // Fetch the most-recent image.
    usleep(1000000 / 32);
    Frame* most_recent_frame = thread_input_stream_->GetLastFrame();
    if (!most_recent_frame) {
      return false;
    }

    Mat* current_image = most_recent_frame->second;
    if (smoothed_image_ == NULL) {
      smoothed_image_ = new Mat(current_image->clone());
    }
    *smoothed_image_ = (0.6 * (*smoothed_image_)
			+ 0.4 * (*current_image));
    (*output_stream_) << smoothed_image_;
    background_->AddBackgroundImage(current_image);

    background_->SubtractBackground(smoothed_image_,
				    &foreground_image_);

    return true;
}

void StreamProcessor::Start() {
  if (!initialized_) {
    InitializeState();
  }

  // Handle 1000 images.
  for (int i = 0; i < 1000; ++i) {
    if (!HandleOneImage(NULL,
			NULL,
			&foreground_image_)) {
      continue;
    }
  }

}

void StreamProcessor::InitializeState() {
  // Start the worker threads.

  // Initialize the model.

  // Note that we're initialized.
  initialized_ = true;
}

void StreamProcessor::EstimateGradients() {
  
}

}
