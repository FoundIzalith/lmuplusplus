#include <iostream>
#include <math.h>
#include <armadillo>
#include <random>
#include <chrono>
#include "lmu.hpp"

LMULayer::LMULayer() {
    cell = 0;
    hiddenState = 0;
    memoryVector = 0;
    output = 0;

    inputSize = 0;
    hiddenSize = 0;
    memorySize = 0;
    theta = 0;

    batchSize = 0;
    sequenceLength = 0;
}

LMULayer::LMULayer(const LMULayer& original) {
    cell = new LMUCell(original.cell);
    hiddenState = new Mat<float>(original.hiddenState);
    memoryVector = new Mat<float>(original.memoryVector);
    output = new Cube<float>(original.output);

    inputSize = original.inputSize;
    hiddenSize = original.hiddenSize;
    memorySize = original.memorySize;
    theta = original.theta;

    batchSize = original.batchSize;
    sequenceLength = original.sequenceLength;
}

LMULayer::LMULayer(int i, int h, int m, int t) {
    inputSize = i;
    hiddenSize = h;
    memorySize = m;
    theta = t;

    cell = new LMUCell(i, h, m, t);
}

LMULayer::~LMULayer() {
    delete cell;
    delete hiddenState;
    delete memoryVector;
    delete output;
}

void LMULayer::processInput(const arma::Cube<float>& input) {
    batchSize = input.n_rows;
    sequenceLength = input.n_cols;

    hiddenState = new arma::Mat<float>(batchSize, hiddenSize);
    memoryVector = new arma::Mat<float>(batchSize, memorySize);
    output = new arma::Cube<float>(sequenceLength, batchSize, hiddenSize);
    
    for(int i = 0; i < sequenceLength; i++) {
        cell.processInput(input, hiddenState, memoryVector);
    }
}