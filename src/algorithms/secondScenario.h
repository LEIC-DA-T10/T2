//
// Created by dudud on 09/04/2022.
//

#ifndef DA_T1_SECONDSCENARIO_H
#define DA_T1_SECONDSCENARIO_H


#include "../abstractAlgorithm.h"

class secondScenario : abstractAlgorithm{
public:
    explicit secondScenario(const map<int, vector<Route>> &nodes);
    void compute() override;
};
#endif //DA_T1_SECONDSCENARIO_H
