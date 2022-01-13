//
// Created by Andrew King on 1/13/22.
//

#include <iostream>
#include <vector>
#include <chrono>
#include "AudioFile.h"
#include "BpmDetector.h"

int main(int argc, char* argv[])
{
    // get filepath from args
    std::string filepath = argv[1];

    // construct AudioFile object and load song
    AudioFile<float> audio;
    audio.load(filepath);
    // copy samples to 2d vector
    std::vector<std::vector<float> > mysamples = audio.samples;

    auto start = std::chrono::system_clock::now(); //DBG

    // create BpmDetector object
    BpmDetector detector;
    detector.setAudio(mysamples);
    float bpm = detector.detectBpm();
    std::cout << "BPM = " << bpm << std::endl;

    //DBG
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
    //DBG

    return 0;
}