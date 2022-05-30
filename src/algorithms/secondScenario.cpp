//
// Created by Eduardo Correia on 09/04/2022.
//


#include <stack>
#include "secondScenario.h"


secondScenario::secondScenario(const map<int, vector<Route>> &nodes) : abstractAlgorithm(nodes) {}

void secondScenario::compute() {
    int state;
    printOptions();
    cin >> state;
    if(run(state)){
        cout << "Finished Computing Scenario 2_" << state << "." << endl;
    }
    else{
        cout << "Exiting to main menu." << endl;
    }
}

void secondScenario::printOptions(){
    cout << "-*-------------  Scenario 2  --------------------------*-" << endl;
    cout << " |--> Computing" << endl;
    cout << " |        1 - Compute Scenario 2.1 " << endl;
    cout << " |        2 - Compute Scenario 2.2"  << endl;
    cout << " |        3 - Compute Scenario 2.3 " << endl;
    cout << " |        4 - Compute Scenario 2.4"  << endl;
    cout << " |        5 - Compute Scenario 2.5 " << endl;
    cout << " |--> Exit " << endl;
    cout << " |        0 - Exit Scenario "<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

bool secondScenario::run(int state) {
    switch (state) {
        case 1:
            compute_2_1();
            return true;
        case 2:
            compute_2_2();
            return true;
        case 3:
            compute_2_3();
            return true;
        case 4:
            compute_2_4();
            return true;
        case 5:
            compute_2_5();
            return true;
        default:
            return false;
    }
}

void secondScenario::compute_2_1() {
    int groupSize;
    cout << "Group Size: " << endl;
    cin >> groupSize;
    stack<int> path = findPathLazy(groupSize);
    if(!path.empty()){
        cout << "Found path" << endl;
        printPath(path);
    }
    else{
        cout << "Could not find an adequate path for the given group size" << endl;
    }
}

void secondScenario::compute_2_2() {

}

void secondScenario::compute_2_3() {

}

void secondScenario::compute_2_4() {

}

void secondScenario::compute_2_5() {

}

stack<int> secondScenario::findPathLazy(int groupSize) {
    stack<int> path;
    int node_index = 0;
    Route route;
    vector<vector<Route>> nodes = safe_nodes;

    path.push(node_index);

    while(!path.empty()){
        node_index = path.top();
        if(node_index != finalNode){
            route = checkNode(groupSize, nodes.at(node_index));
            if(route.destination != FAILED_FLAG){
                cout << node_index << "->" << route.destination << endl;
                path.push(route.destination);
            }
            else{
                path.pop();
            }
        }
        else{
            //Found final node
            break;
        }
    }

    return path;
}

Route secondScenario::checkNode(int groupSize, const vector<Route>& node){
    Route failedRoute;
    failedRoute.destination = FAILED_FLAG;
    for(auto route : node){
        if(route.capacity >= groupSize) return route;
    }
    return failedRoute;
}

void secondScenario::printPath(stack<int> path){
    vector<int> reversedPath;

    while(!path.empty()) {
        reversedPath.push_back(path.top());
        path.pop();
    }

    cout << "(";
    for(int i = (int)reversedPath.size()-1; i >= 0; i--){
        cout << reversedPath.at(i);
        if(i >= 1) cout << "->";
    }
    cout << ")" << endl;
}
