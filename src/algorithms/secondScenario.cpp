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
        stack<int> path = findPathLazy(buffer, nodes, 0);
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
    int groupSize,buffer,counter = 1;
    vector<vector<Route>> nodes = safe_nodes;
    vector<vector<int>> paths;


    cout << "Addition to Group Size: " << endl;
    cin >> groupSize;
    buffer = groupSize;



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


void secondScenario::compute_2_3() {

}

void secondScenario::compute_2_4() {

}

void secondScenario::compute_2_5() {

}

stack<int> secondScenario::findPathLazy(int groupSize, vector<vector<Route>> nodes, int start) {
    stack<int> path;
    int node_index = start;
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

void secondScenario::findDetour(vector<vector<Route>> &nodes, vector<int> &path, int newPassengers){
    int  buffer = newPassengers, counter = 1, maxFlow = 0, groupSize = newPassengers;
    stack<int> path2;
    vector<vector<int>> paths;
    vector<int> buffers;
    vector<int> okCheck = capacityCheck(nodes, path, newPassengers, maxFlow);
    buffer -= maxFlow; //os que sobraram

    //the path does not fit the remainder
    if(!okCheck.empty()){
        if(maxFlow > 0){
            //some people still fit tho
            paths.push_back(path);
            buffers.push_back(maxFlow); //buffer
            blockPath(nodes, path, maxFlow);
            groupSize -= maxFlow;
            buffer = groupSize;
            cout << "some people made it through the given path" << endl;
            counter++;
        }else{
            //no  one fit
            cout<< "no one made it through the given path" << endl;
        }

        //now find new paths for the people that could not fit

        int sourceNodeId = path.at(okCheck[0]);

        while(buffer > 0){
            path2.empty();
            path2 = findPathLazy(buffer, nodes, sourceNodeId); //findAlternativePathLazy(buffer, nodes,)
            if(!path2.empty()){
                vector<int> vectorPath2 = stackIntoVector(path2);
                paths.push_back(vectorPath2);
                buffers.push_back(buffer);
                blockPath(nodes, vectorPath2, buffer); //verify group size
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

    }else{
        cout << "New Passengers Fit" << endl; //update nodes capacity
    }
}


























































vector<int> secondScenario::capacityCheck(const vector<vector<Route>> &nodes, const vector<int> &path, int newPassengers, int &maxFlow){
    vector<int> okCheck;
    maxFlow = newPassengers;
    int finalNode = path[path.size()-1], index, source, destination = 0;
    for(int i = 0; destination != finalNode; i++){
        source = path.at(i);
        destination = path.at(i+1);
        index = checkIfDestination(nodes.at(source),destination);
        if(index != FAILED_FLAG){
            if(nodes.at(source).at(index).capacity >= newPassengers){ // it can fail for 3 people but not 2
                //tem que dar empty
            } else{
                okCheck.push_back(i); //index where capacity fails in path
                if(nodes.at(source).at(index).capacity < maxFlow){
                    maxFlow = nodes.at(source).at(index).capacity;     //BREAK REMOVED
                }
            }
        }
    }
    cout << "Checking if capacity is okay" << endl;
    return okCheck;
}

//stack<int> secondScenario::findAlternativePathLazy(int groupSize, vector<vector<Route>> nodes, int sourceIndex, vector<int> linkUp) { //vector<int> avoid// LInkUp is the remaining available nodes to converge with and the final node
//    stack<int> path;
//    int node_index = sourceIndex;
//    int route_index;
//
//    //insert first node into stack
//    path.push(node_index);
//    //if stack is empty, there is no solution, loops breaks when exit node enters stack.
//    while(!path.empty()){
//        node_index = path.top();
//        if(node_index != finalNode){        // I need to alter the comparison
//            route_index = checkNode(groupSize, nodes.at(node_index));
//            if(route_index != FAILED_FLAG){
//                path.push(route_index);
//            }
//            else{
//                path.pop();
//            }
//        }
//        else{
//            //Found final node
//            break;
//        }
//    }
//
//    return path;
//}
