#include <iostream>
#include <armadillo>

#ifndef LMUPLUSPLUS_SOUNDDS
#define LMUPLUSPLUS_SOUNDDS

//This class is used to store and pre-process audio files 

class soundData {
public:
    soundData();
    soundData();
    soundData(const soundDataset&);
    ~soundData();

    //Functions for external use
    void processAudio(std::string); //Path to directory
    arma::Mat<float> getSpectrogram(); 

    //Implicitly called functions
    void readWav();         //Reads and samples wav
    void genSpectrogram();  //Takes samples and creates spectrogram 
    
private:
    std::string fileName; 
    int duration;
    int sampleRate;
    int channels;
    int length;

    int *samples; //Array of length [sampleRate * duration]
    arma::Mat<float> *spectrogram;
};

#endif