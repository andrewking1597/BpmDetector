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