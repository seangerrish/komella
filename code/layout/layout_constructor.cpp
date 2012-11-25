#include "layout/layout_constructor.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdio.h>
#include <math.h>

#include <vector>
#include <deque>

using std::vector;
using std::deque;
using std::log10;
using namespace cv;

namespace komella {

Background::Background()
  : background_images_(),
    background_image_(NULL),
    number_frames_processed(0) {
}

void Background::SubtractBackground(Mat* image,
				    Mat** foreground) {
  if (!background_image_) {
    return;
  }
  imshow("foo", *image);
  imshow("bar", *background_image_);
  // not bgr.
  // cvtColor(*image, *image, CV_BGR2YCrCb);
  // cvtColor(*image, *image, CV_BGR2YCrCb);
  // cvtColor(*image, *image, CV_RGB2YCrCb);
  // cvtColor(*image, *image, CV_BGR2YCrCb);
  // cvtColor(*background, *background, CV_BGR2YCrCb);
  // cvtColor(*background, *background, CV_RGB2YCrCb);
  // imshow("foo_ycrcb", *image);

  Mat distance = Mat::zeros(image->size(), CV_32F);

  vector<Mat> fgChannels;
  split(*image, fgChannels);
  
  vector<Mat> bgChannels;
  split(*background_image_, bgChannels);

  for(size_t i = 0; i < fgChannels.size(); i++) {
    Mat temp = abs(fgChannels[i] - bgChannels[i]);
    temp.convertTo(temp, CV_32F);
    distance = distance + temp;
    /*printf("temp %d.", i);
    for (int j=0; j < 10; ++j) {
      for (int k=0; k < 10; ++k) {
	printf("%.4f ", distance.at<double>(j, k));
      }
    }
    */
  }

  delete *foreground;
  *foreground = new Mat;
  threshold(distance, **foreground, 32, 255, THRESH_BINARY);
  //  **foreground = (**foreground) + (*image);

  // cout << "distance" << endl;
  // cout << distance << endl;
  // rows, cols
  /*for (int i=0; i < 10; ++i) {
    for (int j=0; j < 10; ++j) {
      printf("%.4f ", distance.at<double>(i, j));
      //printf("%.4f ", distance.at<double>(50, 50));
    }
    printf("\n");
  }
  */

  printf("type: %d \n", image->type());
  printf("type: %d \n", distance.type());
  printf("begin.\n");
  /*  for (int i=0; i < 10; ++i) {
    for (int j=0; j < 10; ++j) {
      printf("%.4f ", image->at<double>(i, j));
      printf("%d ", image->at<int>(i, j));
      //printf("%.4f ", distance.at<double>(50, 50));
    }
    printf("\n");
  }
  */

  //Mat kernel5x5 = getStructuringElement(MORPH_RECT, Size(5, 5));
  //morphologyEx(**foreground, **foreground, MORPH_OPEN, kernel5x5);
  
  imshow("fg", *image);
  imshow("bg", *background_image_);
  imshow("mask", **foreground);
  
  waitKey( 2 );
}

void Background::AddBackgroundImage(Mat* background) {
  // First, add the new image to the list of background images.
  Mat* background_copy = new Mat(background->clone());
  background_images_.push_front(pair<int, Mat*>(number_frames_processed++, background_copy));
  
  // Next, clean up old images.
  // Don't allow more than about 20 frames.
  /*
  int count = 20;
  printf("length of images is: %d\n", background_images_.size());
  for (deque<TimestampFrame>::iterator it = background_images_.begin();
       it < background_images_.end();
       ++it) {
    printf("%d %.3f ", count,
	   log10(number_frames_processed - (*it).first) / log10(2.));
    if (((count < log10(number_frames_processed - (*it).first) / log10(2.))
	 || count < 2)
	&& background_images_.size() >= 2) {
      Mat* to_delete = (*it).second;
      background_images_.erase(it);

      it = background_images_.begin();
      count = 21;
      
      delete to_delete;
    }
    count -= 1;
  }

  */
  int last_timestamp = 0;
  for (deque<TimestampFrame>::iterator it = background_images_.begin();
       it < background_images_.end();
       ++it) {
    if (background_images_.size() < 18) {
      break;
    }
    
    int min_distance_between_frames = (number_frames_processed / 20);

    if (number_frames_processed - (*it).first > 5000000
	|| abs(((*it).first) - last_timestamp) < min_distance_between_frames) {
      Mat* to_delete = (*it).second;
      background_images_.erase(it);

      it = background_images_.begin();
      
      delete to_delete;
    }
    last_timestamp = (*it).first;
  }

  for (deque<TimestampFrame>::iterator it = background_images_.begin();
       it < background_images_.end();
       ++it) {
    printf("%d ", (*it).first);
  }
  printf("\n");

  printf("length of images is: %d\n", background_images_.size());
  SelectBackgroundImage();
}

void Background::SelectBackgroundImage() {
  // Select a background image using the average value of the
  // existing background images.
  if (background_images_.empty()) {
    return;
  }
  
  Mat* new_background = NULL;
  const int image_count = background_images_.size();
  for (deque<TimestampFrame>::iterator it = background_images_.begin();
       it < background_images_.end();
       ++it) {
    Mat* image = (*it).second;
    if (new_background == NULL) {
      new_background = new Mat(image->clone());
      *new_background = *new_background / image_count;
    } else {
      *new_background = (*new_background) + (1. / image_count) * (*image);
    }
  }
  
  Mat* tmp = background_image_;
  background_image_ = new_background;
  delete tmp;
}

}
