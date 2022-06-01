//
// Created by Eduardo Correia on 09/04/2022.
//


#include <stack>
#include "secondScenario.h"
#include <bits/stdc++.h>
#include <limits>
#define FAILED_FLAG -1000



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
    int groupSize,buffer,counter = 1;
    vector<vector<Route>> nodes = safe_nodes;
    vector<vector<int>> paths;
    vector<int> buffers;

    cout << "Group Size: " << endl;
    cin >> groupSize;
    buffer = groupSize;

    while(buffer > 0){
        stack<int> path = findPathLazy(buffer, nodes);
        if(!path.empty()){
            vector<int> vectorPath = stackIntoVector(path);
            paths.push_back(vectorPath);
            buffers.push_back(buffer);
            blockPath(nodes, vectorPath, buffer);
            groupSize -= buffer;
            buffer = groupSize;
            counter++;
        }
        else{
            buffer--;
        }
    }

    if(groupSize > 0){
        cout << "Could not find a path for the given group size" << endl;
    }
    else{
        int counter_b = 0;
        for(const auto& path : paths){
            cout << "Found path for subgroup [" << counter_b+1 << "] with size [" << buffers.at(counter_b) <<"]"<< endl;
            printPath(path);
            counter_b++;
        }
    }
}

void secondScenario::compute_2_2() {

}

void secondScenario::compute_2_3() {
    vector<vector<Route>> nodes = safe_nodes;
    vector<int> path;

    path = computeEdmondsKarp(nodes);
}

void secondScenario::compute_2_4() {

}

void secondScenario::compute_2_5() {

}

