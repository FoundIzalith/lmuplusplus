#include <iostream>
#include <armadillo>
#include "languageIdentifier.hpp"
#include "soundData.hpp"
#include "../lmu/lmu.hpp"

languageIdentifier::languageIdentifier() {
    dataset = new soundData();
    lmu = new LMULayer();
    outputPath = "empty";
}

languageIdentifier::languageIdentifier(const languageIdentifier& original) {
    dataset = original.dataset;
    lmu = new LMULayer(original->lmu);
    outputPath = original.outputPath;
}

languageIdentifier::~languageIdentifier() {
    delete[] dataset;
    delete lmu;
}

void languageIdentifier::train(std::string datapath, std::string label) {

}

void languageIdentifier::analyze(std::string datapath) {
    
}
