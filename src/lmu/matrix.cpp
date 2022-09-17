//This file contains some functions used for manipulating matrices

#include <iostream>
#include <math.h>
#include <armadillo>
#include "lmu.hpp"

void generateMatrices(arma::Mat<float> *matrixA, arma::Mat<float> *matrixB, int memorySize) {
    //Equation 2 [1]
    float Q[memorySize];
    float R[memorySize];
    arma::Mat<float> matrix_I(memorySize, memorySize);
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
                matrixA->at(i, j) = result;
            }

            result = pow(-1.0, matrix_I.at(i, j) * matrix_J.at(i, j));
            matrixB->at(i, j) = result;
        }
    }
}

void discretizeMatrices(arma::Mat<float> *matrixA, arma::Mat<float> *matrixB, int memorySize) {
    //Step 1. Combine A and B, pad out to create square matrix
    //We need a square matrix to find the matrix exponential 
    arma::Mat<float> temp;
    temp = arma::join_cols(*matrixA, *matrixB);
    temp.resize(memorySize + 1, memorySize + 1);

    //Step 2. Compute matrix exponential 
    temp = expmat(temp);

    //Step 3. Slice A and B back out of combined matrix
    for(int i = 0; i < memorySize; i++) {
        for(int j = 0; j < memorySize; j++) {
            matrixA->at(i, j) = temp.at(i, j);
        }
    }

    delete matrixB;
    matrixB = new arma::Mat<float>(temp.row(memorySize));
    matrixB->resize(1, memorySize);
}

//Rectified Linear Unit
float reLU(float n) {
    if(n < 0) return 0;
    else return n;
}        

void LeCunUniform(arma::Mat<float>& matrix, int size) {
    //LeCun Uniform Distribution [5] (Section 1.4.6)
    //Used to initialize weights such that they are not too big but not too small 

    /*Given the fact that the LMU utilizes only a single cell
    per layer, I'm pretty sure the fan in is just the input size*/
    float limit = sqrt(3/inputSize);

    std::srand(time(NULL));

    float sample;

    //I know that every matrix inputted here has just 1 row
    for(int i = 0; i < size; i++) {
        //Get sample on interval [-limit, limit]
        sample = (std::rand() % (int)(limit * 2)) - limit; 
        matrix.at(0, i) = sample; 
    }
}

void xavierInit(arma::Mat<float>& matrix, int rows, int cols) {
    //Xavier Normal Initialization [6]
    //# of inputs and outputs should be the same 
    float mean = 0;
    float standardDeviation = sqrt(2/(2*inputSize));

    unsigned seed = time(NULL);
    std::default_random_engine random(seed);
    std::normal_distribution<float> distribution(mean, standardDeviation);
    std::srand(time(NULL));
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix.at(i, j) = distribution(random);
        }
    }
}