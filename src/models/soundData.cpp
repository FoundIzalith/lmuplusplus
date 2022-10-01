#include <iostream>
#include <armadillo>
#include <math.h>
#include "soundData.hpp"

soundData::soundData() {
    fileName = "NULL";
    duration = 0;
    sampleRate = 0;
    channels = 0;
    length = 0;

    samples = 0;
    spectrogram = 0;
}

soundData::soundData(std::string fN, int d, int s, int c, int l) {
    fileName = fN;
    duration = d;
    sampleRate = s
    channels = c;
    length = l;

    samples = 0;
    spectrogram = 0;
}

soundData::soundData(const soundData& original) {
    fileName = original.fileName;
    duration = original.duration;
    sampleRate = original.sampleRate;
    channels = original.channels;
    length = original.length;

    int totalSampleCount = sampleRate * length;

    samples = new int[totalSampleCount];

    for(int i = 0; i < totalSampleCount; i++) {
        samples[i] = original.samples[i];
    }

    spectrogram = new arma::Mat<float>(*original.spectrogram);
}

soundData::~soundData() {
    delete[] samples;
    delete spectrogram;
}