//
// Created by Eduardo Correia on 09/04/2022.
//

#ifndef DA_T1_FIRSTSCENARIO_H
#define DA_T1_FIRSTSCENARIO_H
#define FAILED_FLAG -1000

#include <stack>
#include "../abstractAlgorithm.h"

class firstScenario : abstractAlgorithm{
public:
    explicit firstScenario(const map<int, vector<Route>> &nodes);
    void compute() override;

    void compute_1_1();

    void compute_1_2();

    bool run(int state);

    void printOptions();

    void printPath(vector<int> path);

    vector<vector<int>> allPaths(vector<vector<struct Route>> Graph);

    int checkNode(vector<Route> &node);

    vector<int> stackIntoVector(stack<int> stack);

    void getBestPath(vector<vector<int>> paths, vector<vector<struct Route>> nodes);

    void printSolution(vector<int> path, int maxCapacity);

    stack<int> findPathLazy(int groupSize, vector<vector<Route>> nodes);

    int getPathCapacity(vector<Route> &node);

    pair<int, vector<int>> elephant_algorithm(vector<vector<Route>> nodes);
    static int checkIfContains(const vector<Vertex> &vector, int value);
    static int overwriteIfExists(vector<Route> & routes, Route newRoute);
    static int getMin(int value1, int value2);

    void blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize);

    int checkIfDestination(const vector<Route> &node, int destination);

    int checkNode(int groupSize, vector<Route> &node);
};
#endif //DA_T1_FIRSTSCENARIO_H
