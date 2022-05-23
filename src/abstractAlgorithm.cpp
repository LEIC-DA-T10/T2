//
// Created by Eduardo Correia on 09/04/2022.
//

#include "abstractAlgorithm.h"

abstractAlgorithm::abstractAlgorithm(const vector<request>& requests,const vector<truck>& trucks) {
    this->requests = requests;
    this->trucks = trucks;
}

abstractAlgorithm::abstractAlgorithm() = default;

