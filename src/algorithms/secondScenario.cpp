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
    int source = 0;
    int sink = finalNode;
    vector<Vertex> vertices;
    vector<Vertex> shortest_path;
    Vertex current_vertex;

    //get shortest path from source to sink for all nodes
    vertices = dijkstra(nodes, sink, source);

    //insert shortest path from source to sink into a vector
    current_vertex = vertices.at(sink);
    while(true){
        shortest_path.push_back(current_vertex);
        if(current_vertex.index == source) break;
        current_vertex = vertices.at(current_vertex.source);
    }

    for(auto elem : shortest_path){
        cout << elem.index << endl;
    }

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

vector<Vertex> secondScenario::dijkstra(vector<vector<Route>> &nodes, int final, int source) {
    vector<Vertex> vertices;
    vector<int> visited;
    Vertex current_vertex;


    //Compare Function used for the prio queue, sorts elements by distance
    auto compare = [](Vertex &vertex1, Vertex &vertex2) { return vertex1.distance > vertex2.distance;};
    priority_queue<Vertex,vector<Vertex>, decltype(compare) > priorityQueue(compare);

    //copy elements from nodes vector and insert them into vertices
    int counter = 0;
    for(const auto& node : nodes){
        Vertex vertex;
        vertex.index = counter;
        if(counter == source)
            vertex.distance = 0;
        vertex.linked_vertex = node;
        vertices.push_back(vertex);
        counter++;
    }
    //adding final node;
    current_vertex.index = counter;
    vertices.push_back(current_vertex);

    priorityQueue.push(vertices.at(source));
    visited.push_back(source);

    while (!priorityQueue.empty()){
        current_vertex = priorityQueue.top();
        priorityQueue.pop();
        int alt = current_vertex.distance + 1;
        if(current_vertex.index != final){
            for(auto route : current_vertex.linked_vertex){
                int destination = route.destination;
                if(alt < vertices.at(destination).distance){
                    vertices.at(destination).distance = alt;
                    vertices.at(destination).source = current_vertex.index;
                    if(vectorContains(visited,vertices.at(destination).index) == FAILED_FLAG){
                        visited.push_back(vertices.at(destination).index);
                        priorityQueue.push(vertices.at(destination));
                    }
                }
            }
        }
    }

    return vertices;
}

int secondScenario::vectorContains(vector<int> vector, int value) {
    int counter = 0;
    for(auto elem : vector){
        if (elem == value) return counter;
        counter++;
    }
    return FAILED_FLAG;
}


