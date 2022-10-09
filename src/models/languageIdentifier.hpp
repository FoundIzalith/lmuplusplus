#include <iostream>
#include <armadillo>
#include "../lmu/lmu.hpp"
#include "soundData.hpp"

#ifndef LMUPLUSPLUS_LANGIDENT
#define LMUPLUSPLUS_LANGIDENT

class languageIdentifier {
public:
    languageIdentifier();
    languageIdentifier(const languageIdentifier&);
    ~languageIdentifier();

    void train(std::string datapath, std::string label);
    void analyze(std::string datapath);

private:
    soundData *dataset; 
    LMULayer *lmu; 

    std::string outputPath; //If set, will send output to file 
};

#endif