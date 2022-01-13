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

    /**
     * Detects the BPM of some audio data. Must first set the audio data by calling setAudio().
     * @see setAudio()
     * @param minBpm the minimum acceptable BPM value
     * @param maxBpm the maximum acceptable BPM value
     * @returns the detected BPM
     */
    float detectBpm(int minBpm=90, int maxBpm=180);
    //================================================================
    // Getters & Setters
    /**
     * Sets the audio whose BPM will be measured. This MUST be called before calling detectBpm()
     * @see detectBpm()
     * @param audio reference to the audio data
     */
    void setAudio(std::vector<std::vector<float> > &audio);

    /** @returns the number of samples per block */
    int getSamplesPerBlock();

    /** @returns the number of blocks per window */
    int getBlocksPerWindow();

    /**
     * Sets the number of samples that make up a block
     * @param samplesPerBlock
     */
    void setSamplesPerBlock(int samplesPerBlock);

    /**
     * Sets the number of blocks that make up a window
     * @param blocksPerWindow
     */
    void setBlocksPerWindow(int blocksPerWindow);

private:
    /**
     * Computes the sound energy threshold for the given window.
     *
     * Computes the sound energy threshold for the given window. The sound energy threshold is the
     * amount of sound energy a block in the given window needs to be considered to contain a beat.
     * @param w specs of the window being analyzed
     * @return the sound energy threshold
     */
    float computeThreshold(WindowSpecs w);

    /**
     * Computes the average sound energy produced by the blocks in the given window
     * @param w specs of the window being analyzed
     * @return the average energy
     * @see computeBlockEnergy()
     */
    float computeAvgBlockEnergy(WindowSpecs w);

    /**
     * Computes the sound energy produced by the given block
     * @param blockNum the index of the block being analyzed
     * @return the sound energy produced by the given block
     */
    float computeBlockEnergy(int blockNum);

    /**
     * vector of vectors of floats, holds audio data that was set using setAudio().
     * The inner vectors each represent a channel.
     * Example: 2 channels and 10 samples might look like...
     * [0.01, 0.23, -0.43, 0.2, -0.68, 0.2], [0.01, 0.19, -0.45, 0.23, -0.7, 0.22]]
     * @see setAudio()
     */
    std::vector<std::vector<float> > m_data;
    int m_samplesPerBlock; /**< number of samples in each block */
    int m_blocksPerWindow; /**< number of blocks in each window */
    int m_numSamples; /**< number of samples in each channel of m_data */
    /**
     * number of samples in each window. This is easily calculated as m_samplesPerBlock * m_blocksPerWindow but
     * it's here for convenience.
     */
    int m_samplesPerWindow;
};


#endif //BPMDETECTOR_BPMDETECTOR_H
