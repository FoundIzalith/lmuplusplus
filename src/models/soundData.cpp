#include <iostream>
#include <armadillo>
#include <math.h>
#include "soundData.hpp"

soundData::soundData() {
    fileName = "NULL";
    path = "NULL";
    duration = 0;
    sampleRate = 0;
    channels = 0;

    samples = 0;
    spectrogram = 0;
}

soundData::soundData(std::string fN, std::string p, int d, int s, int c) {
    fileName = fN;
    path = p; 
    duration = d;
    sampleRate = s
    channels = c;

    samples = 0;
    spectrogram = 0;
}

soundData::soundData(const soundData& original) {
    fileName = original.fileName;
    path = original.path;
    duration = original.duration;
    sampleRate = original.sampleRate;
    channels = original.channels;

    int totalSampleCount = sampleRate * duration;

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

void soundData::processAudio(std::string file) {
    fileName = file; 

}

arma::Mat<float> getSpectrogram() {
    return *spectrogram;
}

void readWav() {
    std::ifstream audioFile;
    audioFile.open(path + fileName);

    //Read from .wav header 
    //These magic numbers are all part of the .wav standard 
    //OFFSET    FIELD NAME      BYTES
    //8         Format          4
    //22        NumChannels     2
    //24        SampleRate      4
    //34        BitsPerSample   2
    //40        Subchunk2size   4

    //Duration = Subchunk2size / SampleRate * BitsPerSample

    if(audioFile != NULL) {
        //This is where the magic numbers come in
        char NumChannels[2];
        char WavSampleRate[4];
        char BitsPerSample[2];
        char Subchunk2size[4];
        char readByte; 
        int bps;
        int sc2s;

        audioFile.read(readByte, 22);
        NumChannels[0] = readByte;
        audioFile.read(readByte, 23)
        NumChannels[1] = readByte;

        audioFile.read(readByte, 24);
        WavSampleRate[0] = readByte;
        audioFile.read(readByte, 25);
        WavSampleRate[1] = readByte;
        audioFile.read(readByte, 26);
        WavSampleRate[2] = readByte;
        audioFile.read(readByte, 27);
        WavSampleRate[3] = readByte;

        audioFile.read(readByte, 34);
        BitsPerSample[0] = readByte;
        audioFile.read(readByte, 35);
        BitsPerSample[1] = readByte;

        audioFile.read(readByte, 40);
        Subchunk2size[0] = readByte;
        audioFile.read(readByte, 41);
        Subchunk2size[1] = readByte;
        audioFile.read(readByte, 42);
        Subchunk2size[2] = readByte;
        audioFile.read(readByte, 43);
        Subchunk2size[3] = readByte;

        //First we read in all the data into arrays of chars,
        //then we can cast them into integers
        channels = *((int*)NumChannels);
        sampleRate = *((int*)WavSampleRate);
        bps = *((int*)BitsPerSample);
        sc2s = *((int*)Subchunk2size);
        duration = sc2s / (bps * sampleRate);

        //Read data section of .wav 
        for(int i = 0; i < sc2s; i++) {
            audioFile.read(readByte, 44 + i);
            samples[i] = (int)readByte;
        }


    } else {
        std::cout << "ERROR: Unable to open file: " << path << fileName << std::endl;
    }

}