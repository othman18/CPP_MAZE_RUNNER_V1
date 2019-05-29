#include <utility>
#include "AlgorithmRegistration.h"
#include "AlgorithmSaver.h"

AlgorithmRegistration::AlgorithmRegistration(std::function<std::unique_ptr<AbstractAlgorithm>()> function) {
    AlgorithmSaver::setFunction(std::move(function));
}