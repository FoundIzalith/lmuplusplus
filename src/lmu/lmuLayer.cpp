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
    cell = new LMUCell(*original.cell);
    hiddenState = new arma::Mat<float>(*original.hiddenState);
    memoryVector = new arma::Mat<float>(*original.memoryVector);
    output = new arma::Cube<float>(*original.output);

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
    //Input x = batchSize, y = sequenceLength, z = inputSize
    batchSize = input.n_rows;
    sequenceLength = input.n_cols;
    inputSize = input.n_slices;

    hiddenState = new arma::Mat<float>(batchSize, hiddenSize);
    memoryVector = new arma::Mat<float>(batchSize, memorySize);
    output = new arma::Cube<float>(batchSize, sequenceLength, hiddenSize);
    
    arma::Cube<float> inputT(batchSize, sequenceLength, inputSize);
    
    for(int i = 0; i < sequenceLength; i++) {
        //Iterate through input along the sequence
        inputT = input;
        inputT.resize(batchSize, i, inputSize);
        cell->processInput(inputT, *hiddenState, *memoryVector);

        //Add hidden state to output, layer by layer, along the sequence
        for(int j = 0; j < batchSize; j++) {
            for(int k = 0; k < hiddenSize; k++) {
                output->at(j, i, k) = hiddenState->at(j, k);
            }
        }
    }
}