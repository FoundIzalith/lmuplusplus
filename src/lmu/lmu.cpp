#include <iostream>
#include <math.h>
#include <armadillo>
#include <random>
#include <chrono>
#include "lmu.hpp"
#include "matrixUtil.hpp"

LMUCell::LMUCell() {
    matrixA = 0;
    matrixB = 0;
    hiddenState = 0;
    memoryVector = 0;

    encodingInput = 0;
    encodingHidden = 0;
    encodingMemory = 0;

    kernelInput = 0;
    kernelHidden = 0;
    kernelMemory = 0;

    inputSize = 0;
    hiddenSize = 0;
    memorySize = 0;
    theta = 0; 
}

LMUCell::LMUCell(const LMUCell& original) {
    matrixA = new arma::Mat<float>(original.matrixA);
    matrixB = new arma::Mat<float>(original.matrixB);
    hiddenState = new arma::Mat<float>(original.hiddenState);
    memoryVector = new arma::Mat<float>(original.memoryVector);

    encodingInput = original.encodingInput;
    encodingHidden = original.encodingHidden;
    encodingMemory = original.encodingMemory;

    kernelInput = original.kernelInput;
    kernelHidden = original.kernelHidden;
    kernelMemory = original.kernelMemory;

    inputSize = original.inputSize;
    hiddenSize = original.hiddenSize;
    memorySize = original.memorySize;
    theta = original.theta;
}

LMUCell::LMUCell(int i, int h, int m, int t) {
    inputSize = i;
    hiddenSize = h;
    memorySize = m;
    theta = t;

    matrices AB = generateMatrices(memorySize, theta);
    discretizeMatrices(matrixA, matrixB, memorySize);

    initEncoders();
    initKernels();

    hiddenState = 0;
    memoryVector = 0;
}

LMUCell::~LMUCell() {
    delete matrixA;
    delete matrixB;
    delete hiddenState;
    delete memoryVector;

    delete encodingInput;
    delete encodingHidden;
    delete encodingMemory;

    delete kernelInput;
    delete kernelHidden;
    delete kernelMemory;
}

void LMUCell::processInput(const arma::Mat<float> input&) {
    //Equation 7 [1]
    //arma::Mat<float> u = 
}

void LMUCell::initEncoders() {
    encodingInput = new arma::Mat<float>(1, inputSize);
    encodingHidden = new arma::Mat<float>(1, hiddenSize);
    encodingMemory = new arma::Mat<float>(1, memorySize);

    LeCunUniform(encodingInput, inputSize);
    LeCunUniform(encodingHidden, hiddenSize);
    LeCunUniform(encodingMemory, memorySize);
}

void LMUCell::initKernels() {
    kernelInput = new arma::Mat<float>(hiddenSize, inputSize);
    kernelHidden = new arma::Mat<float>(hiddenSize, hiddenSize);
    kernelMemory = new arma::Mat<float>(hiddenSize, memorySize);

    //Xavier Initialization [6]
}

void LeCunUniform(arma::Mat<float>& matrix, int size) {
    //LeCun Uniform Distribution [5] (Section 1.4.6)
    //Used to initialize weights such that they are not too big but not too small 

    /*Given the fact that the LMU utilizes only a single cell
    per layer, I'm pretty sure the fan in is just the input size*/
    float limit = sqrt(3/inputSize);

    srand(system_clock::now().time_since_epoch());

    float sample = 0;

    //I know that every matrix inputted here has just 1 row
    for(int i = 0; i < size; i++) {
        //Get sample on interval [-limit, limit]
        sample = (rand() % (limit * 2)) - limit; 
        matrix.at(0, i) = sample; 
    }
}