//lmuplusplus, a C++ implementation of the Legendre Memory Unit

//lmu.hpp contains declarations for core functionality for the LMU 

#include <iostream>
#include <vector>
#include <math.h>
#include <armadillo>
#include "matrixUtil.hpp"

#ifndef GUANSLAB_LMUPLUSPLUS
#define GUANSLAB_LMUPLUSPLUS

//Basic memory cell
class LMUCell {
public:
    LMUCell();
    LMUCell(const LMUCell&);
    LMUCell(int, int, int, int); //Generate by parameters 
    ~LMUCell();

    void processInput(arma::Cube<float> input); //Sets hidden and memory states

    ostream& operator<<(ostream& os, LMUCell); //Write

protected:
    matrices discretizedMatrix, baseMatrix; //Matrices 
    arma::Mat<float> *hiddenState;
    arma::Mat<float> *memoryVector; 

    //Parameters
    int inputSize; //Size of input vector
    int hiddenSize; //Size of hidden vector
    int memorySize; //Size of memory vector (Number of ODEs)
    int theta; //Number of timesteps in sliding window of time 
};

//Standard LMU layer
class LMULayer {
public:
    LMULayer();
    LMULayer(const LMULayer&);
    LMULayer(int, int, int, int);
    ~LMULayer();

    void processInput(arma::Cube<float> input);

    ostream& operator<<(ostream& os, LMULayer); //Write

protected:
    LMUCell *cell; 
    arma::Mat<float> *hiddenState; 
    arma::Cube<float> *output;

    //Parameters
    int inputSize; //Size of input vector
    int hiddenSize; //Size of hidden vector
    int memorySize; //Size of memory vector (Number of ODEs)
    int theta; //Number of timesteps in sliding window of time

    //Taken from the input tensor
    int batchSize;
    int sequenceLength;
};

//Paralellized LMU layer 
class LMUFFT {
public:

protected:

};


#endif 