# project( DisplayImage )
# find_package( OpenCV REQUIRED )
# add_executable( DisplayImage demo/DisplayImage.cpp )
# target_link_libraries( DisplayImage ${OpenCV_LIBS} )

project( GrayImage )
find_package( OpenCV REQUIRED )
add_executable( GrayImage demo/read_image.cpp )
target_link_libraries( GrayImage ${OpenCV_LIBS} )