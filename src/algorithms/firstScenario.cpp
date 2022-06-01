//
// Created by Eduardo Correia on 09/04/2022.
//


#include "firstScenario.h"

#include <climits>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <stack>


firstScenario::firstScenario(const map<int, vector<Route>> &nodes) : abstractAlgorithm(nodes){}

//Main Computing Function
void firstScenario::compute() {
    int state;
    printOptions();
    cin >> state;
    if(run(state)){
        cout << "Finished Computing Scenario 1_" << state << "." << endl;
    }
    else{
        cout << "Exiting to main menu." << endl;
    }
}




void firstScenario::compute_1_1() {
    // Node List, a copy of the data input
    vector<vector<Route>> nodes = safe_nodes;
    for(auto & pat : allPaths(nodes)){
        printPath(pat);
    }
    getBestPath(allPaths(nodes),nodes);
}

void firstScenario::getBestPath(vector<vector<int>> paths,vector<vector<struct Route>> nodes){
    //Max capacity of the path
    //Min capacity of the nodes of the path
    int maxCapacity = -1,minCapacity;

    // The best path, the one with the max capacity
    vector<int> theChosenOne;
    // CurrentPath and CurrentNode are auxiliary vars only to help code comprehension
    for (int i = 0; i < paths.size(); i++) {
        minCapacity = INT64_MAX;
        auto currentPath = paths[i];
        //Only iterating from 0 to size-1 since destination does not have capacity
        for (int j = 0; j < currentPath.size()-1; j++) {
            auto currentNode = currentPath[j];
            if(nodes.at(currentNode).capacity() < minCapacity){
                minCapacity = nodes.at(currentNode).capacity();
                //Computing all nodes from each path and then get the smallest capacity of the path
            }
        }
        //If the computed path has a bigger capacity than the previous one then the Chosen path will be updated
        if(minCapacity>maxCapacity) {
            maxCapacity = minCapacity;
            theChosenOne = paths[i];
        }
    }

    printSolution(theChosenOne,maxCapacity);
}


vector<vector<int>> firstScenario::allPaths(vector<vector<struct Route>> nodes){
    // Vector to store paths that lead to destination
    vector<vector<int>> correctPaths;
    //Stack to hold the current path
    stack<int> path;

    int node_index = 0;
    int route_index;

    //insert first node into stack
    path.push(node_index);
    //if stack is empty, there is no solution, loops breaks when exit node enters stack.
    while(!path.empty()){
        // look for the first node of the path
        node_index = path.top();
        //Check if the current node corresponds to the destination
        if(node_index != finalNode){
            route_index = checkNode(nodes.at(node_index));
            if(route_index != FAILED_FLAG){
                path.push(route_index);
            }
            else{
                //if the path leads to a dead end pop it
                path.pop();
            }
        }
        else{
            correctPaths.push_back(stackIntoVector(path));
            path.pop();
        }
    }
    return correctPaths;
}



int firstScenario::checkNode(vector<Route> &node) {
    for(auto & route : node){
        if(!route.visited){
            route.visited = true;
            return route.destination;
        }
    }
    return FAILED_FLAG;
}

void firstScenario::compute_1_2() {

}

/* Aux functions */

bool firstScenario::run(int state) {
    switch (state) {
        case 1:
            compute_1_1();
            return true;
        case 2:
            compute_1_2();
            return true;
        default:
            return false;
    }
}

void firstScenario::printOptions(){
    cout << "-*-------------  Scenario 1  --------------------------*-" << endl;
    cout << " |--> Computing" << endl;
    cout << " |        1 - Compute Scenario 1.1 " << endl;
    cout << " |        2 - Compute Scenario 1.2"  << endl;
    cout << " |--> Exit " << endl;
    cout << " |        0 - Exit Scenario "<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

void firstScenario::printSolution(vector<int> path,int maxCapacity){
    cout << "-*-------------  Scenario Report  --------------------------*-" << endl;
    cout << " |-->Max path capacity: " << maxCapacity << endl;
    printPath(path);
    cout << "-*----------------------------------------------------*-" << endl;
}

void firstScenario::printPath(vector<int> path){
    cout << "(";
    for(int i = 0; i < path.size(); i++){
        cout << path.at(i);
        if(i < path.size()-1) cout << "->";
    }
    cout << ")" << endl;
}

vector<int> firstScenario::stackIntoVector(stack<int> stack) {
    vector<int> vector;
    while(!stack.empty()) {
        vector.push_back(stack.top());
        stack.pop();
    }
    reverse(vector.begin(), vector.end());
    return vector;
}

