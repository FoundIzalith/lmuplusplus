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

    generateMatrices();
    discretizeMatrices();

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

void LMUCell::generateMatrices() {
    float Q[memorySize];
    float R[memorySize];
    arma::Mat<float matrix_I(memorySize, memorySize);
    arma::Mat<float> matrix_J(memorySize, memorySize);

    float result = 0;
    for(int i = 0; i < memorySize; i++) {
        //Step 1: create array Q with discrete elements
        Q[i] = i;
        //Step 2: create array R equal to 2 * Q + 1
        R[i] = (2 * i) + 1;

        //Step 3: create 2 matrices which are essentially just lines of Q
        for(int j = 0; j < memorySize; j++) {
            matrix_I.at(i, j) = Q[i]; //Ascending vertical
            matrix_J.at(i, j) = Q[j]; //Ascending horizontal

            //Step 4: use I and J to build A and B
            if(matrix_I.at(i, j) < matrix_J.at(i, j)) {
                result = pow(-1.0, matrix_I.at(i, j) - matrix_J.at(i, j) - 1);
                matrixA.at(i, j) = result;
            }

            result = pow(-1.0, matrix_I.at(i, j) * matrix_J.at(i, j));
            matrixB.at(i, j) = result;
        }
    }

    discretizeMatrices();
}

void LMUCell::discretizeMatrices() {

}

void LMUCell::processInput(const arma::Mat<float> input&, const arma::Mat<float> stateH&, const arma::Mat<float> stateM&) {
    //Feed forward

    int batchSize = input.rows();

    hiddenState = stateH;
    memoryVector = stateM;

    //Equation 7 [1]
    float u = tanh()
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

    xavierInit(kernelInput, hiddenSize, inputSize);
    xavierInit(kernelHidden, hiddenSize, hiddenSize);
    xavierInit(kernelMemory, hiddenSize, memorySize);
}

void LeCunUniform(arma::Mat<float>& matrix, int size) {
    //LeCun Uniform Distribution [5] (Section 1.4.6)
    //Used to initialize weights such that they are not too big but not too small 

    /*Given the fact that the LMU utilizes only a single cell
    per layer, I'm pretty sure the fan in is just the input size*/
    float limit = sqrt(3/inputSize);

    srand(system_clock::now().time_since_epoch());

    float sample;

    //I know that every matrix inputted here has just 1 row
    for(int i = 0; i < size; i++) {
        //Get sample on interval [-limit, limit]
        sample = (rand() % (limit * 2)) - limit; 
        matrix.at(0, i) = sample; 
    }
}

void xavierInit(arma::Mat<float>& matrix, int rows, int cols) {
    //Xavier Normal Initialization [6]

    //# of inputs and outputs should be the same 

    float mean = 0;
    float standardDeviation = sqrt(2/(2*inputSize));
    std::normal_distribution<float> distribution(mean, standardDeviation);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix.at(i, j) = distribution(system_clock::now().time_since_epoch());
        }
    }
}