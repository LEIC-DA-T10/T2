//
// Created by dudud on 09/04/2022.
//

#ifndef DA_T1_SECONDSCENARIO_H
#define DA_T1_SECONDSCENARIO_H

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
    stack<int> findPathLazy(int groupSize, vector<vector<Route>> nodes);
    static void printPath(vector<int> path);
    static int checkNode(int groupSize, vector<Route> &node);
    static vector<int> stackIntoVector(stack<int> stack);
    void blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize);
    static int checkIfDestination(const vector<Route>& node, int destination);
    void computeCapacityFlowGraph(vector<vector<Route>> &nodes);
    int calculateAugmentingPath(vector<vector<Route>> &nodes);
    static pair<int, int> checkNodeFlow(vector<Route> &node);
    static int getMin(int value1, int value2);
    void changeFlow(vector<vector<Route>> &nodes,const vector<int> &path,const int &value);


public:
    explicit secondScenario(const map<int, vector<Route>> &nodes);
    void compute() override;

};
#endif //DA_T1_SECONDSCENARIO_H
