#include <iostream>
#include <cassert>
#include <armadillo>
#include "../src/lmu/lmu.hpp"

int main() {
    {
        std::out << "Rectified linear unit of [-3, -1, 0, 1, 3]: "
        float array[] = {-3, -1, 0, 1, 3};
        float result = 0;

        for(int i = 0; i < 4; i++) {
            result = reLU(array[i]);
            std::cout << " " << result; 
        }

        std::cout << "\n";
    }

    {
        arma::Mat<float> *A = new arma::Mat<float>(10, 10);
        arma::Mat<float> *B = new arma::Mat<float>(1, 10);
        int memorySize = 10;

        generateMatrices(*A, *B, memorySize);

        std::cout << "MatrixA : " << std::endl;
        A->print();

        std::cout << "MatrixB: " << std::endl;
        B->print();

        discretizeMatrices(*A, *B, memorySize);
        std::cout << "Both matrices have now been discretized. \n";

        std::cout << "MatrixA : " << std::endl;
        A->print();

        std::cout << "MatrixB: " << std::endl;
        B->print();

        delete A;
        delete B;
    }  

    std::cout << "All matrix tests passed." << std::endl;
}