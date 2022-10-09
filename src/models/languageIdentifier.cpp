#include <iostream>
#include <armadillo>
#include "languageIdentifier.hpp"
#include "soundData.hpp"
#include "../lmu/lmu.hpp"

languageIdentifier::languageIdentifier() {
    dataset = new soundData[10]();
    lmu = new LMULayer();
    batchSize = 10;
    outputPath = "empty";
}

languageIdentifier::languageIdentifier(const languageIdentifier& original) {
    lmu = new LMULayer(*original.lmu);
    batchSize = original.batchSize;
    outputPath = original.outputPath;
    
    dataset = new soundData[batchSize]();

    for(int i = 0; i < batchSize; i++) {
        dataset[i] = new soundData(original.dataset[i]);
    }
}

languageIdentifier::~languageIdentifier() {
    delete[] dataset;
    delete lmu;
}

void languageIdentifier::train(std::string datapath, std::string label) {

}

void languageIdentifier::analyze(std::string datapath) {

}
