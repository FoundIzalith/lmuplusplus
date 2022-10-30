//This file contains bindings for python to interface
//With the C++ LMU code 

#include "../lmu/lmu.hpp"
#include <vector>

//This vector stores all created LMULayers
std::vector<LMULayer> LMUs;

//Creates a new LMULayer, adds it to the end of the storage vector,
//and returns the id of that vector so it can be called again later
unsigned int LMUInit(int input, int hidden, int memory, int theta) {
    unsigned int id;
    LMULayer newLMU(input, hidden, memory, theta);
    LMUs.push_back(newLMU);
    id = LMUs.size() - 1;
    return id; 
}

