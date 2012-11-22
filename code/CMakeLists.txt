# project( DisplayImage )
# find_package( OpenCV REQUIRED )
# add_executable( DisplayImage demo/DisplayImage.cpp )
# target_link_libraries( DisplayImage ${OpenCV_LIBS} )

project( GrayImage )
find_package( OpenCV REQUIRED )
add_executable( GrayImage demo/read_image.cpp )
target_link_libraries( GrayImage ${OpenCV_LIBS} )

project( webcam_example )
find_package( OpenCV REQUIRED )
add_executable( webcam_example demo/webcam_example.cpp )
target_link_libraries( webcam_example ${OpenCV_LIBS} )

project( video_write )
find_package( OpenCV REQUIRED )
add_executable( video_write demo/video-write.cpp )
target_link_libraries( video_write ${OpenCV_LIBS} )

project( video_write_webcam )
find_package( OpenCV REQUIRED )
add_executable( video_write_webcam demo/video-write-webcam.cpp )
target_link_libraries( video_write_webcam ${OpenCV_LIBS} )

project( komella )
find_package( OpenCV REQUIRED )
include_directories( $CMAKE_INCLUDE_PATH )
include_directories( /home/sgerrish/insight/komella/code )
add_executable( komella demo/demo.cpp time_series_state/stream_processor.cpp )
find_package(Boost REQUIRED)
target_link_libraries( komella
  ${OpenCV_LIBS}
  "/usr/lib/libboost_thread.so"
)
