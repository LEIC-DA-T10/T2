//
// Created by Eduardo Correia on 09/04/2022.
//

#include "abstractAlgorithm.h"

abstractAlgorithm::abstractAlgorithm(const map<int, vector<Route>> &nodes) {
    for(const auto& node : nodes){
        this->safe_nodes.push_back(node.second);
    }
    finalNode = (int)safe_nodes.size();
}

