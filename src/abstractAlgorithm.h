//
// Created by Eduardo Correia on 09/04/2022.
//

#ifndef DA_T1_ABSTRACTALGORITHM_H
#define DA_T1_ABSTRACTALGORITHM_H


#include "dataStructs.h"

using namespace std;

class abstractAlgorithm {
protected:
    /**
     * Request Vector which holds all the requests used in the algorithm
     */
    vector<request> requests;
    /**
     * Truck Vector which holds all the trucks used in the algorithm
     */
    vector<truck> trucks;
public:
    /**
     * Constructor for the abstractAlgorithm class, receives a request and truck vector which are then used to instantiate their respective vectors.
     * @param requests request vector to use in the algorithm
     * @param trucks truck vector to use in the algorithm
     */
    abstractAlgorithm(const vector<request>& requests,const vector<truck>& trucks);
    /**
     * Empty Constructor for the abstract algorithm class, used in the compare option.
     */
    abstractAlgorithm();
    /**
     * Pure virtual function used to guarantee that any child class also has the compute function.
     */
    virtual void compute() = 0;
};


#endif //DA_T1_ABSTRACTALGORITHM_H
