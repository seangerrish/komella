#include <stl/vector.h>

#include <opencv2/core/core.hpp>

void SubtractBackground(const Mat* image,
			const Mat* background,
			Mat** foreground) {
  cvtColor(*image, *image, CV_RGB2YCrCb);
  cvtColor(*background, *background, CV_RGB2YCrCb);

  Mat distance = Mat::zeros(fg.size(), CV_32F);

  vector<Mat> fgChannels;
  split(*image, fgChannels);
  
  vector<Mat> bgChannels;
  split(*background, bgChannels);

  for(size_t i = 0; i < fgChannels.size(); i++) {
    Mat temp = abs(fgChannels[i] - bgChannels[i]);
    temp.convertTo(temp, CV_32F);
    
    distance = distance + temp;
  }

  *foreground = new Mat;
  threshold(distance, **foreground, 35, 255, THRESH_BINARY);
    
  Mat kernel5x5 = getStructuringElement(MORPH_RECT, Size(5, 5));
  morphologyEx(**foreground, foreground, MORPH_OPEN, kernel5x5);
  
  imshow("fg", *image);
  imshow("bg", *background);
  imshow("mask", **mask);
  
  waitKey();
}
