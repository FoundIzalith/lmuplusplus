//lmuplusplus, a C++ implementation of the Legendre Memory Unit

//lmu.hpp contains declarations for core functionality for the LMU 

#include <iostream>
#include <vector>
#include <math.h>
#include <armadillo>

#ifndef GUANSLAB_LMUPLUSPLUS
#define GUANSLAB_LMUPLUSPLUS

//Basic memory cell
class LMUCell {
public:
    LMUCell();
    LMUCell(const LMUCell&);
    LMUCell(int, int, int, int); //Generate by parameters 
    ~LMUCell();

    void generateMatrices();
    void discretizeMatrices();
    //Sets hidden and memory states
    void processInput(const arma::Mat<float>& input, arma::Mat<float>& prevH, arma::Mat<float>& prevM); 

    void initEncoders();
    void initKernels();

    void LeCunUniform(arma::Mat<float>&, int size);
    void xavierInit(arma::Mat<float>&, int rows, int cols);

    std::ostream& operator<<(std::ostream& os); //Write

protected:
    arma::Mat<float> *matrixA, *matrixB; //Matrices 

    //Encoders
    arma::Mat<float> *encodingInput, *encodingHidden, *encodingMemory;

    //Kernels 
    arma::Mat<float> *kernelInput, *kernelHidden, *kernelMemory; 

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

    void processInput(const arma::Cube<float>& input);

    std::ostream& operator<<(std::ostream& os); //Write

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
    LMUFFT();
    LMUFFT(const LMUFFT&);
    LMUFFT(int, int, int, int, int);
    ~LMUFFT();

    void processInput(const arma::Cube<float>& input);
    void computeImpulse(); 

protected:
    arma::Mat<float> *matrixA, *matrixB, *matrixH;

    //Parameters
    int inputSize; //Size of input vector
    int hiddenSize; //Size of hidden vector
    int memorySize; //Size of memory vector (Number of ODEs)
    int sequenceLength; //Length of sequence
    int theta; //Number of timesteps in sliding window of time

};


#endif 