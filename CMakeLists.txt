cmake_minimum_required(VERSION 3.21)
project(BpmDetector)

set(CMAKE_CXX_STANDARD 14)

add_executable(BpmDetector
        source/main.cpp source/BpmDetector.cpp source/BpmDetector.h source/AudioFile.h)