stack<int> secondScenario::findPathLazy(int groupSize, vector<vector<Route>> nodes) {
    stack<int> path;
    int node_index = 0;
    int route_index;

    //insert first node into stack
    path.push(node_index);
    //if stack is empty, there is no solution, loops breaks when exit node enters stack.
    while(!path.empty()){
        node_index = path.top();
        if(node_index != finalNode){
            route_index = checkNode(groupSize, nodes.at(node_index));
            if(route_index != FAILED_FLAG){
                path.push(route_index);
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


int secondScenario::checkNode(int groupSize, vector<Route> &node) {
    for(auto & route : node){
        if(groupSize <= route.capacity && !route.visited){
            route.visited = true;
            return route.destination;
        }
    }
    return FAILED_FLAG;
}

void secondScenario::printPath(vector<int> path){
    cout << "(";
    for(int i = 0; i < path.size(); i++){
        cout << path.at(i);
        if(i < path.size()-1) cout << "->";
    }
    cout << ")" << endl;
}

vector<int> secondScenario::stackIntoVector(stack<int> stack) {
    vector<int> vector;
    while(!stack.empty()) {
        vector.push_back(stack.top());
        stack.pop();
    }
    reverse(vector.begin(), vector.end());
    return vector;
}

void secondScenario::blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize) {
    int source,destination = 0,index;
    for(int i = 0; destination != finalNode; i++){
        source = path.at(i);
        destination = path.at(i+1);
        index = checkIfDestination(nodes.at(source),destination);
        if(index != FAILED_FLAG){
            nodes.at(source).at(index).capacity -= groupSize;
        }
    }
}

int secondScenario::checkIfDestination(const vector<Route>& node, int destination){
    for(int i = 0; i < node.size(); i++){
        if(destination == node.at(i).destination){
            return i;
        }
    }
    return FAILED_FLAG;
}

void secondScenario::computeCapacityFlowGraph(vector<vector<Route>> &nodes) {
    int min = 1;

    while(min > 0){
        min = calculateAugmentingPath(nodes);
    }
}

int secondScenario::calculateAugmentingPath(vector<vector<Route>> &nodes) {
    stack<int> path;
    vector<int> pathVector;
    int minimum = numeric_limits<int>::max(),node_index = 0;
    pair<int,int> flow_pair;

    //insert first node into stack
    path.push(node_index);
    //if stack is empty, there is no solution, loops breaks when exit node enters stack.
    while(!path.empty()){
        node_index = path.top();
        if(node_index != finalNode){
            flow_pair = checkNodeFlow(nodes.at(node_index));
            if(flow_pair.first != FAILED_FLAG){
                path.push(flow_pair.first);
                minimum = getMin(minimum,flow_pair.second);
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
    pathVector = stackIntoVector(path);


    if(!pathVector.empty()){
        cout << "Found Augmenting Path : " << endl;
        printPath(pathVector);
        changeFlow(nodes,pathVector,minimum);
        cout << "Flow increased in path by : " << minimum << endl;
    }
    else{
        minimum = 0;
    }

    return minimum;
}

pair<int, int> secondScenario::checkNodeFlow(vector<Route> &node) {
    pair<int, int> returnValue;
    returnValue.first = FAILED_FLAG;
    returnValue.second = FAILED_FLAG;
    for(auto & route : node){
        if(route.flow < route.capacity && !route.visited){
            route.visited = true;
            returnValue.first = route.destination;
            returnValue.second = (route.capacity-route.flow);
            return returnValue;
        }
    }
    return returnValue;
}

int secondScenario::getMin(int value1, int value2) {
    if(value1 < value2) return value1;
    return value2;
}

void secondScenario::changeFlow(vector<vector<Route>> &nodes, const vector<int> &path, const int &value) {
    int source,destination = 0,index;
    for(int i = 0; destination != finalNode; i++){
        source = path.at(i);
        destination = path.at(i+1);
        index = checkIfDestination(nodes.at(source),destination);
        if(index != FAILED_FLAG){
            nodes.at(source).at(index).flow += value;
        }
    }
}

vector<int> secondScenario::computeEdmondsKarp(vector<vector<Route>> &nodes) {
    vector<int> path;
    vector<Vertex> visited_nodes;
    vector<Route> queueBuffer;
    Vertex current_vertex;

    //Compare Function used for the prio queue, sorts elements by capacity
    auto compare = [](Route &route1, Route &route2) { return route1.capacity < route2.capacity;};
    priority_queue<Route,vector<Route>, decltype(compare)> priorityQueue(compare);

    //Add first node routes to prio queue
    current_vertex.index = 0;
    for(auto route : nodes.at(0)){
        priorityQueue.push(route);
    }

    while (!priorityQueue.empty()){
        current_vertex.source = priorityQueue.top().source;
        current_vertex.index = priorityQueue.top().destination;
        current_vertex.capacity = priorityQueue.top().capacity;
        priorityQueue.pop();
        if(current_vertex.index != finalNode){
            for(auto & route : nodes.at(current_vertex.index)){
                if(checkIfContains(visited_nodes,route.destination) == FAILED_FLAG){
                    route.source = current_vertex.index;
                    queueBuffer.clear();
                    //Inserting priorityQueue elements into vector Buffer
                    while(!priorityQueue.empty()){
                        Route routeBuffer = priorityQueue.top();
                        priorityQueue.pop();
                        queueBuffer.push_back(routeBuffer);
                    }

                    //Check if route destination is already in queue, if it is , overwrite if capacity is larger
                    if(overwriteIfExists(queueBuffer,route) == FAILED_FLAG){
                        queueBuffer.push_back(route);
                    }

                    //Re-insert elements into prio queue
                    for(auto elem : queueBuffer){
                        priorityQueue.push(elem);
                    }
                }
            }
        }
        visited_nodes.push_back(current_vertex);
    }


    for(auto node : visited_nodes){
        cout << node.index << "("<<node.capacity <<","<<node.source << ")"<< endl;
    }

    return path;
}

int secondScenario::checkIfContains(const vector<Vertex> &vector, int value) {
    int index = 0;
    for(auto elem : vector){
        if(elem.index == value) return index;
        index++;
    }
    return FAILED_FLAG;
}

int secondScenario::overwriteIfExists(vector<Route> &routes, Route newRoute) {
    int index = 0;
    for(auto & route : routes){
        if(route.destination == newRoute.destination){
            if(route.capacity < newRoute.capacity){
                route = newRoute;
            }
            return index;
        }
        index++;
    }
    return FAILED_FLAG;
}

