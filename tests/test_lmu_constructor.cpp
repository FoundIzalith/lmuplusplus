#include <iostream>
#include <cassert>
#include "../src/lmu/lmu.hpp"

int main() {

    {
        LMUCell lmu1;
        LMUCell lmu2(lmu1);
        LMUCell lmu3(10, 10, 10, 10);
    }

    std::cout << "Passed LMUCell constructor test" << std::endl;

    {
        LMULayer lmu1;
        LMULayer lmu2(lmu1);
        LMULayer lmu3(10, 10, 10, 10);

    }

    std::cout << "Passed LMULayer constructor test" << std::endl;

    std::cout << "All constructor tests passed." << std::endl;

    return 0;
}