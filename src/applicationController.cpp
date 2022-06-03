//
// Created by Eduardo Correia on 09/04/2022.
//

#include "applicationController.h"

using namespace std;

applicationController::applicationController() {
    state = 0;
}

bool applicationController::run() {
    switch (state) {
        case 1:
            readFixed();
            return true;
        case 2:
            computeFirst();
            return true;
        case 3:
            computeSecond();
            return true;
        case 4:
            printRoutes();
            return true;
        default:
            return false;
    }
}

void applicationController::setState(int new_state) {
    this->state = new_state;
}

void applicationController::printMainMenu(){
    cout << "-*-------------  Main Menu  --------------------------*-" << endl;
    cout << " |--> Input: " << endl;
    cout << " |        1 - Fixed input" << endl;
    cout << " |--> Computing Scenarios: " << endl;
    cout << " |        2 - Compute Scenario 1 " << endl;
    cout << " |        3 - Compute Scenario 2"  << endl;
    cout << " |--> Printing Data: " << endl;
    cout << " |        4 - Print Routes"<< endl;
    cout << " |--> Exit " << endl;
    cout << " |        0 - Exit application "<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

void applicationController::readFixed() {
    char fileIndex;
    string newInputPath;
    cout << "-*---------  Choose which file to read from [1,10] ---*-"<< endl;
    cin >> fileIndex;
    newInputPath = string(INPUT_PATH) + string("in") + fileIndex + string("_b.txt");
    data.setInputPath(newInputPath);
    if(data.readNodes()){
        cout << "-*-------------  Finished reading data  --------------*-" << endl;
    }
    else{
        cout << "-*------------  [ERROR] Opening file  ---------------*-" << endl;
    }

}

void applicationController::computeFirst() {
    if(checkForEmpty(data.getNodes())) return;
    firstScenario algorithm(data.getNodes());
    algorithm.compute();
}

void applicationController::computeSecond() {
    if(checkForEmpty(data.getNodes())) return;
    secondScenario algorithm(data.getNodes());
    algorithm.compute();
}

bool applicationController::checkForEmpty(const map<int, vector<Route>> &vector){
    if(vector.empty()){
        cout << "-*-------------  [ERROR] Data not loaded  ------------*-" << endl;
        return true;
    }
    return false;
}

void applicationController::printRoutes() {
    char answer;
    if(checkForEmpty(data.getNodes())) return;
        cout << "-*------------- Print the data to a file? (y/n)  -----*-" << endl;
    cin >> answer;
    data.printNodes(answer);
}


