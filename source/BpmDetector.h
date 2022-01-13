//
// Created by Andrew King on 1/13/22.
//

#ifndef BPMDETECTOR_BPMDETECTOR_H
#define BPMDETECTOR_BPMDETECTOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

typedef struct {
    int id;
    int startSample;
    int endSample;
    int startBlock;
    int endBlock;
    int avgEnergy;
} WindowSpecs;

class BpmDetector {
public:
    BpmDetector(int samplesPerBlock=1024, int blocksPerWindow=40);
    float computeBlockEnergy(int blockNum);
    //================================================================
    // Getters & Setters
    void setAudio(std::vector<std::vector<float> > &audio);
    int getSamplesPerBlock();
    int getBlocksPerWindow();
    void setSamplesPerBlock(int samplesPerBlock);
    void setBlocksPerWindow(int blocksPerWindow);
private:
    std::vector<std::vector<float> > m_data;
    int m_samplesPerBlock;
    int m_blocksPerWindow;
    int m_samplesPerWindow;
    int m_numSamples;
};


#endif //BPMDETECTOR_BPMDETECTOR_H
