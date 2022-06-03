//
// Created by Eduardo Correia on 09/04/2022.
// Developed by Jose Carvalho
//

#include "firstScenario.h"
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <stack>
#include <utility>

firstScenario::firstScenario(const map<int, vector<Route>> &nodes) : abstractAlgorithm(nodes){}

//Main Computing Function
void firstScenario::compute() {
    int state;
    printOptions();
    cin >> state;
    if(run(state)){
        cout << "-*----------------------------------------------------*-" << endl;
        cout << "           Finished Computing Scenario 1_" << state << "." << endl;
    }
    cout << "               Exiting to main menu..." << endl;

}

void firstScenario::compute_1_1() {
    vector<vector<Route>> nodes = safe_nodes;
    pair<int,vector<int>> output;

    output = elephant_algorithm(nodes);

    cout << "Found Maximum Group Size [" << output.first << "] with the following path: " << endl;
    printSolution(output.second,output.first);
}

pair<int, vector<int>> firstScenario::elephant_algorithm(vector<vector<Route>> nodes){
    int next,max;
    pair<int,vector<int>> output;
    vector<int> path;
    vector<Vertex> visited_nodes;
    vector<Route> queueBuffer;
    Vertex current_vertex;

    //Compare Function used for the priority queue, sorts elements by capacity
    auto compare = [](Route &route1, Route &route2) { return route1.capacity < route2.capacity;};
    priority_queue<Route,vector<Route>, decltype(compare)> priorityQueue(compare);

    //Add first node routes to priority queue
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

                    /*
                     * Commented code, used for overwriting elements in prio queue, d
                     * depreceated beacause we can simply re-insert elements with lower capacity
                     * and they are ignored due to already being present in the visited array

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

                    //Re-insert elements into priority queue
                    for(auto elem : queueBuffer){
                        priorityQueue.push(elem);
                    }
                    */

                    priorityQueue.push(route);
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
    // Copy of data input
    vector<vector<Route>> nodes = safe_nodes;
    // Vector to Store paths
    vector<vector<int>> paths;

    /* Control variables for the while:
     *  end = 0 The first try to find a path with a new group size was successful
     *  buffer = Current group size
     *  pathsFound = Nbr of paths within a group size
     *  totalPathsFound = Total nbr of paths found from source to destination in this run
     */

    int end = 0;
    int buffer = 1;

    int pathsFound = 0;
    int totalPathsFound = 0;


    while(end == 0){
        stack<int> path = findPathLazy(buffer, nodes);
        if(!path.empty()){
            vector<int> vectorPath = stackIntoVector(path);
            paths.push_back(vectorPath);
            blockPath(nodes, vectorPath, buffer);
            pathsFound ++;
            totalPathsFound++;
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

    printSolution(paths,nodes);
}

/* Aux functions */

vector<vector<int>> firstScenario::getSimilarPaths(vector<vector<int>> paths, const vector<vector<struct Route>>& nodes,vector<int> pathToCompare){

    vector<vector<int>> similarPaths;

    for(auto & path : paths){
        if (path.size() == pathToCompare.size() && (getGroupSize(path,nodes) == getGroupSize(pathToCompare,nodes) && path != pathToCompare))
            similarPaths.push_back(path);
    }

    return similarPaths;
}

pair<double,vector<int>> firstScenario::getRatio(vector<vector<int>> paths,const vector<vector<struct Route>>& nodes){

    //Min transfers
    double bestRatio = INT32_MIN;
    pair<float,vector<int>> output;
    double ratio;
    // The best path, the one with the least transfers
    vector<int> theChosenOne;

    for(auto & path : paths){
        ratio = (double) getGroupSize(path,nodes) / (double) path.size();
        if (ratio > bestRatio){
            bestRatio = ratio;
            theChosenOne = path;
        }
    }
    output.first =  bestRatio;
    output.second = theChosenOne;
    return output;
}

pair<int,vector<int>> firstScenario::getMinTransfers(vector<vector<int>> paths,const vector<vector<struct Route>>& nodes){

    //Min transfers
    int minTransfers = INT32_MAX;
    pair<int,vector<int>> output;

    // The best path, the one with the least transfers
    vector<int> theChosenOne;

    for(auto & path : paths){
        if (path.size() < minTransfers){
            minTransfers = path.size();
            theChosenOne = path;
        }else if (path.size() == minTransfers && getGroupSize(theChosenOne,nodes) < getGroupSize(path,nodes)){
            theChosenOne = path;

        }
    }

    output.first = minTransfers;
    output.second = theChosenOne;
    return output;
}

pair<int,vector<int>> firstScenario::getBiggestGroupSize(const vector<vector<int>>& paths,vector<vector<struct Route>> nodes){
    //Max capacity of the path
    //Min capacity of the nodes of the path
    int maxCapacity = -1,minCapacity;

    pair<int,vector<int>> output;

    // The best path, the one with the max capacity
    vector<int> theChosenOne;
    // CurrentPath and CurrentNode are auxiliary vars only to help code comprehension
    for (auto & path : paths) {
        minCapacity = INT32_MAX;
        auto currentPath = path;
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
            theChosenOne = path;
        }else if (minCapacity == maxCapacity && theChosenOne.size() > path.size()){
            theChosenOne = path;
        }
    }

    output.first = maxCapacity;
    output.second = theChosenOne;
    return output;

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

int firstScenario::checkNode(int groupSize, vector<Route> &node) {
    for(auto & route : node){
        if(groupSize <= route.capacity && !route.visited){
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
    cout << " | Path: "<< endl;
    cout << " | ";
    printPath(std::move(path));
}

void firstScenario::printSolution(vector<vector<int>> paths, const vector<vector<Route>>& nodes){
    char option;
    sort( paths.begin(), paths.end());
    paths.erase( unique( paths.begin(), paths.end() ), paths.end() );

    // Get pareto-optimal paths
    pair<int,vector<int>> MaxSize = getBiggestGroupSize(paths,nodes);
    pair<int,vector<int>> MinTrans = getMinTransfers(paths,nodes);
    pair<double,vector<int>> BestRatio = getRatio(paths,nodes);

    // Get other "pareto-optimal" paths if exist
    vector<vector<int>> simSize = getSimilarPaths(paths,nodes,MaxSize.second);
    vector<vector<int>> simTrans = getSimilarPaths(paths,nodes,MinTrans.second);
    vector<vector<int>> simRatio = getSimilarPaths(paths,nodes,BestRatio.second);

    cout << "-*-------------  Scenario Report  --------------------------*-" << endl;
    cout << " | [Found " << paths.size() << " path(s)]"<< endl;
    cout << " |"<< endl;
    cout << " |-->Printing best solutions:"<< endl;

    cout << " | [Highest Capacity]"<< endl;
    cout << " | Capacity: "<< MaxSize.first<< endl;
    cout << " | Transfers: "<< MaxSize.second.size()<< endl;
    cout << " | Path: "<< endl;
    cout << " | ";
    printPath(MaxSize.second);

    if(!simSize.empty()){
        cout << " |-->Other Pareto Optimal solutions:"<< endl;
        for(auto & path: simSize){
            cout << " | ";
            cout << " | [Path] "<< endl;
            printPath(path);
        }
    }


    cout << " | [Less transfers]"<< endl;
    cout << " | Capacity: "<< getGroupSize(MinTrans.second,nodes)<< endl;
    cout << " | Transfers:"<< MinTrans.first<< endl;
    cout << " | Path:"<< endl;
    cout << " | ";
    printPath(MinTrans.second);

    if(!simTrans.empty()){
        cout << " |-->Other Pareto Optimal solutions:"<< endl;
        for(auto & path: simTrans){
            cout << " | [Paths] "<< endl;
            cout << " | ";
            printPath(path);
        }
    }

    cout << " | [Highest group size to transfers ratio]"<< endl;
    cout << " | Ratio: "<< BestRatio.first<<endl;
    cout << " | Capacity: "<< getGroupSize(BestRatio.second,nodes)<< endl;
    cout << " | Transfers:"<< BestRatio.second.size()<< endl;
    cout << " | Path:"<< endl;
    cout << " | ";
    printPath(BestRatio.second);

    if(!simRatio.empty()){
        cout << " |-->Other Pareto Optimal solutions:"<< endl;
        for(auto & path: simRatio){
            cout << " | [Paths] "<< endl;
            cout << " | ";
            printPath(path);
        }
    }
    cout << " | "<< endl;
    cout << " |-->No other Pareto Optimal solutions were found."<< endl;
    cout << " |-->Do you wish to see all paths?: (y/n)"<< endl;
    cin >> option;
    if(option == 'y'){
        for(const auto& path : paths){
            cout << " | ";
            printPath(path);
        }
    }
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

int firstScenario::checkIfContains(const vector<Vertex> &vector, int value) {
    int index = 0;
    for(const auto& elem : vector){
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

int firstScenario::getGroupSize(vector<int> &path, vector<vector<struct Route>> nodes) {
    int minCapacity = INT32_MAX;
    for (int j = 0; j < path.size()-1; j++) {
        auto currentNode = path[j];
        if(nodes.at(currentNode).capacity() < minCapacity){
            minCapacity = nodes.at(currentNode).capacity();
            //Computing all nodes from each path and then get the smallest capacity of the path
        }
    }
    return minCapacity;
}



