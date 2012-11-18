#include "stream_processor.h"
//#include "time_series_state/stream_processor.h"
using boost::thread;

namespace komella {

  StreamProcessor::StreamProcessor(InputStream* input_stream,
				   OutputStream* output_stream)
  : initialized_(false),
    background_image_(NULL),
    thread_image_(new thread()),
    thread_pose_(new thread()),
    thread_feature_extractor_(new thread()),
    thread_input_stream_(input_stream),
    thread_output_stream_(output_stream) {
}

void StreamProcessor::Start() {
  if (!initialized_) {
    InitializeState();
  }
  
  for (int i = 0; i < 100; ++i) {
    // Fetch the most-recent image.
    Frame most_recent_frame = thread_input_stream_->GetLastFrame();

    // Update model parameters.
    // TODO(sean)

    // Prepare output.
    

    // Output to the output stream.
    (*output_stream_) << most_recent_frame;

    // Save to disk.
  }

}

void StreamProcessor::InitializeState() {
  // Start the worker threads.

  // Initialize the model.

  // Note that we're initialized.
  initialized_ = true;
}

void StreamProcessor::FindBackgroundImage(InputStream* input) {
  delete background_image_;
  background_image_ = new Mat;
  (*input_stream_)[0]->second->copyTo(background_image_);
}

void StreamProcessor::FindSilhouette(Silhouette* silhouette) {
  for () {
    
  }
}

void StreamProcessor::EstimateGradients() {
  
}

}
