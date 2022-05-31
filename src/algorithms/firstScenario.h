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

    void longestPath(int s);

    void allPaths(int s);

    void printAllPathsUtil(int u, int d, bool *visited, int *path, int &path_index);
};
#endif //DA_T1_FIRSTSCENARIO_H
