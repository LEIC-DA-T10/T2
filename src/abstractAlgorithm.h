//
// Created by Eduardo Correia on 09/04/2022.
//

#ifndef DA_T1_ABSTRACTALGORITHM_H
#define DA_T1_ABSTRACTALGORITHM_H


#include <map>
#include "dataStructs.h"

using namespace std;

class abstractAlgorithm {
protected:
    /**
     * Node Vector which holds all the nodes and routes used in the algorithm
     */
    map<int,vector<Route>> nodes;
public:
    /**
     * Constructor for the abstractAlgorithm class, receives a node vector for computing the algorithm.
     * @param nodes node vector to be used in the algorithm.
     */
    explicit abstractAlgorithm(const map<int, vector<Route>> &nodes);
    /**
     * Pure virtual function used to guarantee that any child class also has the compute function.
     */
    virtual void compute() = 0;
};


#endif //DA_T1_ABSTRACTALGORITHM_H
