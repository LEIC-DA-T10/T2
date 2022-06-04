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
    static void printPath(const vector<Vertex>& path);
    static int checkNode(int groupSize, vector<Route> &node);
    static vector<int> stackIntoVector(stack<int> stack);
    void blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize);
    static int checkIfDestination(const vector<Route>& node, int destination);
    static vector<Vertex> dijkstra(const vector<Vertex> &safe_vertices, int final, int source);
    static int vectorContains(vector<int> vector, int value);
    static int getMinimumCapacity(const vector<Vertex>& path);
    static vector<Vertex> increaseFlow(const vector<Vertex> & vertices_input, const vector<Vertex> & path, int value);
    void calculate_earliestStartFinish(vector<Vertex> &vertices, int source, int final);
    vector<Vertex> safe_vertices;
public:
    explicit secondScenario(const map<int, vector<Route>> &nodes);
    void compute() override;

};
#endif //DA_T1_SECONDSCENARIO_H
