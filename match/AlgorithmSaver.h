
#ifndef MANAGERCPP_ALGORITHMSAVER_H
#define MANAGERCPP_ALGORITHMSAVER_H


#include <functional>
#include <memory>
#include "AbstractAlgorithm.h"

class AlgorithmSaver {
    std::function<std::unique_ptr<AbstractAlgorithm>()> algorithm;
    static std::unique_ptr<AlgorithmSaver> instance;
public:
    static void setFunction(std::function<std::unique_ptr<AbstractAlgorithm>()> function);
    static std::function<std::unique_ptr<AbstractAlgorithm>()> getFunction();
};


#endif //MANAGERCPP_ALGORITHMSAVER_H
