//
// Created by Andrew King on 1/13/22.
//

#include <iostream>
#include <vector>
#include <string>
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

    // create BpmDetector object
    BpmDetector detector;

    return 0;
}