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