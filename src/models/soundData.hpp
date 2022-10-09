#include <iostream>
#include <armadillo>

#ifndef LMUPLUSPLUS_SOUNDDS
#define LMUPLUSPLUS_SOUNDDS

//This class is used to store and pre-process audio files 

const int MAX_FREQUENCY = 4300;

class soundData {
public:
    soundData();
    soundData(std::string, std::string, int, int, int, int);
    soundData(const soundData&);
    ~soundData();

    //Functions for external use
    void processAudio(std::string); //File
    void processAudio(std::string, int sizeOfWindows);
    arma::Mat<float> getSpectrogram(); 

    //Implicitly called functions
    void readWav();         //Reads and samples wav
    void genSpectrogram();  //Takes samples and creates spectrogram 

    soundData& operator=(const soundData&);
    
private:
    std::string fileName;
    std::string path;  
    int duration;
    int sampleRate;
    int channels;

    int windowSize; //Determines # of samples per second for spectrogram, default = 20

    int *samples; //Array of length [sampleRate * duration]
    arma::Mat<float> *spectrogram;
};

#endif