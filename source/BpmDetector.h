/**
 * @file BpmDetector.h
 * @author Andrew King
 * @copyright Copyright (C) 2021 Andrew King
 */

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
    /**
     * Constructor
     * @param samplesPerBlock the block size to use (in samples)
     * @param blocksPerWindow the window size to use (in blocks)
     */
    BpmDetector(int samplesPerBlock=1024, int blocksPerWindow=40);
    float detectBpm(int minBpm=90, int maxBpm=180);
    //================================================================
    // Getters & Setters
    void setAudio(std::vector<std::vector<float> > &audio);
    int getSamplesPerBlock();
    int getBlocksPerWindow();
    void setSamplesPerBlock(int samplesPerBlock);
    void setBlocksPerWindow(int blocksPerWindow);
private:
    float computeThreshold(WindowSpecs w);
    float computeAvgBlockEnergy(WindowSpecs w);
    float computeBlockEnergy(int blockNum);
    std::vector<std::vector<float> > m_data;
    int m_samplesPerBlock;
    int m_blocksPerWindow;
    int m_samplesPerWindow;
    int m_numSamples;
};


#endif //BPMDETECTOR_BPMDETECTOR_H
