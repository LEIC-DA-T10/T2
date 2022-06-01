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

void firstScenario::printOptions(){
    cout << "-*-------------  Scenario 1  --------------------------*-" << endl;
    cout << " |--> Computing" << endl;
    cout << " |        1 - Compute Scenario 1.1 " << endl;
    cout << " |        2 - Compute Scenario 1.2"  << endl;
    cout << " |--> Exit " << endl;
    cout << " |        0 - Exit Scenario "<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

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

void firstScenario::compute_1_1() {
    // Node List
    vector<vector<Route>> nodes = safe_nodes;
    // Stack to store all solutions
    vector<vector<int>> paths = allPaths(nodes);


    for(auto & path : paths){
        printPath(path);
    }
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
            route_index = checkNode( nodes.at(node_index));
            if(route_index != FAILED_FLAG){
                path.push(route_index);
            }
            else{
                //if the path
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

vector<int> firstScenario::stackIntoVector(stack<int> stack) {
    vector<int> vector;
    while(!stack.empty()) {
        vector.push_back(stack.top());
        stack.pop();
    }
    reverse(vector.begin(), vector.end());
    return vector;
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

void firstScenario::printPath(vector<int> path){
    cout << "(";
    for(int i = 0; i < path.size(); i++){
        cout << path.at(i);
        if(i < path.size()-1) cout << "->";
    }
    cout << ")" << endl;
}



void firstScenario::compute_1_2() {

}



