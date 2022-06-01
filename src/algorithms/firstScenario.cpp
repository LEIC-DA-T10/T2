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
    vector<vector<Route>> nodes = safe_nodes;
    pair<int,vector<int>> output;

    output = elephant_algorithm(nodes);

    cout << "Found Maximum Group Size [" << output.first << "] with the following path: " << endl;
    printPath(output.second);
}

pair<int, vector<int>> firstScenario::elephant_algorithm(vector<vector<Route>> nodes){
    int next,max;
    pair<int,vector<int>> output;
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

                    route.capacity = getMin(current_vertex.capacity,route.capacity);

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
        else{
            visited_nodes.push_back(current_vertex);
            break;
        }
        visited_nodes.push_back(current_vertex);
    }


    path.push_back(visited_nodes.back().index);
    next = visited_nodes.back().source;
    max = visited_nodes.back().capacity;

    //Insert Path into output vector
    for(int i = visited_nodes.size() - 1; i >= 0; i--){
        Vertex node = visited_nodes.at(i);
        if(node.index == next){
            path.push_back(node.index);
            next = node.source;
        }
    }

    //Add First Node;
    path.push_back(0);
    reverse(path.begin(), path.end());

    output.first = max;
    output.second = path;
    return output;
}

void firstScenario::compute_1_2() {
    int buffer = 1;
    vector<vector<Route>> nodes = safe_nodes;
    vector<vector<int>> paths;
    vector<int> buffers;

    int end = 0;
    int pathsFound = 0;

    while(end == 0){
        stack<int> path = findPathLazy(buffer, nodes);
        if(!path.empty()){
            vector<int> vectorPath = stackIntoVector(path);
            paths.push_back(vectorPath);
            blockPath(nodes, vectorPath, buffer);
            pathsFound ++;
        }
        else{
           if (pathsFound == 0){
               end = 1;
           }else{
               pathsFound = 0;
               buffer++;
           }
        }
    }

    for(auto path : paths){
        printPath(path);
        cout << "-*-----*-" << endl;
    }
}

stack<int> firstScenario::findPathLazy(int groupSize, vector<vector<Route>> nodes) {
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

void firstScenario::blockPath(vector<vector<Route>> &nodes, const vector<int> &path, int groupSize) {
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

int firstScenario::checkIfDestination(const vector<Route>& node, int destination){
    for(int i = 0; i < node.size(); i++){
        if(destination == node.at(i).destination){
            return i;
        }
    }
    return FAILED_FLAG;
}



/* Aux functions */
int firstScenario::checkNode(int groupSize, vector<Route> &node) {
    for(auto & route : node){
        if(groupSize <= route.capacity && !route.visited){
            route.visited = true;
            return route.destination;
        }
    }
    return FAILED_FLAG;
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

/* Most likely trash */

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

int firstScenario::checkIfContains(const vector<Vertex> &vector, int value) {
    int index = 0;
    for(auto elem : vector){
        if(elem.index == value) return index;
        index++;
    }
    return FAILED_FLAG;
}

int firstScenario::overwriteIfExists(vector<Route> &routes, Route newRoute) {
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

int firstScenario::getMin(int value1, int value2) {
    if(value1 < value2) return value1;
    return value2;
}
