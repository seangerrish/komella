#ifndef __CODE_LAYOUT_CONSTRUCTOR_H__
#define __CODE_LAYOUT_CONSTRUCTOR_H__

#include <opencv2/core/core.hpp>
#include <deque>

namespace cv {
  // class Mat;
}

using std::pair;
using std::deque;
using cv::Mat;

namespace komella {

typedef pair<int, Mat*> TimestampFrame;

class Background {
 public:
  Background();

  void SubtractBackground(Mat* image,
			  Mat** foreground);

  // Does not take ownership of background.
  void AddBackgroundImage(Mat* background);

 private:
  void SelectBackgroundImage();

  // Keeps track of log2(N) background images,
  // for log2(N) up to 10.
  deque<TimestampFrame> background_images_;

  Mat* background_image_;

  int number_frames_processed;
};

}

#endif // __CODE_LAYOUT_CONSTRUCTOR_H__
