//
// Created by Andrew King on 1/13/22.
//

#include "BpmDetector.h"

BpmDetector::BpmDetector(int samplesPerBlock, int blocksPerWindow)
{
    m_samplesPerBlock = samplesPerBlock;
    m_blocksPerWindow = blocksPerWindow;
    m_samplesPerWindow = m_blocksPerWindow * m_samplesPerBlock;
    m_numSamples = 0;
}

float BpmDetector::detectBpm(int minBpm, int maxBpm)
{
    // calculate total number of complete blocks and windows
    int numBlocks = m_numSamples / m_samplesPerBlock;
    int numWindows = numBlocks / m_blocksPerWindow;

    int numBeatsDetected = 0;

    // for each window
    for (int w = 0; w < numWindows; w++)
    {
        // construct the WindowSpecs struct
        WindowSpecs window;
        window.id = w;
        window.startBlock = m_blocksPerWindow * w;
        window.endBlock = window.startBlock + m_blocksPerWindow;
        window.startSample = window.startBlock * m_samplesPerBlock;
        window.endSample = window.endBlock * m_samplesPerBlock;

        for (int b = window.startBlock; b < window.endBlock; b++)
        {
            float e = computeBlockEnergy(b);
            float threshold = computeThreshold(window);
            if (e > threshold) {
                //note there is a beat
                numBeatsDetected++;
            }
        }
    }

    // calculate raw bpm
    float seconds = m_numSamples / 44100;
    float mins = seconds / 60;
    float bpm = numBeatsDetected / mins;

    // convert bpm to the specified range
    while (bpm < minBpm) {
        bpm *= 2;
    }
    while (bpm > maxBpm) {
        bpm /= 2;
    }

    return bpm;
}

float BpmDetector::computeThreshold(WindowSpecs w)
{
    // compute variance
    float varSum = 0;
    for (int i = w.startBlock; i < w.endBlock; i++)
    {
        float temp = computeAvgBlockEnergy(w) - computeBlockEnergy(i);
        temp = temp*temp;
        varSum += temp;
    }

    float variance = varSum / (w.endBlock - w.startBlock);
    float c = -0.0000015 * variance + 1.5142857;
    float thresh = c * computeAvgBlockEnergy(w);

    return thresh;
}

float BpmDetector::computeAvgBlockEnergy(WindowSpecs w)
{
    //* Compute the average energy of the blocks in the given window

    int totalEnergy = 0;
    for (int i = w.startBlock; i < w.endBlock; i++)
    {
        totalEnergy += computeBlockEnergy(i);
    }

    float avg = totalEnergy / (w.endBlock - w.startBlock);

    return avg;
}

float BpmDetector::computeBlockEnergy(int blockNum)
{
    int blockStart = blockNum * m_samplesPerBlock;
    int blockEnd = blockStart + m_samplesPerBlock;

    float total = 0;
    for (int i = blockStart; i < blockEnd; i++)
    {
        // sum the squares of left and right channels
        float left = m_data[0][i]; //note this works!
        float right = m_data[1][i]; //note this works!

        total = total + left*left + right*right;
    }

    return total;
}

//=======================================================================
//                        Getters & Setters
//=======================================================================
void BpmDetector::setAudio(std::vector<std::vector<float> > &audio)
{
    m_data = audio;
    m_numSamples = m_data[0].size();
    return;
}

void BpmDetector::setBlocksPerWindow(int blocksPerWindow) {
    m_blocksPerWindow = blocksPerWindow;
    m_samplesPerWindow = m_blocksPerWindow * m_samplesPerBlock;
    return;
}

int BpmDetector::getBlocksPerWindow() {
    return m_blocksPerWindow;
}

void BpmDetector::setSamplesPerBlock(int samplesPerBlock) {
    m_samplesPerBlock = samplesPerBlock;
    m_samplesPerWindow = m_blocksPerWindow * m_samplesPerBlock;
    return;
}

int BpmDetector::getSamplesPerBlock() {
    return m_samplesPerBlock;
}