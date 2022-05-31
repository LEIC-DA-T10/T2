//
// Created by dudud on 09/04/2022.
//

#ifndef DA_T1_SECONDSCENARIO_H
#define DA_T1_SECONDSCENARIO_H
#define FAILED_FLAG -1000

#include "../abstractAlgorithm.h"
#include <iostream>
#include <stack>

class secondScenario : abstractAlgorithm{
private:
    static void printOptions();
    bool run(int state);
    void compute_2_1();
    void compute_2_2();
    void compute_2_3();
    void compute_2_4();
    void compute_2_5();
    stack<int> findPathLazy(int groupSize);
    static void printPath(stack<int> path);
    static int checkNode(int groupSize, vector<Route> &node);

public:
    explicit secondScenario(const map<int, vector<Route>> &nodes);
    void compute() override;
};
#endif //DA_T1_SECONDSCENARIO_H
