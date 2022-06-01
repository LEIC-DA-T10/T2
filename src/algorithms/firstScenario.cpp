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
    // Source and Destination nodes explicitly;
    int Source = 0;
    int Destination = finalNode;

    // Queue to store all paths
    queue<vector<int>> paths;
    
    // Vector to store paths that lead to destination
    vector<vector<int>> correctPaths;
    //Current path
    vector<int> path;
    //Adding the source to the initial path
    path.push_back(Source);
    //Pushing the path to the path vector
    paths.push(path);
    
    int currentVertex;
    
    //Stop only when there's no more paths to compute
    while(!paths.empty()){
        path = paths.front();
        paths.pop();
        
        currentVertex = path[path.size()-1];
        
        if(currentVertex == Destination){
            cout << "Encontrado Caminho" << endl;
            correctPaths.push_back(path);
        }

        for (int i = 0; i < nodes[currentVertex].size(); i++){
            if (!nodes[currentVertex][i].visited){
                nodes[currentVertex][i].visited = true;
                vector<int> newpath(path);
                newpath.push_back(nodes[currentVertex][i].destination);
                paths.push(newpath);
            }
        }
    }

    return correctPaths;
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



