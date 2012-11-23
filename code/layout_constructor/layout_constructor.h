#ifndef __CODE_LAYOUT_CONSTRUCTOR_H__
#define __CODE_LAYOUT_CONSTRUCTOR_H__

#include <opencv2/core/core.hpp>

void SubtractBackground(const Mat* image,
			const Mat* background,
			Mat** foreground);

#endif // __CODE_LAYOUT_CONSTRUCTOR_H__
