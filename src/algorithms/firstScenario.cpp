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
    int Source,Destination;
    stack<int> path;
    vector<vector<Route>> nodes = safe_nodes;


}

void firstScenario::allPaths(int s)
{
    stack<int> Stack;
    int numberNodes = finalNode++;


    bool* visited = new bool[numberNodes];
    // Initialize all vertices as not visited
    for (int i = 0; i < numberNodes; i++)
        visited[i] = false;


}
//https://www.geeksforgeeks.org/find-paths-given-source-destination/
void firstScenario::printAllPathsUtil(int u, int d, bool visited[],int path[], int& path_index){

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

