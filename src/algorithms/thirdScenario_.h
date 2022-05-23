//
// Created by Ze Carvalho on 16/04/2022.
//

#ifndef DA_T1_THIRDSCENARIO__H
#define DA_T1_THIRDSCENARIO__H
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

#include "../abstractAlgorithm.h"

class thirdScenario_ : abstractAlgorithm{
private:
    truck express;
    vector<request> requests;
    vector<truck> trucks;

    unsigned int usedTime = 0;
    unsigned int income = 0;
    const unsigned int timeFrame = 28800;
    int nReq = 0;
    vector<request> deliveryList;

public:
    thirdScenario_(const vector<request>& requests, const vector<truck>& trucks);
    void compute() override;
    vector<request> fitsTruck();
    bool isDeliverable(int i) const;

    int knapSack(int W, vector<request>, int n);

    int knapSackRec(int W, vector<request> wt, int i, int **dp);
};

#endif //DA_T1_THIRDSCENARIO__H
