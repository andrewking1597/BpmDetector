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