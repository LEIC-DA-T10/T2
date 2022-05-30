//
// Created by Eduardo Correia on 09/04/2022.
//

#include "abstractAlgorithm.h"

abstractAlgorithm::abstractAlgorithm(const map<int, vector<Route>> &nodes) {
    for(const auto& node : nodes){
        this->nodes.push_back(node.second);
    }
}

