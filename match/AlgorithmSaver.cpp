#include "AlgorithmSaver.h"

std::unique_ptr<AlgorithmSaver> AlgorithmSaver::instance = std::make_unique<AlgorithmSaver>();

void AlgorithmSaver::setFunction(std::function<std::unique_ptr<AbstractAlgorithm>()> function) {
    instance->algorithm = std::move(function);
}

std::function<std::unique_ptr<AbstractAlgorithm>()> AlgorithmSaver::getFunction() {
    return instance->algorithm;
}
