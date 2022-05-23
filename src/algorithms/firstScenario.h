//
// Created by Eduardo Correia on 09/04/2022.
//

#ifndef DA_T1_FIRSTSCENARIO_H
#define DA_T1_FIRSTSCENARIO_H


#include "../abstractAlgorithm.h"

class firstScenario : abstractAlgorithm{
public:
    firstScenario(vector<request> requests, vector<truck> trucks);
    void compute() override;
    vector<truck> execute(vector<truck> trucks);
    void clearTruckLoad(vector<truck> *trucks);
    void computeWeightSort();
    void computeVolumeSort();
    void computeTimeSort();

};

bool requestTimeSort(const request &a, const request &b);
bool truckWeightSort(const truck &a, const truck &b);
bool requestWeightSort(const request &a, const request &b);
bool truckVolumeSort(const truck &a, const truck &b);
bool requestVolumeSort(const request &a, const request &b);
bool isNegative(truck, request);
void truckLoadPrint(vector<request> truckLoad);
int printMenu();

#endif //DA_T1_FIRSTSCENARIO_H
