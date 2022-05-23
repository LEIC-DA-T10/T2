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

dataIO::dataIO(string inputPath) {
    this->inputPath = std::move(inputPath);
}

bool dataIO::readTrucksFixed(int start, int finish) {
    fstream file;
    string stringBuffer;
    int counter = 0;

    file.open(truckPath, ios::in);
    if(!file) return false;

    for(int i = 0; i <= start; i++){
        getline(file,stringBuffer);
    }

    if(!trucks.empty()){
        for(auto truck : trucks){
            truck.truckLoad.clear();
        }
        trucks.clear();
    }

    while(getline(file,stringBuffer) && counter < (finish-start)){
        vector<string> splitString = split(stringBuffer," ");

        truck truckBuffer;
        truckBuffer.maxVolume = stoi(splitString.at(0));
        truckBuffer.maxWeight = stoi(splitString.at(1));
        truckBuffer.cost = stoi(splitString.at(2));
        truckBuffer.availableWeight = truckBuffer.maxWeight;
        truckBuffer.availableVolume = truckBuffer.maxVolume;

        trucks.push_back(truckBuffer);
        counter++;
    }

    file.close();
    return true;
}


bool dataIO::readNodes() {
    fstream file;
    file.open(inputPath, ios::in);
    if(!file) return false;
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


