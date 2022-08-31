#include <iostream>
#include <math.h>
#include <armadillo>
#include "lmu.hpp"
#include "matrixUtil.hpp"

LMUCell::LMUCell() {
    matrixA = 0;
    matrixB = 0;
    hiddenState = 0;
    memoryVector = 0;
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

    hiddenState = 0;
    memoryVector = 0;
}

LMUCell::~LMUCell() {
    delete matrixA;
    delete matrixB;
    delete hiddenState;
    delete memoryVector;
}

void LMUCell::processInput(const arma::Cube<float> input&) {
    
}