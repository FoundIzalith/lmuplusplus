#include <iostream>
#include <math.h>
#include <armadillo>
#include <random>
#include <time.h>
#include "lmu.hpp"

LMUCell::LMUCell() {
    matrixA = 0;
    matrixB = 0;

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
    matrixA = new arma::Mat<float>(*original.matrixA);
    matrixB = new arma::Mat<float>(*original.matrixB);

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

//This is the constructor which actually gets called by the LMULayer
LMUCell::LMUCell(int i, int h, int m, int t) {
    inputSize = i;
    hiddenSize = h;
    memorySize = m;
    theta = t;

    generateMatrices(matrixA, matrixB, memorySize);
    discretizeMatrices(matrixA, matrixB, memorySize);

    initEncoders();
    initKernels();
}

LMUCell::~LMUCell() {
    delete matrixA;
    delete matrixB;

    delete encodingInput;
    delete encodingHidden;
    delete encodingMemory;

    delete kernelInput;
    delete kernelHidden;
    delete kernelMemory;
}

void LMUCell::processInput(const arma::Mat<float>& input, arma::Mat<float>& prevH, arma::Mat<float>& prevM) {
    //input is input. prevH is hiddenState (t - 1). prevM is memoryVector (t - 1)
    //The paper [1] can help make the purpose of this function more clear.
    //Feed forward
    int batchSize = input.n_rows;

    arma::Mat<float> hiddenState(batchSize, hiddenSize);
    arma::Mat<float> memoryVector(batchSize, memorySize);
    
    //Equation 7 [1]
    //u = (e_x^T * x_t) + (e_h^T * h_t-1) + (e_m^T * m_t-1)
    arma::Mat<float> u(batchSize, 1);
    u = input * encodingInput->t() + (prevH * encodingHidden->t()) + (prevM * encodingMemory->t());

    //Equation 4 [1]
    //m = (A * m_t-1) + (B * u) 
    memoryVector = (*matrixA * prevM) + (*matrixB * u);

    //Equation 6 [1]
    //h = f((W_x * x_t) * (W_h * h_t-1) + (W_m * m_t)), where f() is a chosen nonlinearity, in our case tanh  
    hiddenState = (input * *kernelInput) + (prevH * *kernelHidden) + (prevM * *kernelMemory);
    hiddenState.transform( [](float n) { return tanh(n); });

    //We set these for the next cycle 
    prevH = hiddenState;
    prevM = memoryVector;
}

void LMUCell::initEncoders() {
    encodingInput = new arma::Mat<float>(1, inputSize);
    encodingHidden = new arma::Mat<float>(1, hiddenSize);
    encodingMemory = new arma::Mat<float>(1, memorySize);

    LeCunUniform(*encodingInput, inputSize);
    LeCunUniform(*encodingHidden, hiddenSize);
    LeCunUniform(*encodingMemory, memorySize);
}

void LMUCell::initKernels() {
    kernelInput = new arma::Mat<float>(hiddenSize, inputSize);
    kernelHidden = new arma::Mat<float>(hiddenSize, hiddenSize);
    kernelMemory = new arma::Mat<float>(hiddenSize, memorySize);

    xavierInit(*kernelInput, hiddenSize, inputSize);
    xavierInit(*kernelHidden, hiddenSize, hiddenSize);
    xavierInit(*kernelMemory, hiddenSize, memorySize);
}