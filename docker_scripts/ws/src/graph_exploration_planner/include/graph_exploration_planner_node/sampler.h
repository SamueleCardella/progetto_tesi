#pragma once 

#include <random>
#include <iostream>

class Sampler {
private:
    
public:

    Sampler(){}

    ~Sampler(){}

    std::vector<std::pair<float,float>> sampleArea(const float& xMin, 
                                                   const float& xMax,
                                                   const float& yMin,
                                                   const float& yMax, 
                                                   const uint32_t& sampleSize) {
        std::vector<std::pair<float,float>> returnSample;
        returnSample.resize(sampleSize);
        std::random_device rd;  
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> disX(xMin, xMax);
        std::uniform_real_distribution<> disY(yMin, yMax);
        for (size_t i = 0; i < sampleSize; i++) {
            returnSample[i].first  = disX(gen);
            returnSample[i].second = disY(gen);
        }
        return returnSample;
    }

};

