cmake_minimum_required(VERSION 2.8.12)
project( ParallelMotionDetection )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable( FrameTa experiments/FrameTa.cpp )
target_compile_options( FrameTa PRIVATE -O3 -Wall )
target_link_libraries( FrameTa ${OpenCV_LIBS} )

add_executable( BlackWhite experiments/BlackWhite.cpp )
target_compile_options( BlackWhite PRIVATE -O3 -Wall )
target_link_libraries( BlackWhite ${OpenCV_LIBS} )

add_executable( Conv experiments/Conv.cpp )
target_compile_options( Conv PRIVATE -O3 -Wall )
target_link_libraries( Conv ${OpenCV_LIBS} )