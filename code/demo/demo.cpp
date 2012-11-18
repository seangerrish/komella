#include "time_series_state/stream_processor.h"
#include "time_series_state/stream.h"

using komella::StreamProcessor;
using komella::InputStream;
using komella::OutputStream;

int main(int n, char** c) {
  InputStream input_stream;
  OutputStream output_stream;

  StreamProcessor processor(&input_stream,
			    &output_stream);

  processor.InitializeState();
  processor.Start();

  return 0;
}
