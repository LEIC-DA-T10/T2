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
    stack<int> findPathLazy(int groupSize, vector<vector<Route>> nodes, int start);
    static void printPath(vector<int> path);
    static int checkNode(int groupSize, vector<Route> &node);
    static vector<int> stackIntoVector(stack<int> stack);
    void blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize);
    static int checkIfDestination(const vector<Route>& node, int destination);
    vector<int> capacityCheck(const vector<vector<Route>> &nodes, const vector<int> &path, int newPassengers, int &maxFlow);
    void findDetour(vector<vector<Route>> &nodes, vector<int> &path, int newPassengers);
public:
    explicit secondScenario(const map<int, vector<Route>> &nodes);
    void compute() override;

};
#endif //DA_T1_SECONDSCENARIO_H
