//
// Created by Eduardo Correia on 06/04/2022.
//

#include <set>
#include <random>
#include <utility>
#include "dataIO.h"

using namespace std;


vector<string> split (const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

bool dataIO::readNodes() {
    fstream file;
    string stringBuffer;
    vector<string> splitString;

    file.open(inputPath, ios::in);
    if(!file){
        return false;
    }

    if(!nodes.empty()){
        nodes.clear();
    }

    //Get First Line
    getline(file,stringBuffer);
    splitString = split(stringBuffer," ");

    numberNodes = stoi(splitString.at(0));
    numberRoutes = stoi(splitString.at(1));

    while(getline(file,stringBuffer)){
        splitString = split(stringBuffer," ");
        Route routeBuffer;
        int source = stoi(splitString.at(0));
        routeBuffer.destination = stoi(splitString.at(1));
        routeBuffer.capacity = stoi(splitString.at(2));
        routeBuffer.duration = stoi(splitString.at(3));
        nodes.at(source).push_back(routeBuffer);
    }

    file.close();
    return true;
}



unsigned int dataIO::getNumberNodes() {
    return this->numberNodes;
}

vector<vector<Route>> dataIO::getNodes() {
    return this->nodes;
}

string dataIO::getInputPath() {
    return this->inputPath;
}

void dataIO::printNodes(char answer) {
    fstream file;
    if(answer == 'y'){
        file.open(NODE_PRINT_PATH, ios::out);
    }
    for (int i = 0; i <= numberNodes; i++){
        if(file){
            file << "Node " << i << " : (Destination, Capacity, Duration)" << endl;
            for(auto route : nodes.at(i)){
                file << "   (" << route.destination << "," << route.capacity << "," << route.duration << ")" << endl;
            }
        }
        else{
            cout << "Node " << i << " : (Destination, Capacity, Duration)" << endl;
            for(auto route : nodes.at(i)) {
                cout << "   (" << route.destination << "," << route.capacity << "," << route.duration << ")" << endl;
            }
        }
    }
    if(file) std::cout << "Written to file at : " << NODE_PRINT_PATH << endl;
    std::cout << "----" << endl;
}

void dataIO::setInputPath(const string &input) {
    dataIO::inputPath = input;
}


